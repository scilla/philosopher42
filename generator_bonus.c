#include "phil_bonus.h"

void	gen_sem(t_opt *opt)
{
	char	*sem_name;

	sem_name = ft_strdup("/tmp/phil");
	sem_unlink(sem_name);
	opt->sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, opt->p_count);
	sem_name = ft_strdup("/tmp/salive");
	sem_unlink(sem_name);
	opt->alive = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 0);
}

t_opt	*gen_opt(int argc, char **argv)
{
	t_opt	*opt;
	char	*sem_name;

	if (argc < 5 || argc > 6)
	{
		printf("wrong args\n");
		exit(0);
	}
	opt = malloc(sizeof(t_opt));
	opt->p_count = atoi(argv[1]);
	opt->time_die = atoi(argv[2]);
	opt->time_eat = atoi(argv[3]);
	opt->time_sleep = atoi(argv[4]);
	opt->eat_count = -1;
	if (argc == 6)
		opt->eat_count = atoi(argv[5]);
	opt->sim_start = mtime();
	opt->phils = malloc(sizeof(t_phil *) * opt->p_count);
	opt->pids = malloc(sizeof(int) * opt->p_count);
	gen_sem(opt);
	return (opt);
}

t_phil	*gen_phil(t_opt *opt, int i)
{
	t_phil	*phil;

	phil = malloc(sizeof(t_phil));
	phil->stage = 0;
	phil->eat_count = 0;
	phil->stage_time = 0;
	phil->last_eat = mtime();
	phil->opt = opt;
	phil->pid = i + 1;
	return (phil);
}
