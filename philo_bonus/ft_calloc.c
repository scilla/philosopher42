/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:25:27 by scilla            #+#    #+#             */
/*   Updated: 2021/07/15 17:25:29 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*new;
	unsigned int	i;

	new = malloc(size * count);
	if (!new)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		*(new + i) = 0;
		i++;
	}
	return (new);
}
