/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <cpoirier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:48:00 by cpoirier          #+#    #+#             */
/*   Updated: 2018/11/06 15:04:47 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*str;
	void	*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	str = (char *)mem;
	while (size-- > 0)
	{
		*str++ = 0;
	}
	return (mem);
}
