#include "philo.h"

int	error(int i, char *str)
{
	if (i == -1)
		printf("Error\n - argument %s is not recommended\n", str);
	if (i == -2)
		printf("Error\n - philo 1 .. 200, you=%s\n", str);
	if (i == -3)
		printf("Error\n - format: count_philos time_to_die time_to_eat "
			   "time_to_sleep number_of_times_each_philos(optional)\n");
	if (i == -4)
		printf("Error\n - max int %s\n", str);
	if (i == -5)
		printf("Error\n - need to eat > 0 \n");
	return (i);
}

void	init_rules(t_rules *rules)
{
	rules->count_philo = 0;
	rules->tdie = 0;
	rules->teat = 0;
	rules->tsleep = 0;
	rules->eat_all = 0;
	rules->one_died = 0;
}

int	pars(int argc, char **argv, t_rules *rules, int y)
{
	rules->count_philo = ft_atoi(argv[1]);
	rules->tdie = ft_atoi(argv[2]);
	rules->teat = ft_atoi(argv[3]);
	rules->tsleep = ft_atoi(argv[4]);
	if (rules->count_philo < 1)
		y = error(-2, argv[1]);
	if (rules->tdie == -1)
		y = error(-4, argv[2]);
	if (rules->teat == -1)
		y = error(-4, argv[3]);
	if (rules->tsleep == -1)
		y = error(-4, argv[4]);
	if (argc == 6)
	{
		rules->eat = ft_atoi(argv[5]);
		if (rules->eat == -1)
			y = error(-4, argv[5]);
		if (rules->eat == 0)
			y = error(-5, argv[5]);
	}
	else
		rules->eat = -1;
	return (y);
}

int	is_digit_pars(int argc, char **argv, t_rules	*rules)
{
	int	y;
	int	i;
	int	z;

	y = 0;
	i = 0;
	while (++i < argc)
	{
		z = 0;
		while (argv[i][z])
		{
			if (ft_isdigit(argv[i][z++]) == 0)
			{
				error(-1, argv[i]);
				return (-1);
			}
		}
	}
	y = pars(argc, argv, rules, y);
	return (y);
}

void	forks(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->count_philo == 1)
	{
		rules->philo[1].l_fork = 1;
		rules->philo[1].r_fork = 1;
		return ;
	}
	while (++i <= rules->count_philo)
	{
		rules->philo[i].l_fork = i;
		if ((i + 1) % rules->count_philo == 0)
			rules->philo[i].r_fork = i + 1;
		else
			rules->philo[i].r_fork = (i + 1) % rules->count_philo;
	}
}
