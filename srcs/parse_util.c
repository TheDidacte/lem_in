/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 12:24:47 by cpoirier          #+#    #+#             */
/*   Updated: 2019/02/09 14:37:50 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			is_int(char *s)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		sign = *s == '-' ? -1 : 1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (res > res * 10 + *s - '0')
		{
			if (res * 10 + *s - '0' - 1 == 2147483647 && sign < 0 && (s[1] < '0'
						|| s[1] > '9'))
				return (1);
			return (0);
		}
		res = res * 10 + *s - '0';
		s++;
	}
	return (1);
}

int			is_numeric(char *s)
{
	while (*s)
	{
		if ((*s < '0' || *s > '9'))
			return (0);
		s++;
	}
	return (1);
}

int			is_sign_numeric(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

char		*get_next_num(char *s)
{
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
		s++;
	while (*s == ' ')
		s++;
	return (s);
}
