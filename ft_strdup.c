/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:27:06 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

char	*ft_strdup(const char *s1)
{
	char	*new;

	new = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + 1);
	if (new == 0)
		return (0);
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	return (new);
}
