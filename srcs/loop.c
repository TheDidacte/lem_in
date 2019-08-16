/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:48:06 by cpoirier          #+#    #+#             */
/*   Updated: 2019/02/15 13:48:24 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

int			loop(void *v)
{
	t_visual	*visu;

	visu = (t_visual *)v;
	if (!visu->pause)
	{
		clear_image(visu);
		if (visu->anim_frame == ANIM_COOL)
		{
			visu->anim_frame = 0;
			if (visu->frame < g_ope.best)
			{
				visu->frame++;
			}
		}
		else
			visu->anim_frame++;
		draw_graph(visu);
		if (visu->frame < g_ope.best)
			draw_ants(visu);
		render(visu);
	}
	return (0);
}
