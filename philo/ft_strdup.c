/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:24:40 by scilla            #+#    #+#             */
/*   Updated: 2021/07/15 17:24:41 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s1)
{
	char	*new;

	new = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + 1);
	if (new == 0)
		return (0);
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	return (new);
}
