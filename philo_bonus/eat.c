#include "philo_bonus.h"

void	*ded(void *a)
{
	t_rules	*param;
	int		res;

	param = (t_rules *)a;
	while (1)
	{
		res = get_time() - param->last_eat;
		if (res > param->tdie)
		{
			sem_post(param->die);
			sem_wait(param->print);
			printf(RED "%ld  %d is dead\n",
				   get_ms(param->time_start), param->numb);
			exit (1);
		}
	}
}

void	pprint(char *str, int i, t_rules *param)
{
	sem_wait(param->print);
	printf("%-6ld %d %s\n", get_ms(param->time_start), i, str);
	sem_post(param->print);
}

void	eat(t_rules *param)
{
	param->last_eat = param->new_start;
	pthread_create(&param->t, NULL, ded, (void *)param);
	pthread_detach(param->t);
	while (1)
	{
		sem_wait(param->both_forks);
		sem_wait(param->sem);
		pprint("has taken a fork- left", param->numb, param);
		sem_wait(param->sem);
		pprint("has taken a fork- right", param->numb, param);
		sem_post(param->both_forks);
		param->last_eat = get_time();
		pprint("is eating", param->numb, param);
		gettimeofday(&param->current_time, NULL);
		uusleep(param->teat, param->current_time);
		sem_post(param->sem);
		sem_post(param->sem);
		if (--param->eat == 0)
			break ;
		pprint("is sleeping", param->numb, param);
		gettimeofday(&param->current_time, NULL);
		uusleep(param->tsleep, param->current_time);
		pprint("is thinking", param->numb, param);
	}
	exit (1);
}

void	*all_eat(void *a)
{
	int		i;
	t_rules	*param;

	param = (t_rules *)a;
	i = param->count_philo - 1;
	while (i >= 0)
		waitpid(param->pid[i--], 0, 0);
	if (param->flag_dth == 1)
		return (NULL);
	printf(RED"%ld  Everyone ate %d times! \n",
		   get_ms(param->time_start), param->eat);
	exit(1);
}
