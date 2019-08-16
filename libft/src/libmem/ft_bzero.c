/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <cpoirier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:07:01 by cpoirier          #+#    #+#             */
/*   Updated: 2019/01/07 00:02:22 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > sizeof(long long))
	{
		n -= sizeof(long long);
		*(unsigned long long*)(ptr + n) = 0;
	}
	while (n > sizeof(short))
	{
		n -= sizeof(short);
		*(unsigned short*)(ptr + n) = 0;
	}
	if (n > 0)
	{
		--n;
		ptr[n] = '\0';
	}
}
