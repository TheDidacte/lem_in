/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <cpoirier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:22:20 by cpoirier          #+#    #+#             */
/*   Updated: 2018/11/06 15:16:18 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*result;

	result = dest;
	while (*dest != '\0')
		++dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
