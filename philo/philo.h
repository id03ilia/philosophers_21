#ifndef PHILO_H
# define PHILO_H

# define RED     "\x1b[31m"
# define WHITE   "\x1b[0m"

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_t		t;
	int				numb;
	int				l_fork;
	int				r_fork;
	long			last_eat;
	int				count_eat;
	int				p_eating;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	int				count_philo;
	int				eat;
	int				eat_all;
	int				one_died;
	int				tdie;
	int				teat;
	int				tsleep;
	struct timeval	current_time;
	struct timeval	time_start;
	pthread_mutex_t	die;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}				t_rules;

int			main(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_ms(struct timeval old);
void		uusleep(long time, struct timeval now, t_philo *philo);
int			get_time(void);
void		pprint(char *str, int i, t_philo *philo);
void		*eat(void *philo_tmp);
int			error(int i, char *str);
void		init_rules(t_rules *rules);
int			pars(int argc, char **argv, t_rules *rules, int y);
void		forks(t_rules *rules);
int			check_die(t_rules *rules, int *i);
int			live_philo(t_rules *rules);
int			is_digit_pars(int argc, char **argv, t_rules	*rules);

#endif
