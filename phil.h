#ifndef PHIL_H
# define PHIL_H

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef long long int	t_llint;

typedef struct	s_tinfo
{
	pthread_t	tid;
	int			tnum;
}				t_tinfo;

typedef struct	s_opt
{
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	p_count;
	int	**forks;
	pthread_mutex_t	**fork_m;
	pthread_mutex_t	*print_m;
}				t_opt;

typedef struct	s_phil
{
	int			pid;
	int			stage;
	t_llint		eat;
	t_llint		think;
	t_llint		sleep;
	t_llint		stage_time;
	t_opt		*opt;
}				t_phil;

#endif
