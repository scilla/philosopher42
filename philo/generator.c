#include "phil.h"

t_phil	*gen_phil(t_opt *opt, int i)
{
	t_phil	*phil;

	phil = malloc(sizeof(t_phil));
	opt->phils[i] = phil;
	phil->opt = opt;
	phil->pid = i + 1;
	phil->stage = 0;
	phil->left = 0;
	phil->right = 0;
	phil->eat_count = 0;
	phil->stage_time = 0;
	phil->last_eat = mtime();
	return (phil);
}

void	wrong_args(t_opt *opt)
{
	free(opt);
	printf("wrong args\n");
	exit(0);
}

t_opt	*gen_opt(int argc, char **argv)
{
	t_opt	*opt;

	opt = malloc(sizeof(t_opt));
	if (argc < 5 || argc > 6)
		wrong_args(opt);
	opt->p_count = ft_atoi(argv[1]);
	opt->time_die = ft_atoi(argv[2]);
	opt->time_eat = ft_atoi(argv[3]);
	opt->time_sleep = ft_atoi(argv[4]);
	opt->eat_count = -1;
	if (argc == 6)
		opt->eat_count = ft_atoi(argv[5]);
	if (!opt->p_count || !opt->time_die || !opt->time_eat || !opt->time_sleep
		|| !opt->eat_count)
		wrong_args(opt);
	opt->alive = 1;
	opt->phils = malloc(sizeof(t_phil *) * opt->p_count);
	init_mutex(opt);
	opt->tid = malloc(sizeof(pthread_t) * opt->p_count);
	return (opt);
}
