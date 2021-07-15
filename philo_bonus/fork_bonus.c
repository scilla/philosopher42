/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:25:20 by scilla            #+#    #+#             */
/*   Updated: 2021/07/15 17:25:21 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

void	*get_forks(void *arg)
{
	t_phil	*phil;
	t_opt	*opt;

	phil = arg;
	opt = phil->opt;
	sem_wait(opt->sem);
	sem_wait(opt->sem);
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	phil->has_forks = 1;
	phil->checking = 0;
	return (0);
}

void	drop_forks(t_opt *opt, t_phil *phil)
{
	(void)phil;
	sem_post(opt->sem);
	sem_post(opt->sem);
}
