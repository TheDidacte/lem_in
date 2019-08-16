/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:45:42 by cpoirier          #+#    #+#             */
/*   Updated: 2019/02/13 13:44:22 by skiessli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include <stdlib.h>

int			index_of(char *s)
{
	int		i;

	i = 0;
	while (i < g_len)
	{
		if (!ft_strcmp(s, g_vs[i]->name))
			return (i);
		i++;
	}
	return (-1);
}

int			same_coord(char **t)
{
	int		i;

	i = 0;
	while (i < g_len)
	{
		if (g_vs[i]->x == ft_atoi(t[1]) && g_vs[i]->y == ft_atoi(t[2]))
			return (1);
		i++;
	}
	return (0);
}

int			add_link(char **t)
{
	int		v1;
	int		v2;
	int		i;

	v1 = index_of(t[0]);
	v2 = index_of(t[1]);
	if (v1 < 0 || v2 < 0)
		return (0);
	i = -1;
	while (++i < g_vs[v1]->n_links)
	{
		if (g_vs[v1]->links[i] == v2)
			return (0);
	}
	g_vs[v1]->links[g_vs[v1]->n_links] = v2;
	g_vs[v1]->n_links++;
	g_vs[v2]->links[g_vs[v2]->n_links] = v1;
	g_vs[v2]->n_links++;
	free_tab(t);
	return (1);
}

void		init_all_links(void)
{
	int		i;

	i = -1;
	while (++i < g_len)
		if (!(g_vs[i]->links = (int *)malloc(sizeof(int) * (g_len - 1))))
			exit(1);
}

t_vertice	*init_vertex(char **t, int special)
{
	t_vertice	*res;

	if (!(res = (t_vertice *)malloc(sizeof(t_vertice))))
		exit(1);
	res->id = g_len;
	res->name = ft_strdup(*t);
	res->x = ft_atoi(t[1]);
	res->y = ft_atoi(t[2]);
	res->n_links = 0;
	res->type = special;
	res->in_path = 0;
	res->rev = -1;
	return (res);
}

int			add_vertex(char **t, int special)
{
	if (index_of(*t) > -1 || same_coord(t))
		return (0);
	// Need to be as long as possible
	g_vs[g_len] = init_vertex(t, special);
	g_len++;
	free_tab(t);
	return (1);
}
