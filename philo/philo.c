#include "philo.h"

int	init_pthr(t_rules *rules)
{
	int	f;

	rules->philo = malloc(sizeof(t_philo) * rules->count_philo);
	rules->fork = malloc(sizeof(pthread_mutex_t) * rules->count_philo);
	f = 0;
	while (++f <= rules->count_philo)
	{
		if (pthread_mutex_init(&rules->fork[f], NULL) != 0)
			return (-1);
		rules->philo[f].rules = rules;
		rules->philo[f].numb = f;
		rules->philo[f].count_eat = rules->eat;
	}
	if (pthread_mutex_init(&rules->die, NULL) != 0)
		return (-1);
	return (0);
}

void	pthr_create(int z, t_rules *rules)
{
	int		i;
	void	*a;

	i = 0;
	while (++i <= rules->count_philo)
	{
		if (i % 2 == z)
		{
			rules->philo[i].last_eat = get_time();
			a = (void *) &rules->philo[i];
			pthread_create(&rules->philo[i].t, NULL, &eat, a);
			usleep(50);
		}
	}
}

int	pthr(t_rules rules)
{
	if (init_pthr(&rules) == -1)
		return (-1);
	forks(&rules);
	gettimeofday(&rules.time_start, NULL);
	pthr_create(1, &rules);
	pthr_create(0, &rules);
	while (1)
	{
		rules.one_died = live_philo(&rules);
		if (rules.one_died == -1)
			break ;
	}
	usleep(10000);
	free(rules.philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		y;

	y = 0;
	init_rules(&rules);
	if (argc == 5 || argc == 6)
		y = is_digit_pars(argc, argv, &rules);
	else
	{
		error(-3, NULL);
		return (-1);
	}
	if (y < 0 || pthr(rules) == -1)
		return (-1);
	return (0);
}
