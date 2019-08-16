/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:09:53 by cpoirier          #+#    #+#             */
/*   Updated: 2019/03/08 15:19:16 by cpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define	NORMAL 0
# define	START  1
# define	END    2

# define	WIDTH  1000
# define	HEIGHT 1000
# define	WIN_OFF 50

# define ANIM_COOL 50

typedef struct		s_vertice
{
	int					id;
	char				*name;
	int					*links;
	int					n_links;
	int					rev;
	int					type;
	int					x;
	int					y;
	int					in_path;
}					t_vertice;

typedef	struct		s_int2
{
	int				x;
	int				y;
}					t_int2;

typedef struct		s_vert_list
{
	t_vertice			*v;
	struct s_vert_list	*n;
}					t_vert_list;

typedef struct		s_path
{
	int				count;
	int				cur;
	int				*len;
	int				**ps;
}					t_path;

typedef	struct		s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
}					t_rect;

typedef	struct		s_ope
{
	int				***ope;
	int				len;
	int				current_ope;
	int				best;
}					t_ope;

typedef	struct		s_visual
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_addr;
	int				bpp;
	int				s_l;
	int				endian;
	int				x_off;
	int				y_off;
	int				x_width;
	int				y_width;
	int				start;
	int				end;
	int				frame;
	int				anim_frame;
	int				pause;
}					t_visual;

typedef struct		s_pq
{
	int				id;
	int				val;
}					t_pq;

typedef struct		s_pqs
{
	int				cur;
	int				end;
	t_pq			*pq;
}					t_pqs;

extern	t_vertice	**g_vs;
extern	int			g_len;
extern	int			g_ants;
extern	t_ope		g_ope;

int					is_int(char *s);
int					is_numeric(char *s);
int					is_sign_numeric(char *s);
char				*get_next_num(char *s);
void				free_tab(char **t);
char				*parse_anthill(t_visual *visu);
int					add_link(char **t);
int					add_vertex(char **t, int special);
void				init_all_links(void);
t_path				*find_path(int start, int end, int max);
int					get_start_index(void);
void				convert_to_edges(void);

void				print(t_path *p);
void				print_path(int start, int end, char *f);

void				init_visual(t_visual *v);
void				draw_line(t_visual *v, t_int2 *p1, t_int2 *p2);
void				draw_graph(t_visual *v);
void				render(t_visual *v);
void				clear_image(t_visual *v);
int					on_key_hook(int key, void *v);
t_int2				*get_screen_coord(t_visual *v, t_vertice *vert, t_int2 *c);
void				init_ope(t_ope *ope);
void				add_to_ope(t_ope *ope, int a, int b);
int					loop(void *v);
void				draw_ants(t_visual *v);

#endif
