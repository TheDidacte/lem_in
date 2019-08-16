/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiessli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:09:56 by skiessli          #+#    #+#             */
/*   Updated: 2019/03/10 17:23:48 by skiessli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int		g_another;
int		g_qlen;

void	init_bfs(int **from, t_pq **q, int **hide)
{
	int		i;

	if (!(*from = malloc(sizeof(int) * g_len)))
		exit(1);
	if (!(*q = malloc(sizeof(t_pq) * g_qlen)))
		exit(1);
	if (!(*hide = malloc(sizeof(int) * g_len)))
		exit(1);
	i = 0;
	while (i < g_len)
	{
		(*from)[i] = -1;
		(*q)[i].id = -1;
		(*hide)[i] = g_len + 1;
		i++;
	}
}

void	insert_in_q(t_pq *q, int id, int cur, int tot, int val)
{
	int		i;
	int		id_tmp;
	int		val_tmp;
	int		ret;

	i = cur + 1;
	while (q[i].val <= val && i < tot)
		i++;
	id_tmp = q[i].id;
	val_tmp = q[i].val;
	q[i].id = id;
	q[i].val = val;
	while (i < tot)
	{
		q[tot].id = q[tot - 1].id;	
		q[tot].val = q[tot - 1].val;
		tot--;
	}
	//printf("%i\n", i);
	if (i + 1 < g_qlen)
	{
		q[i + 1].id = id_tmp;
		q[i + 1].val = val_tmp;
	}
}

int		add_to_queue(int *from, t_pq *q, int *hide, int tot, int cur)
{
	int			i;
	t_vertice	*v;
	t_vertice	*v_i;

	//hide[q[cur]] = 1;
	v = g_vs[q[cur].id];
	//if (v->rev >= 0)
	if(v->in_path != -1)
	{		v_i = g_vs[v->rev];
			//dprintf(2, "\tadd rev: cur: %s in_path: %i tot: %i hidden: %i\n",
			//v_i->name, v_i->in_path, tot, hide[v_i->id]);
	
	}
	if (v->in_path != -1 && v->rev >= 0 && q[cur].val - 1 < hide[v->rev])
	{
		v_i = g_vs[v->rev];
		from[v_i->id] = q[cur].id;
		//q[tot] = v_i->id;
		insert_in_q(q, v_i->id, cur, tot, q[cur].val - 1);
		tot++;
		hide[v_i->id] = q[cur].val - 1;

	}
	i = 0;
	while (i < g_vs[q[cur].id]->n_links)
	{
		v_i = g_vs[v->links[i]];
		//dprintf(2, "\tadd: cur: %s in_path: %i tot: %i hidden: %i \n", v_i->name, v_i->in_path, tot, hide[v_i->id]);
		if (q[cur].val + 1 < hide[v_i->id] && v_i->in_path == -1)
		{
			//dprintf(2, "\t\t normal: cur: %s in_path: %i tot: %i hidden: %i \n", v_i->name, v_i->in_path, tot, hide[v_i->id]);
			from[v_i->id] = q[cur].id;
			//q[tot].id = v_i->id;
			insert_in_q(q, v_i->id, cur, tot, q[cur].val + 1);
			tot++;
			hide[v_i->id] = q[cur].val + 1;
		}
		else if (q[cur].val < hide[v_i->id] && v_i->in_path != -1 && v->in_path != v_i->in_path)
		{
			//hide[v_i->id] = 1;
			//from[v_i->id] = q[cur].id;
			//dprintf(2, "\t\tstep back: cur: %s in_path: %i rev: %i, tot: %i hidden: %i\n", v_i->name, v_i->in_path, v_i->rev, tot, hide[v_i->id]);
			v_i = g_vs[v_i->rev];
			if (q[cur].val < hide[v_i->id])
			{
				from[v_i->id] = q[cur].id;
				//q[tot] = v_i->id;
				insert_in_q(q, v_i->id, cur, tot, q[cur].val);
				tot++;
				hide[v_i->id] = q[cur].val;
			}
		}
		//dprintf(2, "\tafter add: cur: %s in_path: %i tot: %i\n", v_i->name, v_i->in_path, tot);
		i++;
	}
	return (tot);
}

void	print_all_shit()
{
	int 	i = 0;

	while (i < g_len)
	{
			
		dprintf(2, "%s in_path: %i\n", g_vs[i]->name, g_vs[i]->in_path);
		i++;
	}
}

void	print_tmp(int *tmp, int len)
{
	int i = 0;
	dprintf(2, "tmp: %i\n", len);
	while (i < len)
	{
		dprintf(2, "%s ", g_vs[tmp[i]]->name);
		i++;
	}
	dprintf(2, "\nendtmp\n");
}

void	print_cur_path(int cur, int *from)
{
	while(cur >= 0)
	{
		dprintf(2, "%s in_path: %i, ", g_vs[cur]->name, g_vs[cur]->in_path);
		cur = from[cur];
	}
	dprintf(2, "\n");
}

int		split_path(t_path *ret, int *from, int cur)
{
	int		*tmp;
	int		len;
	int		path;
	// malloc new new path
	if (!(tmp = malloc(sizeof(int) * g_len)))
		exit(1);
	// copy of old path to new new path
	//print_all_shit();
	path = g_vs[cur]->in_path;
	dprintf(2, "cur: %s g_vs[cur]->in_path: %i ret->cur: %i ret->len[path]: %i\n",
			g_vs[cur]->name, g_vs[cur]->in_path, ret->cur, ret->len[path]);
	print(ret);

	len = 0;
	while (ret->ps[path][ret->len[path] - 1] != cur)
	{
		ret->len[path]--;
		tmp[len] = ret->ps[path][ret->len[path]];
		if (g_vs[ret->ps[path][ret->len[path]]]->type != END)
			g_vs[ret->ps[path][ret->len[path]]]->in_path = ret->cur;
		len++;
	}
	dprintf(2, "\nafter old to new new\n");
	print(ret);
	print_tmp(tmp, len);
	// copy of new path to old path
	while (ret->len[ret->cur] > 0)
	{
		//dprintf(2, "%i\n", ret->len[ret->cur]);
		ret->len[ret->cur]--;
		ret->ps[path][ret->len[path]] = ret->ps[ret->cur][ret->len[ret->cur]];
		if (g_vs[ret->ps[ret->cur][ret->len[ret->cur]]]->type != END)
			g_vs[ret->ps[ret->cur][ret->len[ret->cur]]]->in_path = path;
		ret->len[path]++;
	}
	dprintf(2, "\nafter new to old\n");
	print(ret);
	print_tmp(tmp, len);
	// free new path
	free(ret->ps[ret->cur]);
	// copy address of new new path to new path
	ret->ps[ret->cur] = tmp;
	ret->len[ret->cur] = len;
	// remove additional
	dprintf(2, "\nafter free \n");
	print(ret);
	print_cur_path(cur, from);
	while (g_vs[from[cur]]->in_path == path)
	{
		dprintf(2, "remove: %s\n", g_vs[cur]->name);
		ret->len[ret->cur]--;
		g_vs[cur]->in_path = -1;
		cur = from[cur];	
	}
	dprintf(2, "\ndone split_path\n");
	print(ret);
	//print_tmp(tmp, len);
	dprintf(2, "\n");
	dprintf(2, "mark: %s\n", g_vs[cur]->name);
	//if (g_vs[cur]->type != END)	
	//	g_vs[cur]->in_path = ret->cur;
	return (from[cur]);
}

int		create_path(t_path *ret, int *from, int cur, int start)
{
	int		i;
	int		tmp;

	while (cur != start)
	{
		dprintf(2, "cur: %s in_path: %i\n", g_vs[cur]->name, g_vs[cur]->in_path);
		if (g_vs[cur]->in_path != -1)
		{
			cur = split_path(ret, from, cur);
		}
		else
		{
			ret->ps[ret->cur][ret->len[ret->cur]] = cur;
			ret->len[ret->cur]++;
			if (g_vs[cur]->type != END)
				g_vs[cur]->in_path = ret->cur;
			g_vs[cur]->rev = from[cur];
			cur = from[cur];
		}
	}
	i = 0;
	while (i < ret->len[ret->cur] / 2)
	{
		tmp = ret->ps[ret->cur][i];
		ret->ps[ret->cur][i] = ret->ps[ret->cur][ret->len[ret->cur] - i - 1];
		ret->ps[ret->cur][ret->len[ret->cur] - i - 1] = tmp;
		i++;
	}
	return (1);
}

int		bfs(int start, t_path *ret)
{
	int		*from;
	t_pq	*q;
	int		cur;
	int		tot;
	int		*hide;
	int		changed;

	init_bfs(&from, &q, &hide);
	q[0].id = start;
	q[0].val = 0;
	hide[start] = 0;
	cur = 0;
	tot = 1;
	changed = 0;
	g_another = 1;
	while (ret->cur < ret->count)// && cur < tot)
	{
		//dprintf(2, "ret->cur: %i, ret->count: %i, cur: %i, tot: %i, q[cur]: %i",
		//		ret->cur, ret->count, cur, tot, q[cur].id);
		//dprintf(2, ", name: %s\n",
		//		g_vs[q[cur].id]->name);
		if (cur == tot)
		{
			if (!changed)
				break ;
			tot = g_len;
			while (tot > 0)
			{
				tot--;
				hide[tot] = 0;
			}
			hide[start] = 1;
			cur = 0;
			tot = 1;
			changed = 0;
			//dprintf(2, "another round\n");
		}
		else if (g_vs[q[cur].id]->type == END)
		{
			create_path(ret, from, q[cur].id, start);
			ret->cur++;
			tot = g_len;
			while (tot > 0)
			{
				tot--;
				hide[tot] = g_len + 1;
			}
			hide[start] = 0;
			cur = 0;
			tot = 1;
			//dprintf(2, "found path\n");
			//changed = 1;
		}
		
	/*	if (g_vs[q[cur]]->type == END)
		{
			create_path(ret, from, q[cur], start);
			ret->count = 2;
			tot = g_len;
			while (tot > 0)
			{
				tot--;
				hide[tot] = 0;
			}
			hide[start] = 1;
			cur = 0;
			tot = 1;
		}//*/
		else
		{
			tot = add_to_queue(from, q, hide, tot, cur);	
			cur++;
		}
	}
	//dprintf("found path with: %i wanted %i", ret->cur, ret->count);
	if (ret->cur == ret->count)
		return (1);
	return (0);
}

t_path	*init_path(int count)
{
	t_path	*p;

	if (!(p = malloc(sizeof(t_path))))
		exit(1);
	p->cur = 0;
	p->count = count;
	if (!(p->ps = malloc(sizeof(int *) * count)))
		exit(1);
	if (!(p->len = malloc(sizeof(int) * count)))
		exit(1);
	count--;
	while (count >= 0)
	{
		if (!(p->ps[count] = malloc(sizeof(int) * g_len)))
			exit(1);
		p->len[count] = 0;
		count--;
	}
	count = 0;
	while (count < g_len)
	{
		g_vs[count]->in_path = -1;
		g_vs[count]->rev = -1;
		count++;
	}
	return (p);
}

void	free_path(t_path *p)
{
	int		i;

	i = 0;
	while (i < p->count)
	{
		free(p->ps[i]);
		i++;
	}
	free(p->ps);
	free(p);
}
t_path	*find_path(int start, int end, int max)
{
	int		count;
	t_path	*ret;

	count = g_vs[start]->n_links < g_vs[end]->n_links
				? g_vs[start]->n_links : g_vs[end]->n_links;
	count = max < count ? max : count;
	dprintf(2, "count: %i\n", count);
	g_qlen = 10 * g_len;
	while (count > 0)
	{
		ret = init_path(count);
		//dprintf(2, "before bfs\n");
		if (bfs(start, ret))
			return (ret);
		count--;
		free_path(ret);
		//dprintf(2, "\n");
	}
	//ret->count = count;
	return (0);
}

