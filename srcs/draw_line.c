#include "lem_in.h"
#include "mlx.h"

void		render(t_visual *v)
{
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}

void		draw_circle(t_visual *v, t_int2 *p, int r, int col)
{
	int		i;
	int		j;
	int		r2;

	i = 0;
	r2 = r * r;
	while (i < 2 * r)
	{
		j = 0;
		while (j < 2 * r)
		{
			if ((i - r) * (i - r) + (j - r) * (j - r) < r2)
				*(int *)(v->img_addr + (p->x + i - r) * v->bpp / 8 + (p->y + j
							- r) * v->s_l) = col;
			j++;
		}
		i++;
	}
}

void		draw_line(t_visual *v, t_int2 *p1, t_int2 *p2)
{
	int		tabx[2];
	int		taby[2];
	int		e[2];

	tabx[0] = abs(p2->x - p1->x);
	tabx[1] = p1->x < p2->x ? 1 : -1;
	taby[0] = abs(p2->y - p1->y);
	taby[1] = p1->y < p2->y ? 1 : -1;
	e[0] = (tabx[0] > taby[0] ? tabx[0] : -taby[0]) / 2;
	while (p1->x != p2->x || p1->y != p2->y)
	{
		*(int *)(v->img_addr + p1->x * v->bpp / 8 + p1->y * v->s_l) = 0xFFFFFF;
		e[1] = e[0];
		e[1] > -tabx[0] ? e[0] -= taby[0] : 1 == 1;
		e[1] > -tabx[0] ? p1->x += tabx[1] : 1 == 1;
		e[1] < taby[0] ? e[0] += tabx[0] : 1 == 1;
		e[1] < taby[0] ? p1->y += taby[1] : 1 == 1;
	}
}

//void	draw_ant(t_visual *v, t_int
