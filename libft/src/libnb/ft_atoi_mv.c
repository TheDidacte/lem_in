/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <cpoirier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:33:19 by cpoirier          #+#    #+#             */
/*   Updated: 2019/01/22 15:34:19 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_mv(char **nptr)
{
	short int		sign;
	unsigned long	result;

	result = 0;
	sign = 1;
	while (**nptr == ' ' || **nptr == '\n' || **nptr == '\t'
		|| **nptr == '\f' || **nptr == '\v' || **nptr == '\r')
		++(*nptr);
	if (**nptr == '-' && ++(*nptr))
		sign = -1;
	else if (**nptr == '+')
		++(*nptr);
	while ('0' <= **nptr && **nptr <= '9')
		result = result * 10UL + ((unsigned long)*(*nptr)++ - 48UL);
	return ((int)result * sign);
}
