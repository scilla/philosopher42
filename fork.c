#include "phil.h"

int	check_left_fork(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 0;
	if (!*opt->forks[phil->pid - 1])
	{
		wrapped_print(opt, mtime(), phil->pid, "has taken a fork (left)");
		*opt->forks[phil->pid - 1] = 1;
		res += 1;
		phil->left = 1;
	}
	return (res);
}

int	check_right_fork(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 0;
	if (!*opt->forks[phil->pid])
	{
		wrapped_print(opt, mtime(), phil->pid, "has taken a fork (right)");
		*opt->forks[phil->pid] = 1;
		res += 2;
		phil->right = 1;
	}
	return (res);
}

int	get_forks(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 0;
	if (!phil->left)
	{
		pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
		res += check_left_fork(opt, phil);
		pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	}
	else
		res += 1;
	if (!phil->right)
	{
		pthread_mutex_lock(opt->fork_m[phil->pid]);
		res += check_right_fork(opt, phil);
		pthread_mutex_unlock(opt->fork_m[phil->pid]);
	}
	else
		res += 2;
	if (res != 3)
	{
		res = 0;
	}
	return (res);
}

void	drop_forks(t_opt *opt, t_phil *phil)
{
	pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
	pthread_mutex_lock(opt->fork_m[phil->pid]);
	*opt->forks[phil->pid - 1] = 0;
	*opt->forks[phil->pid] = 0;
	phil->right = 0;
	phil->left = 0;
	pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	pthread_mutex_unlock(opt->fork_m[phil->pid]);
}
