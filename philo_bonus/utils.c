/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:26:03 by scilla            #+#    #+#             */
/*   Updated: 2021/07/15 17:26:03 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_llint	mtime(void)
{
	t_time	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(t_llint msec)
{
	usleep(msec * 1000);
}

void	msleep_till(t_llint msec)
{
	t_llint	delta;

	delta = msec - mtime();
	if (delta > 0)
		msleep(delta);
}
