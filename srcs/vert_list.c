/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiessli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:44:20 by skiessli          #+#    #+#             */
/*   Updated: 2019/02/07 16:28:32 by skiessli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

t_vert_list	*init_v_list(t_vertice *v)
{
	t_vert_list	*n;

	if (!(n = malloc(sizeof(t_vert_list))))
		exit(1);
	n->v = v;
	n->n = 0;
	return (n);
}

void		add_to_end(t_vert_list *q, t_vert_list *n)
{
	while (q->n)
		q = q->n;
	q->n = n;
}
