#ifndef PHIL_H
# define PHIL_H

#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
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
	t_llint			time_die;
	t_llint			time_eat;
	t_llint			time_sleep;
	int				p_count;
	int				**forks;
	int				alive;
	int				eat_count;
	pthread_mutex_t	**fork_m;
	pthread_mutex_t	*print_m;
	sem_t			*sem;
}				t_opt;

typedef struct	s_phil
{
	int			pid;
	int			stage;
	int			fails;
	int			left;
	int			right;
	int			eat_count;
	t_llint		stage_time;
	t_llint		last_eat;
	t_opt		*opt;
}				t_phil;

#endif
