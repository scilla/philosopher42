#ifndef PHIL_BONUS_H
# define PHIL_BONUS_H

# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef long long int	t_llint;

typedef struct s_tinfo
{
	pthread_t	tid;
	int			tnum;
}				t_tinfo;

typedef struct s_opt
{
	t_llint			time_die;
	t_llint			time_eat;
	t_llint			time_sleep;
	int				p_count;
	int				**forks;
	int				alive;
	int				eat_count;
	pthread_mutex_t	*print_m;
	sem_t			*sem;
}				t_opt;

typedef struct s_phil
{
	int			pid;
	int			stage;
	int			left;
	int			right;
	int			eat_count;
	t_llint		stage_time;
	t_llint		last_eat;
	t_opt		*opt;
}				t_phil;

void	*life(void *arg);
void	wrapped_print(t_opt *opt, t_llint ttime, int pid, char *str);
void	msleep(t_llint msec);
t_llint	mtime(void);
int		ft_atoi(const char *str);
t_phil	*gen_phil(t_opt *opt, int i);
t_opt	*gen_opt(int argc, char **argv);
void	init_mutex(t_opt *opt);
void	drop_forks(t_opt *opt, t_phil *phil);
int		get_forks(t_opt *opt, t_phil *phil);

#endif
