# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpoirier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 13:08:51 by cpoirier          #+#    #+#              #
#    Updated: 2019/03/10 17:25:10 by skiessli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS = 	srcs/lem_in.c				\
		srcs/parse.c				\
		srcs/parse_util.c			\
		srcs/add.c					\
		srcs/visual.c				\
		srcs/draw_line.c			\
		srcs/draw_graph.c			\
		srcs/find_path.c			\
		srcs/print.c				\
		srcs/key_hook.c				\
		srcs/ope.c					\
		srcs/loop.c					\
		srcs/convert.c				\

LIBFT = libft

HDRS =	includes/lem_in.h			\

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -g -fsanitize=address # -Werror

INCLUDES = -I./includes -I./libft -I./minilibx -I /usr/local/include

CC = gcc

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@make -C $(LIBFT)
	#$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME) $(LIBFT)/libft.a minilibx/libmlx_Linux.a -L/usr/x86_64-linux-gnu -lXext -lX11 #use this on macOs instead: -lmlx -framework OpenGL -framework AppKit
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME) $(LIBFT)/libft.a -lmlx -framework OpenGL -framework AppKit

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT)
	rm -f $(NAME)

re:	fclean all
