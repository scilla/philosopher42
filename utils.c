#include "phil.h"

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
