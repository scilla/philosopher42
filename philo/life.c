/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:25:01 by scilla            #+#    #+#             */
/*   Updated: 2021/07/20 16:40:00 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	stage_eat(t_opt *opt, t_phil *phil)
{
	int		res;
	t_llint	tt;

	res = get_forks(opt, phil);
	if (res)
	{
		tt = mtime();
		wrapped_print(opt, tt, phil->pid, "is eating");
		phil->last_eat = tt;
		phil->stage_time = tt;
		phil->stage = 1;
		msleep(opt->time_eat - 5);
	}
}

void	stage_sleep(t_opt *opt, t_phil *phil)
{
	t_llint	tt;

	tt = mtime();
	if (phil->stage_time <= tt - opt->time_eat)
	{
		if (!(opt->eat_count >= 0 && phil->eat_count >= opt->eat_count - 1))
			wrapped_print(opt, tt, phil->pid, "is sleeping");
		drop_forks(opt, phil);
		phil->stage_time = tt;
		phil->stage = 2;
		msleep(opt->time_sleep - 5);
	}
}

int	stage_think(t_opt *opt, t_phil *phil)
{
	int		res;
	t_llint	tt;

	res = 0;
	if (phil->stage == 2)
	{
		tt = mtime();
		if (phil->stage_time <= tt - opt->time_sleep)
		{
			phil->stage_time = tt;
			phil->stage = 0;
			phil->eat_count++;
			if (opt->eat_count >= 0 && phil->eat_count >= opt->eat_count)
			{
				res++;
			}
			else
				wrapped_print(opt, tt, phil->pid, "is thinking");
		}
	}
	return (res);
}

void	*check_death(void *arg)
{
	t_opt	*opt;
	t_phil	*phil;
	t_llint	tt;

	phil = arg;
	opt = phil->opt;
	while (opt->alive)
	{
		tt = mtime();
		if (phil->last_eat < tt - opt->time_die)
		{
			pthread_mutex_lock(opt->print_m);
			if (opt->alive)
				printf("%lld %d %s\n", mtime() - opt->sim_start, phil->pid, "died");
			opt->alive = 0;
			phil->alive = 0;
			pthread_mutex_unlock(opt->print_m);
			if (phil->left)
				pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
			if (phil->right)
				pthread_mutex_unlock(opt->fork_m[phil->pid]);
		}
		usleep(1000);
		if (opt->eat_count >= 0 && phil->eat_count >= opt->eat_count)
			break ;
	}
	return (0);
}

void	*life(void *arg)
{
	t_opt	*opt;
	t_phil	*phil;

	phil = (t_phil *)arg;
	opt = phil->opt;
	phil->alive = 1;
	pthread_create(&phil->tid, NULL, &check_death, phil);
	while (opt->alive)
	{
		if (phil->stage == 0)
			stage_eat(opt, phil);
		else if (phil->stage == 1)
			stage_sleep(opt, phil);
		else if (stage_think(opt, phil))
			break ;
	}
	if (phil->left)
		pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	if (phil->right)
		pthread_mutex_unlock(opt->fork_m[phil->pid]);
	pthread_join(phil->tid, NULL);
	return (0);
}
