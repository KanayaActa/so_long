# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 21:38:04 by miwasa            #+#    #+#              #
#    Updated: 2024/11/30 14:18:40 by miwasa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long

FT_DIR		:= ./libft
LIBFT		:= $(FT_DIR)/libft.a
MLX_DIR		:= ./minilibx-linux
MLX_LIB		:= $(MLX_DIR)/libmlx.a
INCS_DIR	:= ./includes
SRCS_DIR	:= ./srcs
OBJS_DIR	:= ./objs

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -I$(INCS_DIR) -I$(FT_DIR) -I$(MLX_DIR) -g
MLXFLAGS	:= -L$(MLX_DIR) -lmlx -lm -L/usr/X11/lib -lXext -lX11

SRCS		:= \
	main.c \
	is_valid_args.c \
	option_help.c \
	init_mlx.c \
	init_map.c \
	init_camera.c \
	read_map.c \
	open_file.c \
	fill_map.c \
	check_alloc_error.c \
	set_z_value.c \
	project.c \
	matrix.c \
	transform.c \
	draw.c \
	mlx_hooks.c \
	events.c \
	move_camera.c \
	vector.c \
	color.c \
	free_utils.c \
	my_mlx_pixel_put.c \
	draw_utils.c

OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

.PHONY: all clean fclean re

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	$(MAKE) -C $(FT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLXFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	$(MAKE) clean -C $(FT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(FT_DIR)

re: fclean all
