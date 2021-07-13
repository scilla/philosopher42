#include "phil.h"

void	stage_eat(t_opt *opt, t_phil *phil, t_llint tt)
{
	int	res;

	if (phil->stage == 0)
	{
		res = get_forks(opt, phil);
		if (res)
		{
			wrapped_print(opt, mtime(), phil->pid, "is eating");
			phil->last_eat = tt;
			phil->stage_time = tt;
			phil->stage = 1;
		}
	}
}

void	stage_sleep(t_opt *opt, t_phil *phil, t_llint tt)
{
	if (phil->stage == 1)
	{
		if (phil->stage_time < tt - opt->time_eat)
		{
			wrapped_print(opt, mtime(), phil->pid, "is sleeping");
			drop_forks(opt, phil);
			phil->stage_time = tt;
			phil->stage = 2;
		}
	}
}

int	stage_think(t_opt *opt, t_phil *phil, t_llint tt)
{
	int	res;

	res = 0;
	if (phil->stage == 2)
	{
		if (phil->stage_time < tt - opt->time_sleep)
		{
			phil->stage_time = tt;
			phil->stage = 0;
			phil->eat_count++;
			if (opt->eat_count >= 0 && phil->eat_count >= opt->eat_count)
			{
				wrapped_print(opt, mtime(), phil->pid, "done!");
				res++;
			}
			else
				wrapped_print(opt, mtime(), phil->pid, "is thinking");
		}
	}
	return (res);
}

int	check_death(t_opt *opt, t_phil *phil, t_llint tt)
{
	int	res;

	res = 0;
	if (phil->last_eat < tt - opt->time_die)
	{
		wrapped_print(opt, mtime(), phil->pid, "died");
		opt->alive = 0;
		res++;
	}
	return (res);
}

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
		msleep(opt->time_eat);
	while (opt->alive)
	{
		tt = mtime();
		if (check_death(opt, phil, tt))
			break ;
		stage_eat(opt, phil, tt);
		stage_sleep(opt, phil, tt);
		if (stage_think(opt, phil, tt))
			break ;
	}
	return (0);
}
