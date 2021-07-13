#include "phil.h"

void	*life(void *arg)
{
	t_opt	*opt;
	t_phil	*phil;
	t_llint	tt;
	int		res;

	phil = (t_phil *)arg;
	opt = phil->opt;
	wrapped_print(opt, mtime(), phil->pid, "start");
	if (!(phil->pid % 2))
		msleep(opt->time_eat + 1);
	while (opt->alive)
	{
		tt = mtime();
		if (phil->last_eat < tt - opt->time_die)
		{
			opt->alive = 0;
			wrapped_print(opt, mtime(), phil->pid, "died");
			break ;
		}
		if (phil->stage == 0)
		{
			res = get_forks(opt, phil);
			if (res)
			{
				wrapped_print(opt, mtime(), phil->pid, "is eating");
				phil->last_eat = tt;
				phil->stage_time = tt;
				phil->stage = 1;
				phil->fails = 1;
			}
			else
				phil->fails++;
		}
		else if (phil->stage == 1)
		{
			if (phil->stage_time < tt - opt->time_eat)
			{
				wrapped_print(opt, mtime(), phil->pid, "is sleeping");
				drop_forks(opt, phil);
				phil->stage_time = tt;
				phil->stage = 2;
			}
		}
		else if (phil->stage == 2)
		{
			if (phil->stage_time < tt - opt->time_sleep)
			{
				phil->stage_time = tt;
				phil->stage = 0;
				phil->eat_count++;
				if (opt->eat_count >= 0 && phil->eat_count >= opt->eat_count)
				{
					wrapped_print(opt, mtime(), phil->pid, "done!");
					break ;
				}
				else
					wrapped_print(opt, mtime(), phil->pid, "is thinking");
			}
		}
	}
	return (0);
}
