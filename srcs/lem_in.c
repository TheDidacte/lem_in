/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:10:14 by cpoirier          #+#    #+#             */
/*   Updated: 2019/03/10 16:18:46 by skiessli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

t_vertice	**g_vs;
int			g_len;
int			g_ants;
t_ope		g_ope;

int			main(void)
{
	t_visual	visu;
	t_path		*p;
	char		*ret;

	g_ants = 0;
	g_len = 0;
	if (!(g_vs = (t_vertice **)malloc(sizeof(t_vertice *) * 11000)))
		exit (1);
	if ((ret = parse_anthill(&visu)))
	{
	//	convert_to_edges()
		printf("done with parsing\n");;
		print_path(visu.start, visu.end, ret);
	}

//	p = find_path(visu.start, visu.end, g_ants);
//	print(p);
	
	
	init_visual(&visu);
	draw_graph(&visu);
	render(&visu);
	mlx_hook(visu.win, 2, 0, on_key_hook, &visu);
	mlx_loop_hook(visu.mlx, loop, &visu);
	mlx_loop(visu.mlx);
	

	return (0);
}
