#include "philo.h"

int	check_die(t_rules *rules, int *i)
{
	int	res;

	res = get_time() - rules->philo[*i].last_eat;
	if (res > rules->tdie)
	{
		pthread_mutex_lock(&rules->die);
		rules->one_died = -1;
		usleep(50);
		printf(RED "%-6lld %d died\n" WHITE, get_ms(rules->time_start), *i);
		return (-1);
	}
	if (rules->philo[*i].count_eat == 0
		&& rules->philo[*i].p_eating == 0 && rules->eat > -1)
	{
		rules->eat_all++;
		rules->philo[*i].p_eating = 1;
	}
	return (0);
}

int	live_philo(t_rules *rules)
{
	int	i;
	int	res;

	i = 1;
	while (1)
	{
		while (i <= rules->count_philo)
		{
			res = check_die(rules, &i);
			if (res == -1)
				return (-1);
			i++;
		}
		if (rules->eat_all == rules->count_philo && rules->eat > -1)
		{
			pthread_mutex_lock(&rules->die);
			rules->one_died = -1;
			usleep(50);
			printf(RED "%-6lld Everyone ate the required amount \n" WHITE,
				   get_ms(rules->time_start));
			return (-1);
		}
		i = 1;
	}
}

void	pprint(char *str, int i, t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->die);
	printf(WHITE"%-6lld %d %s\n", get_ms(philo->rules->time_start), i, str);
	pthread_mutex_unlock(&philo->rules->die);
}

void	*eat(void *philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	pthread_detach(philo->t);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->fork[philo->r_fork]);
		pprint("has taken a fork- right", philo->numb, philo);
		pthread_mutex_lock(&philo->rules->fork[philo->l_fork]);
		pprint("has taken a fork- left", philo->numb, philo);
		philo->last_eat = get_time();
		pprint("is eating", philo->numb, philo);
		gettimeofday(&philo->rules->current_time, NULL);
		uusleep(philo->rules->teat, philo->rules->current_time, philo);
		pthread_mutex_unlock(&philo->rules->fork[philo->l_fork]);
		pthread_mutex_unlock(&philo->rules->fork[philo->r_fork]);
		philo->count_eat--;
		pprint("is sleeping", philo->numb, philo);
		gettimeofday(&philo->rules->current_time, NULL);
		uusleep(philo->rules->tsleep, philo->rules->current_time, philo);
		pprint("is thinking", philo->numb, philo);
		if (philo->rules->one_died == -1)
			break ;
	}
	return (NULL);
}
