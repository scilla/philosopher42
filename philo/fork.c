/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:23:48 by scilla            #+#    #+#             */
/*   Updated: 2021/07/20 16:37:18 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	get_forks(t_opt *opt, t_phil *phil)
{
	int	res;

	res = 1;
	pthread_mutex_lock(opt->fork_m[phil->pid - 1]);
	phil->left = 1;
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	pthread_mutex_lock(opt->fork_m[phil->pid]);
	phil->right = 1;
	wrapped_print(opt, mtime(), phil->pid, "has taken a fork");
	return (res);
}

void	drop_forks(t_opt *opt, t_phil *phil)
{
	*opt->forks[phil->pid - 1] = 0;
	*opt->forks[phil->pid] = 0;
	pthread_mutex_unlock(opt->fork_m[phil->pid - 1]);
	phil->left = 0;
	pthread_mutex_unlock(opt->fork_m[phil->pid]);
	phil->right = 0;
}
