#include "philo_bonus.h"

void	init_rules(t_rules *param)
{
	param->count_philo = 0;
	param->tdie = 0;
	param->teat = 0;
	param->tsleep = 0;
}

void	philo_fork(t_rules *param)
{
	int	i;

	param->pid = malloc(sizeof(int) * param->count_philo);
	if (!param->pid)
		exit (-1);
	i = 0;
	while (i < param->count_philo)
		param->pid[i++] = -1;
	i = 0;
	param->numb = 1;
	while (i < param->count_philo)
	{
		param->pid[i] = fork();
		if (param->pid[i] == 0)
		{
			if (i == 0)
				sem_wait(param->die);
			eat(param);
		}
		else
		{
			param->numb++;
			i++;
		}
	}
}

void	ini_sem(t_rules *param)
{
	sem_unlink("main");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("die");
	param->sem = sem_open("main", O_CREAT, 0666, param->count_philo);
	if (!param->sem)
		exit (-1);
	param->both_forks = sem_open("forks", O_CREAT, 0666, 1);
	if (!param->both_forks)
		exit (-1);
	param->print = sem_open("print", O_CREAT, 0666, 1);
	if (!param->print)
		exit (-1);
	param->die = sem_open("die", O_CREAT, 0666, 1);
	if (!param->die)
		exit (-1);
}

void	sem_clear(t_rules *param)
{
	wait(NULL);
	sem_close(param->sem);
	sem_close(param->both_forks);
	sem_close(param->print);
	sem_post(param->die);
	sem_close(param->die);
	free(param->pid);
}

int	main(int argc, char **argv)
{
	int			i;
	t_rules		param;
	pthread_t	t_m;

	init_rules(&param);
	pars(argc, argv, &param);
	ini_sem(&param);
	gettimeofday(&param.time_start, NULL);
	param.new_start = get_time();
	param.flag_dth = 0;
	philo_fork(&param);
	usleep(200);
	if (argc == 6)
	{
		pthread_create(&t_m, NULL, all_eat, (void *)&param);
		pthread_detach(t_m);
	}
	sem_wait(param.die);
	param.flag_dth = 1;
	usleep(200);
	i = param.count_philo - 1;
	while (i > -1)
		kill(param.pid[i--], 9);
	sem_clear(&param);
	exit (1);
}
