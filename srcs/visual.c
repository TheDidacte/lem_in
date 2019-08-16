#include <lem_in.h>
#include "mlx.h"

void		init_bounds(t_visual *v)
{
	int		i;

	i = 0;
	v->x_off = g_vs[0]->x;
	v->y_off = g_vs[0]->y;
	while (++i < g_len)
	{
		if (g_vs[i]->x < v->x_off)
			v->x_off = g_vs[i]->x;
		if (g_vs[i]->y < v->y_off)
			v->y_off = g_vs[i]->y;
	}
	v->x_width = 0;
	v->y_width = 0;
	i = 0;
	while (++i < g_len)
	{
		if (g_vs[i]->x - v->x_off > v->x_width)
			v->x_width = g_vs[i]->x - v->x_off;
		if (g_vs[i]->y - v->y_off > v->y_width)
			v->y_width = g_vs[i]->y - v->y_off;
	}
}

int			get_start_index(void)
{
	int		i;

	i = 0;
	while (i < g_len)
	{
		if (g_vs[i]->type == START)
			return (i);
		i++;
	}
	return (0);
}

void		init_visual(t_visual *v)
{
	if (!(v->mlx = mlx_init()))
		exit(1);
	if (!(v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "lem_in visualizer")))
		exit(1);
	if (!(v->img = mlx_new_image(v->mlx, WIDTH, HEIGHT)))
		exit(1);
	v->img_addr = mlx_get_data_addr(v->img, &v->bpp, &v->s_l, &v->endian);
	v->frame = 0;
	v->anim_frame = 0;
	v->pause = 0;
	init_bounds(v);
}
