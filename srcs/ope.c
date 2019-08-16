/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:35:14 by cpoirier          #+#    #+#             */
/*   Updated: 2019/02/14 15:24:11 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void			init_ope(t_ope *ope)
{
	int		i;
	int		j;

	if (!(ope->ope = (int ***)malloc(sizeof(int **) * (1 + ope->best))))
		exit(1);
	ope->len = 0;
	ope->current_ope = 0;
	i = 0;
	while (i < (1 + ope->best))
	{
		j = 0;
		if (!(ope->ope[i] = (int **)malloc(sizeof(int *) * (g_ants + 1))))
				exit(1);
		while (j < g_ants + 1)
		{
			if (!(ope->ope[i][j] = (int *)malloc(sizeof(int) * 2)))
				exit(1);
			j++;

		}
		i++;		
	}
}

void			add_to_ope(t_ope *ope, int a, int b)
{
	ope->ope[ope->len][ope->current_ope][0] = a;
	ope->ope[ope->len][ope->current_ope][1] = b;
	ope->current_ope++;
}
