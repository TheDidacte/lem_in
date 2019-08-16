/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiessli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:12:34 by skiessli          #+#    #+#             */
/*   Updated: 2019/03/10 17:22:51 by skiessli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print(t_path *p)
{
	int		i;
	int		j;

	i = 0;
	dprintf(2, "count: %i\n", p->count);
	while (i < p->count)
	{
		j = 0;
		dprintf(2, "len [%i]: %i \n", i,  p->len[i]);
		while (j < p->len[i])
		{
			dprintf(2, "%s ", g_vs[p->ps[i][j]]->name);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
}

void	sort_path(t_path *p)
{
	int		i;
	int		tmp_n;
	int		*tmp_ar;
	// sort path asceding according to path length
	i = 0;
	while (i < p->count - 1)
	{
		if (p->len[i] > p->len[i + 1])
		{
			tmp_n = p->len[i + 1];
			p->len[i + 1] = p->len[i];
			p->len[i] = tmp_n;
			tmp_ar = p->ps[i + 1];
			p->ps[i + 1] = p->ps[i];
			p->ps[i] = tmp_ar;
			i = 0;
		}
		else
			i++;
	}
}

void	fill_opt_path(t_path *p, int *a_path, int opt, int best)
{
	int		ants;
	int		cur;
	int		i;

	ants = g_ants;
	cur = 0;
	//dprintf(2, "opt: %i best: %i\n", opt, best);
	while (cur < g_ants)
	{
		i = 0;
		//dprintf(2, "opt: %i best: %i\n", cur, best);
		while (i < opt && cur < g_ants)
		{
			a_path[cur] = i;
			i++;
			cur++;
		}
		best--;
		i = 0;
		while (i < opt)
		{
			if (p->len[i] > best)
				break ;
			i++;
		}
		opt = i;
	}
}

void	print_opt(t_path *p, int opt, int best)
{
	int		*a_pos;
	int		*a_path;
	int		i;
	int		cur;
	int		done;

	int		steps;

	if (!(a_pos = malloc(sizeof(int) * g_ants)))
		exit(1);
	if (!(a_path = malloc(sizeof(int) * g_ants)))
		exit(1);
	i = 0;
	//dprintf(2, "in print_opt\n");
	//dprintf(2, "opt: %i best: %i\n", opt, best);
	while (i < g_ants)
	{
		a_pos[i] = 0;
		i++;
	}
	fill_opt_path(p, a_path, opt, best);
	cur = opt;
	done = 0;

	steps = 0;

	g_ope.best = best;
	init_ope(&g_ope);

	while (done < g_ants)
	{
		i = done;
		//dprintf(2, "done: %i cur: %i opt: %i\n", done, cur, opt);
		while (i < cur)
		{
			//dprintf(2, "%i: %i p->len[i %% opt]: %i ", 
			//		i, ants[i], p->len[i % opt]);
			if (a_pos[i] < p->len[a_path[i]]) // choose path
			{
				if (a_pos[i])
					add_to_ope(&g_ope, p->ps[a_path[i]][a_pos[i] - 1], p->ps[a_path[i]][a_pos[i]]);
				else
					add_to_ope(&g_ope, get_start_index(), p->ps[a_path[i]][a_pos[i]]);
				printf("L%i-%s%*s", i + 1, 
					g_vs[p->ps[a_path[i]][a_pos[i]]]->name, i + 1 < cur, "");
				a_pos[i]++;
			}
			else if (done == i)
				done++;
			i++;
		}
		if (done < g_ants)
		{
			//dprintf(2, "My current frame: %d\n", g_ope.current_ope);
			g_ope.ope[g_ope.len][g_ope.current_ope] = 0;
			g_ope.len++;
			g_ope.current_ope = 0;
			printf("\n");
			steps++;
		}
		//dprintf(2, "cur: %i opt: %i g_ants: %i\n", cur, opt, g_ants);
		while (cur < g_ants)
			if (++cur < g_ants && a_path[cur] == 0)
				break ;
		//cur = cur + opt < g_ants ? cur + opt : g_ants;
	}
	dprintf(1, "steps: %i\n", steps);
}

int		find_optimal(t_path **paths, int len)
{
	int		i;
	int		best;
	int		opt;
	int		c_ants;
	int		c_best;
	int		j;

	i = 1;
	opt = -1;
	best = 0;
	//dprintf(2, "len: %i\n", len);
	while (i <= len)
	{
		//dprintf(2, "in\n");
		c_ants = g_ants - i;
		j = 0;
		while (j < i)
		{
			//dprintf(2, "big: %i small: %i\n",
			//		paths[i]->len[i - 1], paths[i]->len[j]);
			c_ants -= (paths[i]->len[i - 1] - paths[i]->len[j]);
			j++;
		}
		c_best = paths[i]->len[i - 1];
		while (c_ants > 0)
		{
			c_ants -= i;
			c_best += 1;
		}
		dprintf(2, "opt: %i i: %i best: %i c_best: %i\n",
				opt, i, best, c_best);
		if (opt == -1 || c_best < best)
		{
			best = c_best;
			opt = i;
		}
		i++;
	}
	//dprintf(2, "g_ants: %i len: %i opt: %i best: %i\n", g_ants, len, opt, best);
	//print(paths[opt]);
	print_opt(paths[opt], opt, best);
	return (opt);
}

void	print_path(int start, int end, char *ret)
{
	t_path	*p;
	t_path	**paths;
	int		len;
	int		opt;
	// get pats
	//dprintf(2, "in first path\n");
	p = find_path(start, end, g_ants);
	//print(p);
	if (!p)
	{
		dprintf(2, "No paths found\n");
		return ;
	}
	sort_path(p);
	//dprintf(2, "first path done\n");
	len = p->count;
	if (!(paths = malloc(sizeof(t_path *) * (len + 1))))
		exit(1);
	paths[len] = p;
	dprintf(2, "max nb paths: %i\n", len);
	while (--len > 0)
	{
		//dprintf(2, "%i path beg\n", len);
		paths[len] = find_path(start, end, len);
		//print(paths[len]);
		sort_path(paths[len]);
	}
	//dprintf(2, "all path done\n");
	len = p->count;

	if (len > 0)
	{
		ft_putstr(ret);
		ft_putchar('\n');
		opt = find_optimal(paths, len);
	}
	else
		printf("ERROR\n");
	
	//opt = 0;
	//while (++opt <= p->count)
	//	print(paths[opt]);

	// find minimum lines
	// print path
}
