#include "phil.h"

void	wrapped_print(t_opt *opt, t_llint ttime, int pid, char *str)
{
	pthread_mutex_lock(opt->print_m);
	if (opt->alive)
		printf("%lld %d %s\n", ttime - opt->sim_start, pid, str);
	pthread_mutex_unlock(opt->print_m);
}

t_llint	mtime(void)
{
	t_llint	mtime_res;
	int		res;
	t_time	tv;
	t_zone	tz;

	res = gettimeofday(&tv, &tz);
	mtime_res = tv.tv_sec * 1000;
	mtime_res += tv.tv_usec / 1000;
	return (mtime_res);
}

void	msleep(t_llint msec)
{
	usleep(msec * 1000);
}

void	msleep_till(t_llint msec)
{
	t_llint	delta;

	delta = msec - mtime();
	if (delta > 0)
		msleep(delta);
}
