/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <cpoirier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:04:05 by cpoirier          #+#    #+#             */
/*   Updated: 2018/11/14 11:26:22 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_found(const char *s1, const char *s2, size_t n)
{
	while (n-- && *s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	if (!*s2)
		return (1);
	return (0);
}

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	if (*s2 == '\0')
		return ((char*)s1);
	while (*s1 && n)
	{
		if (is_found(s1, s2, n))
			return ((char *)s1);
		++s1;
		--n;
	}
	return (NULL);
}
