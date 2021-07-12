#include "phil.h"

typedef struct timeval	t_time;
typedef struct timezone	t_zone;

t_llint	mtime()
{
	t_llint	mtime_res;
	int		res;
	t_time	tv;
	t_zone	tz;

	res = gettimeofday(&tv, &tz);
	mtime_res = tv.tv_sec * 1000;
	mtime_res += tv.tv_usec / 1000;
	return (mtime_res);
}

void	msleep_till(t_llint msec)
{
	t_llint	delta;

	delta = msec - mtime();
	if (delta > 0)
		usleep(delta * 1000);
}

int	get_forks(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 0;
	pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
	pthread_mutex_lock(opt->fork_m[phil->pid]);
	if (!opt->forks[phil->pid - 1] && !opt->forks[phil->pid])
	{
		*opt->forks[phil->pid - 1] = 1;
		*opt->forks[phil->pid] = 1;
		res = 1;
	}
	pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	pthread_mutex_unlock(opt->fork_m[phil->pid]);
	return (res);
}

void	drop_forks(t_opt *opt, t_phil *phil)
{
	pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
	pthread_mutex_lock(opt->fork_m[phil->pid]);
	*opt->forks[phil->pid - 1] = 0;
	*opt->forks[phil->pid] = 0;
	pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	pthread_mutex_unlock(opt->fork_m[phil->pid]);
}

void	*life(void *arg)
{
	t_opt	*opt;
	t_phil	*phil;

	phil = (t_phil*)arg;
	opt = phil->opt;
	while (opt->alive)
	{
		if (phil->last_eat < mtime() - opt->time_die)
		{
			opt->alive = 0;
			printf("%lld %d died\n", mtime(), phil->pid);
			break ;
		}
	}
	return (0);
}

pthread_mutex_t	**init_mutex(t_opt *opt)
{
	int	i;
	pthread_mutex_t	**fork_m;

	i = 0;
	opt->fork_m = malloc(sizeof(pthread_mutex_t*) * (opt->p_count + 1));
	opt->forks = malloc(sizeof(int*) * (opt->p_count + 1));
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
	pthread_attr_t	*attr;
	int				i;
	void			*ret;
	t_opt			*opt;
	t_phil			*phil;

	opt = malloc(sizeof(t_opt));
	opt->time_die = 800;
	opt->time_eat = 200;
	opt->time_sleep = 200;
	opt->p_count = 5;
	opt->alive = 1;

	init_mutex(opt);

	attr = malloc(sizeof(pthread_attr_t));
	pthread_attr_init(attr);

	tid = malloc(sizeof(pthread_t) * opt->p_count);
	i = 0;
	printf("%lld start\n", mtime());
	while (i < opt->p_count)
	{
		usleep(600);
		phil = malloc(sizeof(t_phil));
		phil->opt = opt;
		phil->pid = i + 1;
		phil->stage = 0;
		phil->stage_time = 0;
		phil->last_eat = mtime();
		pthread_create(&tid[i], attr, &life, phil);
		i++;
	}
	i = 0;
	while (i < opt->p_count)
	{
		pthread_join(tid[i], &ret);
		i++;
	}
	return (0);
}