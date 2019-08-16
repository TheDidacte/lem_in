/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:55:33 by cpoirier          #+#    #+#             */
/*   Updated: 2019/03/08 16:21:44 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "lem_in.h"
#include "libft.h"
#include <stdlib.h>

void		print_graph(void)
{
	for (int k = 0; k < g_len; k++)
	{
		printf("Node named %s, id %d :\n", g_vs[k]->name, g_vs[k]->id);
		for (int l = 0; l < g_vs[k]->n_links; l++)
			printf("%s %d, ", g_vs[g_vs[k]->links[l]]->name, g_vs[g_vs[k]->links[l]]->id);
		printf("\n");
	}
}

void		init_new_node(int k)
{
	char	*name;

	name = ft_strnew(ft_strlen(g_vs[k]->name) + 4);
	if (!(g_vs[g_len] = (t_vertice *)malloc(sizeof(t_vertice))))
		exit(1);
	g_vs[g_len]->id = g_len;
	printf("Copy that\n");
	ft_strcpy(name, g_vs[k]->name);
	g_vs[g_len]->name = ft_strcat(name, "_out");
	if (!(g_vs[g_len]->links = (int *)malloc(sizeof(int) * g_len)))
		exit(1);
	g_vs[g_len]->n_links = 0;
	g_vs[g_len]->rev = -1;
	g_vs[g_len]->type = 0;
	g_vs[g_len]->x = 0;
	g_vs[g_len]->y = 0;
	g_vs[g_len]->in_path = 0;
}

void		convert_to_edges(void)
{
	int		i;
	int		l;
	int		initial_len;

	print_graph();
	initial_len = g_len;
	i = -1;
	while (++i < initial_len)
	{
		if (!g_vs[i]->type)
		{
			init_new_node(i);
			l = -1;
			while (++l < g_vs[i]->n_links)
			{
				g_vs[g_len]->links[g_vs[g_len]->n_links] = g_vs[i]->links[l];
				g_vs[g_len]->n_links++;
			}
			g_vs[i]->links[0] = g_len;
			g_vs[i]->n_links = 1;
			g_len++;
		}
	}
	print_graph();
}
