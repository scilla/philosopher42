#include "phil_bonus.h"

typedef struct timeval	t_time;
typedef struct timezone	t_zone;

void	init_mutex(t_opt *opt)
{
	int		i;
	char	*sem_name;

	sem_name = ft_strdup("/tmp/sprint");
	i = 0;
	sem_unlink(sem_name);
	opt->print_m = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
}

void	forker(t_opt *opt, int i)
{
	t_phil	*phil;

	phil = gen_phil(opt, i);
	opt->phils[i] = phil;
	opt->pids[i] = fork();
	if (!opt->pids[i])
	{
		life(phil);
		exit(0);
	}
}

void	ft_exit(t_opt *opt)
{
	int	i;

	i = 0;
	while (i < opt->p_count)
	{
		free(opt->phils[i]);
		i++;
	}
	free(opt->pids);
	free(opt->phils);
	free(opt);
	return ;
}

void	*kill_all(void *arg)
{
	int		i;
	t_opt	*opt;

	opt = arg;
	sem_wait(opt->alive);
	i = 0;
	while (i < opt->p_count)
	{
		kill(opt->pids[i], 1);
		i++;
	}
	return (0);
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
	pthread_create(&opt->tid, NULL, &kill_all, opt);
	i = 0;
	while (i < opt->p_count)
	{
		waitpid(opt->pids[i], (int *)&opt->pids[i], 0);
		i++;
	}
	ft_exit(opt);
	return (0);
}
