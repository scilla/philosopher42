#include "phil.h"

int	check_left_fork(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 0;
	if (!*opt->forks[phil->pid - 1])
	{
		wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
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
		wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
		*opt->forks[phil->pid] = 1;
		res += 2;
		phil->right = 1;
	}
	return (res);
}

int	get_forks(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 1;
	pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	pthread_mutex_lock(opt->fork_m[phil->pid]);
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	return (res);
}

void	drop_forks(t_opt *opt, t_phil *phil)
{
	*opt->forks[phil->pid - 1] = 0;
	*opt->forks[phil->pid] = 0;
	phil->right = 0;
	phil->left = 0;
	pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	pthread_mutex_unlock(opt->fork_m[phil->pid]);
}
