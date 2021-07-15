#include "phil.h"

void	ft_exit(t_opt *opt)
{
	int	i;

	i = 0;
	while (i < opt->p_count)
	{
		free(opt->forks[i]);
		free(opt->fork_m[i]);
		free(opt->phils[i]);
		i++;
	}
	free(opt->print_m);
	free(opt->fork_m);
	free(opt->forks);
	free(opt->phils);
	free(opt->tid);
	free(opt);
	return ;
}

void	init_mutex(t_opt *opt)
{
	int	i;

	opt->fork_m = malloc(sizeof(pthread_mutex_t *) * (opt->p_count + 1));
	opt->forks = malloc(sizeof(int *) * (opt->p_count + 1));
	i = 0;
	while (i < opt->p_count)
	{
		opt->fork_m[i] = malloc(sizeof(pthread_mutex_t));
		opt->forks[i] = malloc(sizeof(int));
		*opt->forks[i] = 0;
		pthread_mutex_init(opt->fork_m[i], NULL);
		i++;
	}
	opt->fork_m[i] = opt->fork_m[0];
	opt->forks[i] = opt->forks[0];
	opt->print_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(opt->print_m, NULL);
	opt->sim_start = mtime();
}

int	main(int argc, char **argv)
{
	int				i;
	void			*ret;
	t_opt			*opt;
	t_phil			*phil;

	opt = gen_opt(argc, argv);
	i = 0;
	while (i < opt->p_count)
	{
		phil = gen_phil(opt, i);
		pthread_create(&opt->tid[i], NULL, &life, phil);
		i++;
	}
	i = 0;
	while (i < opt->p_count)
	{
		pthread_join(opt->tid[i], &ret);
		i++;
	}
	ft_exit(opt);
	return (0);
}
