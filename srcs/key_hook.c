/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:02:39 by cpoirier          #+#    #+#             */
/*   Updated: 2019/02/15 13:49:17 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

void		draw_rect(t_visual *visu, t_rect *rect, int col)
{
	int		i;
	int		j;

	i = 0;
	while (i < rect->width)
	{
		j = 0;
		while (j < rect->height)
		{
			if ((rect->x + i) * visu->bpp / 8 + (rect->y + j) * visu->s_l
					< WIDTH * HEIGHT * visu->bpp / 8)
				*(int *)(visu->img_addr + (rect->x + i) * visu->bpp / 8
						+ (rect->y + j) * visu->s_l) = col;
			j++;
		}
		i++;
	}
}

void		clear_image(t_visual *v)
{
	mlx_destroy_image(v->mlx, v->img);
	if (!(v->img = mlx_new_image(v->mlx, WIDTH, HEIGHT)))
		exit(1);
	v->img_addr = mlx_get_data_addr(v->img, &v->bpp, &v->s_l, &v->endian);
}

void		draw_ants(t_visual *v)
{
	int		i;
	t_int2	p1;
	t_int2	p2;
	double	delta;

	i = 0;
	while (g_ope.ope[v->frame][i])
	{
		get_screen_coord(v, g_vs[g_ope.ope[v->frame][i][0]], &p1);
		get_screen_coord(v, g_vs[g_ope.ope[v->frame][i][1]], &p2);
		delta = (double)v->anim_frame / (double)ANIM_COOL;
		p1.x = (1. - delta) * (double)p1.x + delta * (double)p2.x;
		p1.y = (1. - delta) * (double)p1.y + delta * (double)p2.y;
		draw_circle(v, &((t_int2){p1.x, p1.y}), 17, 0xA04504);
		//draw_rect(v, &((t_rect){p1.x - 10, p1.y - 10, 20, 20}), 0xFFFFFF);
		i++;
	}
}

int			on_key_hook(int key, void *v)
{
	t_visual	*visu;

	visu = (t_visual *)v;
	clear_image(visu);
	if (key == 53)
		exit(1);
	else if (key == 49)
		visu->pause = !visu->pause;
	else if (key == 124)
	{
		if (visu->frame < g_ope.best)
			visu->frame++;
	}
	else if (key == 123)
	{
		if (visu->frame)
			visu->frame--;
	}
	draw_graph(visu);
	if (visu->frame < g_ope.best)
	draw_ants(visu);
	render(visu);
	return (0);
}
