#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define RED     "\x1b[31m"

# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>

typedef struct s_rules
{
	int				count_philo;
	int				numb;
	int				tdie;
	int				teat;
	int				tsleep;
	int				eat;
	int				flag_dth;
	long			last_eat;
	struct timeval	current_time;
	struct timeval	time_start;
	long			new_start;
	sem_t			*sem;
	sem_t			*both_forks;
	sem_t			*print;
	sem_t			*die;
	int				*pid;
	pthread_t		t;
	int				status;
}				t_rules;

int			main(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long		get_ms(struct timeval current);
void		uusleep(long time, struct timeval now);
long		get_time(void);
int			error(int i, char *str);
int			pars_arg(int argc, char **argv, t_rules *rules, int y);
void		pars(int argc, char **argv, t_rules *rules);
void		*ded(void *a);
void		pprint(char *str, int i, t_rules *param);
void		eat(t_rules *param);
void		*all_eat(void *a);

#endif