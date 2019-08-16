/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <cpoirier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:55:47 by cpoirier          #+#    #+#             */
/*   Updated: 2018/11/06 15:20:09 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	while ((next = (*alst)->next))
	{
		ft_lstdelone(&*alst, del);
		free(*alst);
		*alst = next;
	}
	ft_lstdelone(&*alst, del);
	free(*alst);
	*alst = NULL;
}
