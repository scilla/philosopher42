#include "phil_bonus.h"

typedef struct timeval	t_time;
typedef struct timezone	t_zone;

void	init_mutex(t_opt *opt)
{
	int		i;
	char	*sem_name;

	sem_name = ft_strdup("/tmp/sprint");
	i = 0;
	opt->forks = malloc(sizeof(int *) * (opt->p_count + 1));
	i = 0;
	while (i < opt->p_count)
	{
		opt->forks[i] = malloc(sizeof(int));
		*opt->forks[i] = 0;
		i++;
	}
	opt->forks[i] = opt->forks[0];
	sem_unlink(sem_name);
	opt->print_m = sem_open(sem_name, O_CREAT | O_EXCL, 0644, opt->p_count);
}

void	forker(t_opt *opt, int i)
{
	t_phil	*phil;

	msleep(100);
	phil = gen_phil(opt, i);
	opt->phils[i] = phil;
	opt->pids[i] = fork();
	if (!opt->pids[i])
	{
		life(phil);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_phil	*phil;
	t_opt	*opt;

	opt = gen_opt(argc, argv);
	init_mutex(opt);
	i = 0;
	while (i < opt->p_count)
	{
		forker(opt, i);
		i++;
	}
	i = 0;
	while (i < opt->p_count)
	{
		waitpid(opt->pids[i], (int *)&opt->pids[i], 0);
		i++;
	}
	return (0);
}
