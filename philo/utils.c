#include "utils.h"

t_llint	mtime(void)
{
	t_time	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
