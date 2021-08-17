#include "philo.h"

long long	get_ms(struct timeval old)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	new.tv_sec -= old.tv_sec;
	new.tv_usec -= old.tv_usec;
	if (new.tv_usec < 0)
	{
		--new.tv_sec;
		new.tv_usec += 1000000;
	}
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

void	uusleep(long time, struct timeval now, t_philo *philo)
{
	long long	cur_time;

	cur_time = get_ms(now);
	while (1)
	{
		usleep(100);
		if (get_ms(now) >= cur_time + time || philo->rules->one_died == -1)
			break ;
	}
}

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
