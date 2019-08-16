#include "lem_in.h"

t_int2			*get_screen_coord(t_visual *v, t_vertice *vert, t_int2 *coord)
{
	coord->y = WIN_OFF + (int)((double)(vert->y - v->y_off) / (double)v->y_width
				* (double)(HEIGHT - 2 * WIN_OFF));
	coord->x = WIN_OFF + (int)((double)(vert->x - v->x_off) / (double)v->x_width
				* (double)(WIDTH - 2 * WIN_OFF));
	return (coord);
}

void		draw_graph(t_visual *v)
{
	int		i;
	int		j;
	t_int2	p1;
	t_int2	p2;

	i = -1;
	while (++i < g_len)
	{
		j = -1;
		while (++j < g_vs[i]->n_links)
		{
			if (g_vs[i]->links[j] > i)
				draw_line(v, get_screen_coord(v, g_vs[i], &p1),
					get_screen_coord(v, g_vs[g_vs[i]->links[j]], &p2));
		}
		draw_circle(v, get_screen_coord(v, g_vs[i], &p1), 26, 0xCCCCCC);
		draw_circle(v, get_screen_coord(v, g_vs[i], &p1), 22, 0x666666);
	}
}
