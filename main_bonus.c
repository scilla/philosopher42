#include "phil_bonus.h"

typedef struct timeval	t_time;
typedef struct timezone	t_zone;

void	init_mutex(t_opt *opt)
{
	int	i;
	pthread_mutex_t	**fork_m;

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
	opt->print_m = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(opt->print_m, NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		*tid;
	int				i;
	void			*ret;
	t_opt			*opt;
	t_phil			*phil;
	int				*pids;

	printf("%lld sim started\n", mtime());
	opt = malloc(sizeof(t_opt));
	opt->p_count = atoi(argv[1]);
	opt->time_die = atoi(argv[2]);
	opt->time_eat = atoi(argv[3]);
	opt->time_sleep = atoi(argv[4]);
	opt->alive = 1;
	if (argc > 5)
		opt->eat_count = atoi(argv[5]);
	else
		opt->eat_count = -1;
	char semname[] = "sem9";
	sem_unlink(semname);
	opt->sem = sem_open(semname, O_CREAT, 0644, opt->p_count);
	printf("sem create %p\n", opt->sem);
	init_mutex(opt);
	pids = malloc(sizeof(int) * opt->p_count);
	tid = malloc(sizeof(pthread_t) * opt->p_count);
	i = 0;
	while (i < opt->p_count)
	{
		msleep(100);
		phil = malloc(sizeof(t_phil));
		phil->stage = 0;
		phil->eat_count = 0;
		phil->stage_time = 0;
		phil->last_eat = mtime();
		phil->opt = opt;
		phil->pid = i + 1;
		pids[i] = fork();
		if (!pids[i])
		{
			life(phil);
			printf("child %d done\n", phil->pid);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < opt->p_count)
	{
		printf("pid %d wait\n", pids[i]);
		waitpid(pids[i], &pids[i], 0);
		i++;
	}
	return (0);
}
