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

void	msleep(t_llint msec)
{
	usleep(msec * 1000);
}

int	get_forks(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 0;
	//printf("%lld %d checking forks\n", mtime(), phil->pid);
	if (!phil->left)
	{
		pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
		if (!*opt->forks[phil->pid - 1])
		{
			printf("%lld %d has taken a fork (left)\n", mtime(), phil->pid);
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
			printf("%lld %d has taken a fork (right)\n", mtime(), phil->pid);
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

void	*life(void *arg)
{
	t_opt	*opt;
	t_phil	*phil;
	t_llint	tt;
	int		res;

	phil = (t_phil*)arg;
	opt = phil->opt;
	if (phil->pid % 2)
		msleep(opt->time_eat + 1);
	printf("%lld start %d\n", mtime(), phil->pid);
	while (opt->alive)
	{
		tt = mtime();
		if (phil->last_eat < tt - opt->time_die)
		{
			opt->alive = 0;
			printf("%lld %d died\n", tt, phil->pid);
			break ;
		}
		//if (phil->stage == 0 && tt - phil->last_eat > (phil->fails * opt->time_die) / (phil->fails + 1))
		if (phil->stage == 0)	// I am thinking
		{
			// if (phil->fails)
			// 	usleep(10 * phil->fails);
			res = get_forks(opt, phil);
			if (res)
			{
				printf("%lld %d is eating\n", tt, phil->pid);
				phil->last_eat = tt;
				phil->stage_time = tt;
				phil->stage = 1;
				phil->fails = 1;
			}
			else
				phil->fails++;
		}
		else if (phil->stage == 1)	// I am eating
		{
			if (phil->stage_time < tt - opt->time_eat)
			{
				printf("%lld %d is sleeping\n", tt, phil->pid);
				drop_forks(opt, phil);
				phil->stage_time = tt;
				phil->stage = 2;
			}
		}
		else if (phil->stage == 2)	// I am sleeping
		{
			if (phil->stage_time < tt - opt->time_sleep)
			{
				printf("%lld %d is thinking\n", tt, phil->pid);
				phil->stage_time = tt;
				phil->stage = 0;
			}
		}
		msleep(1);
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
	opt->p_count = atoi(argv[1]);
	opt->time_die = atoi(argv[2]);
	opt->time_eat = atoi(argv[3]);
	opt->time_sleep = atoi(argv[4]);
	opt->alive = 1;

	init_mutex(opt);

	attr = malloc(sizeof(pthread_attr_t));
	pthread_attr_init(attr);

	tid = malloc(sizeof(pthread_t) * opt->p_count);
	i = 0;
	while (i < opt->p_count)
	{
		msleep(1);
		phil = malloc(sizeof(t_phil));
		phil->opt = opt;
		phil->pid = i + 1;
		phil->stage = 0;
		phil->fails = 1;
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