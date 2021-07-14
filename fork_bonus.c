#include "phil_bonus.h"

int	get_forks(t_opt *opt, t_phil *phil)
{
	int	res;

	sem_wait(opt->sem);
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	sem_wait(opt->sem);
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	return (1);
}

void	drop_forks(t_opt *opt, t_phil *phil)
{
	sem_post(opt->sem);
	sem_post(opt->sem);
}
