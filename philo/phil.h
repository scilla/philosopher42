/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:25:14 by scilla            #+#    #+#             */
/*   Updated: 2021/07/15 17:25:15 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef long long int	t_llint;
typedef struct timeval	t_time;
typedef struct timezone	t_zone;

typedef struct s_tinfo
{
	pthread_t	tid;
	int			tnum;
}				t_tinfo;

typedef struct s_phil	t_phil;

typedef struct s_opt
{
	t_llint			sim_start;
	t_llint			time_die;
	t_llint			time_eat;
	t_llint			time_sleep;
	int				p_count;
	int				**forks;
	int				alive;
	int				eat_count;
	pthread_mutex_t	**fork_m;
	pthread_mutex_t	*print_m;
	t_phil			**phils;
	pthread_t		*tid;
}				t_opt;

typedef struct s_phil
{
	int			pid;
	int			stage;
	int			left;
	int			right;
	int			eat_count;
	int			alive;
	t_llint		stage_time;
	t_llint		last_eat;
	t_opt		*opt;
	pthread_t	tid;
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
char	*ft_strdup(const char *s1);

#endif
