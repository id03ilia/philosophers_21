#include "philo_bonus.h"

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

int	pars_arg(int argc, char **argv, t_rules *rules, int y)
{
	rules->count_philo = ft_atoi(argv[1]);
	if (rules->count_philo < 1)
		y = error(-2, argv[1]);
	rules->tdie = ft_atoi(argv[2]);
	if (rules->tdie == -1)
		y = error(-4, argv[2]);
	rules->teat = ft_atoi(argv[3]);
	if (rules->teat == -1)
		y = error(-4, argv[3]);
	rules->tsleep = ft_atoi(argv[4]);
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
	int	i;
	int	z;
	int	y;

	i = 0;
	y = 0;
	while (++i < argc)
	{
		z = 0;
		while (argv[i][z])
		{
			if (ft_isdigit(argv[i][z++]) == 0)
			{
				y = error(-1, argv[i]);
				exit (-1);
			}
		}
	}
	y = pars_arg(argc, argv, rules, y);
	return (y);
}

void	pars(int argc, char **argv, t_rules *rules)
{
	int	y;

	y = 0;
	if (argc == 5 || argc == 6)
	{
		y = is_digit_pars(argc, argv, rules);
	}
	else
		y = error(-3, NULL);
	if (y < 0)
		exit (-1);
}
