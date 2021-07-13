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
	free(opt);
	return ;
}

int	get_forks(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 0;
	if (!phil->left)
	{
		pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
		if (!*opt->forks[phil->pid - 1])
		{
			wrapped_print(opt, mtime(), phil->pid, "has taken a fork (left)");
			*opt->forks[phil->pid - 1] = 1;
			res += 1;
			phil->left = 1;
		}
		pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	}
	else
		res += 1;
	if (!phil->right)
	{
		pthread_mutex_lock(opt->fork_m[phil->pid]);
		if (!*opt->forks[phil->pid])
		{
			wrapped_print(opt, mtime(), phil->pid, "has taken a fork (right)");
			*opt->forks[phil->pid] = 1;
			res += 2;
			phil->right = 1;
		}
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

void	init_mutex(t_opt *opt)
{
	int				i;
	pthread_mutex_t	**fork_m;

	i = 0;
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
}

int	main(int argc, char **argv)
{
	pthread_t		*tid;
	int				i;
	void			*ret;
	t_opt			*opt;
	t_phil			*phil;

	opt = malloc(sizeof(t_opt));
	opt->p_count = ft_atoi(argv[1]);
	opt->time_die = ft_atoi(argv[2]);
	opt->time_eat = ft_atoi(argv[3]);
	opt->time_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		opt->eat_count = ft_atoi(argv[5]);
	else
		opt->eat_count = -1;
	opt->alive = 1;
	opt->phils = malloc(sizeof(t_phil *) * opt->p_count);
	init_mutex(opt);
	tid = malloc(sizeof(pthread_t) * opt->p_count);
	i = 0;
	opt->sim_start = mtime();
	while (i < opt->p_count)
	{
		phil = malloc(sizeof(t_phil));
		opt->phils[i] = phil;
		phil->opt = opt;
		phil->pid = i + 1;
		phil->stage = 0;
		phil->fails = 1;
		phil->eat_count = 0;
		phil->stage_time = 0;
		phil->last_eat = mtime();
		pthread_create(&tid[i], NULL, &life, phil);
		i++;
	}
	i = 0;
	while (i < opt->p_count)
	{
		pthread_join(tid[i], &ret);
		i++;
	}
	ft_exit(opt);
	return (0);
}
