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

void	*pinfo(void *arg)
{
	t_llint	start;
	t_opt	*opt;

	opt = (t_opt*)arg;
	start = mtime();
	for (int i = 0; 1; i++){
		printf("time: %lld %d\n", mtime(), opt->time_eat);
		msleep_till(start + 1000 * i + i);
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
	t_tinfo			*tinfo;
	pthread_attr_t	*attr;
	int				i;
	void			*ret;
	t_opt			*opt;

	opt = malloc(sizeof(t_opt));
	opt->time_die = 800;
	opt->time_eat = 200;
	opt->time_sleep = 200;
	opt->p_count = 5;

	init_mutex(opt);

	attr = malloc(sizeof(pthread_attr_t));
	pthread_attr_init(attr);

	tinfo = malloc(sizeof(t_tinfo));
	i = pthread_create(&tinfo->tid, attr, &pinfo, opt);
	usleep(200 * 1000);
	i = pthread_create(&tinfo->tid, attr, &pinfo, opt);
	pthread_join(tinfo->tid, &ret);
	return (0);
}