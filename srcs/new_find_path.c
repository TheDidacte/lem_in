
#include "lem_in.h"
// options with start and end

void	push_pq(t_pqs *pq, int id, int val)
{
	int		i;
	int		j;
	int		id_tmp;
	int		val_tmp;

	i = pq->cur + 1;
	while (pq->pq[i].val <= val && i < pq->end)
		i++;
	id_tmp = pq->pq[i].id;
	val_tmp = pq->pq[i].val;
	pq->pq[i].id = id;
	pq->pq[i].val = val;
	j = pq->end - 1;
	while (i < j)
	{
		pq->pq[j].id = pq->pq[j].id;	
		pq->pq[j].val = pq->pq[j].val;
		j--;
	}
	//printf("%i\n", i);
	if (i + 1 < g_len)
	{
		pq->pq[i + 1].id = id_tmp;
		pq->pq[i + 1].val = val_tmp;
	}	
}

void	find_p(int **flow, int **graph, int *a_path, int start, int end)
{
	t_pqs	pqs;
	int		*dist;
	int		i;
	int		u;

	if (!(dist = malloc(sizeof(int) * g_len)))
		return ;
	if (!(pqs.pq = malloc(sizeof(t_pq) * g_len)))
		return ;
	i = 0;
	while (i < g_len)
	{
		a_path[i] = -1;
		dist[i] = __INT_MAX__;
		i++;
	}
	dist[start] = 0;
	push_pq(&pqs, start, 0);
	while (pqs.cur < pqs.end)
	{
		while (1)
		{
			if (pqs.pq[pqs.cur].val == dist[pqs.cur])
				break ;
			
			//push_pq(&pqs, pqs.pq[pqs.cur].id, dist[pqs.cur]);
			pqs.cur++;
		}
		u = pqs.pq[pqs.cur].id;
		if (u == end)
			break ;
		i = 0;
		while (i < g_len)
		{
			if (!flow[u][i] && dist[u] + 1 < dist[i])
			{
				dist[i] = dist[u] + 1;
				a_path[i] = u;
				push_pq(&pqs, i, dist[i]);
			}
			if (flow[i][u] && dist[u] + 1 < dist[i])
			{
				dist[i] = dist[u] + 1;
				a_path[i] = u;
				push_pq(&pqs, i, dist[i]);
			}
			i++;
		}
		pqs.cur++;
	}
}

void	add_path(int **flow, int **graph, int *a_path, int start, int end)
{
	int		i;
	int		u;
	
	i = end;
	while (i != start)
	{
		u = a_path[i];
		if (graph[u][i])
			flow[u][i] = 1;
		else
			flow[i][u] = 1;				
		i = u;
	}	
}

int		is_in(int j, int *ar, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ar[i] == j)
			return (1);
		i++;
	}
	return (0);
}

void	init_graph(int ***flow, int ***graph, int **a_path, t_path **paths, int max)
{
	int		i;
	int		j;

	if (!(*flow = malloc(sizeof(int *) * g_len)))
		exit(1);
	if (!(*graph = malloc(sizeof(int *) * g_len)))
		exit(1);
	if (!(*a_path = malloc(sizeof(int *) * g_len)))
		exit(1);
	if (!(*paths = malloc(sizeof(t_path *) * max)))
		exit(1);
	i = 0;	
	while (i < g_len)
	{
		if (!(*flow[i] = malloc(sizeof(int) * g_len)))
			exit(1);
		if (!(*graph[i] = malloc(sizeof(int) * g_len)))
			exit(1);
		j = 0;
		while (j < g_len)
		{
			flow[i][j] = 0;
			graph[i][j] = is_in(j, g_vs[i]->links, g_vs[i]->n_links);
			j++;
		}	
		i++;
	}
}
void	save_state(t_path *paths, int t_flow)
{
	
}

t_path	**start_path_search(int start, int end, int max)
{
	int		**flow;
	int		**graph;
	int		*a_path;
	int		t_flow;
	t_path	*paths;

	init_graph(&flow, &graph, *a_path, &paths, max);
	t_flow = 0;
	while (t_flow < max)
	{
		find_p(flow, graph, a_path, start, end);
		if (a_path[end] == -1)
			break ;
		add_path(flow, graph, a_path, start, end);
		save_state(paths, t_flow);
		t_flow++;
	}
	return (paths);
}