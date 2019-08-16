/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 12:09:49 by cpoirier          #+#    #+#             */
/*   Updated: 2019/02/18 17:20:16 by skiessli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include "libft.h"

void		free_tab(char **t)
{
	char	**tmp;

	tmp = t;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(t);
}

void		print_anthill(void)
{
	ft_printf("\n\nANTHILL:\n");
	ft_printf("Number of ants: %4d\n", g_ants);
	ft_printf("Rooms: %d\n\n", g_len);
	for (int i = 0; i < g_len; i++)
	{
		ft_printf("Id: %16d\nName: %14s\n", g_vs[i]->id, g_vs[i]->name);
		ft_printf("Type: %14d\n", g_vs[i]->type);
		ft_printf("x: %17d\ny: %17d\n", g_vs[i]->x, g_vs[i]->y);
		ft_printf("Links: ");
		for (int k = 0; k < g_vs[i]->n_links; k++)
			ft_printf("%d, ", g_vs[i]->links[k]);
		ft_printf("\n\n");
	}
}

int			is_complete(int spe)
{
	return (spe == 3 && g_ants);
}

char		*parse_anthill(t_visual *visu)
{
	char		*s;
	int			special;
	char		*num;
	int			is_special;
	char		**tab;
	int			is_links;
	char		*ret;
	int			len;


	special = 0;
	is_special = 0;
	is_links = 0;
	ret = 0;
	while (get_next_line(0, &s) > 0)
	{
		printf("%s\n", s);
		num = s;
		if (!*s)
			break ;
		else if (*s == '#')
		{
			if (s[1] == '#')
			{
				if (g_ants && !ft_strncmp(s, "##start", len) && !(special % 2))
				{
					special++;
					is_special++;
				}
				else if (g_ants && !ft_strncmp(s, "##end", len) && special < 2)
				{
					special += 2;
					is_special += 2;
				}
				else
					break ;
			}
		}
		else if (*s == 'L')
		{
			break ;
		}
		else
		{
			tab = ft_strsplit(s, ' ');
			
			if (!*tab)
			{
				free_tab(tab);
				break ;
			}
			else if (!tab[1])
			{
				free_tab(tab);
				tab = ft_strsplit(s, '-');
				if (!*tab)
				{
					free_tab(tab);
					break ;
				}
				else if (!tab[1])
				{
					if (is_special || g_ants || !is_numeric(*tab) || !is_int(*tab))
					{
						free_tab(tab);
						break ;
					}
					g_ants = ft_atoi(*tab);
					free_tab(tab);
					if (!g_ants)
						break ;
				}
				else if (!tab[2])
				{
					if (!is_links)
					{
						init_all_links();
						is_links++;
					}
					if (is_special || !add_link(tab))
					{
						free_tab(tab);
						break ;
					}
				}
			}
			else if (!tab[2])
			{
				free_tab(tab);
				break ;
			}
			else if (g_ants && !tab[3])
			{
				if (is_links || !is_sign_numeric(tab[1])
						|| !is_sign_numeric(tab[2]) || !is_int(tab[1])
						|| !is_int(tab[2]) || !add_vertex(tab, is_special))
				{
					free_tab(tab);
					break ;
				}
				else
				{
					if (is_special == END)
						visu->end = g_len - 1;
					else if (is_special == START)
						visu->start = g_len - 1;
					is_special = 0;
				}
			}
			else
			{
				free_tab(tab);
				break ;
			}
		}
		len = ft_strlen(s);
		s[len] = '\n';
		if (!ft_strncat_join(&ret, s, len + 1))
			return (0);
		free(s);
	}
	free(s);
	if (!is_complete(special))
	{
		ft_printf("ERROR\n");
		return (0);
	}
	print_anthill();
	return (ret);
}
