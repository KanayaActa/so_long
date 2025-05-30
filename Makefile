# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 04:05:51 by miwasa            #+#    #+#              #
#    Updated: 2025/05/17 04:05:51 by miwasa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long
NAME_BONUS	:= so_long_bonus
NAME_3D		:= so_long_3d

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
	so_long_main.c \
	map_utils.c \
	map_validation.c \
	player.c \
	game_draw.c \
	textures.c \
	game_events.c \
	utils.c

# 3D版のソースファイル
SRCS_3D		:= \
	so_long_main_3d.c \
	map_utils.c \
	map_validation.c \
	player.c \
	game_draw.c \
	textures.c \
	utils.c \
	so_long_vector.c \
	so_long_matrix.c \
	so_long_projection.c \
	so_long_draw_3d.c \
	so_long_camera.c \
	so_long_events_3d.c

OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# ボーナス用のソースファイル（基本的に同じだが、必要に応じて変更可能）
SRCS_BONUS	:= \
	so_long_main.c \
	map_utils.c \
	map_validation.c \
	player.c \
	game_draw.c \
	textures.c \
	game_events.c \
	utils.c

OBJS_BONUS	:= $(addprefix $(OBJS_DIR)/bonus/, $(SRCS_BONUS:.c=.o))

# 3D版のオブジェクトファイル
OBJS_3D		:= $(addprefix $(OBJS_DIR)/3d/, $(SRCS_3D:.c=.o))

.PHONY: all clean fclean re bonus 3d

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

# ボーナスターゲット
bonus: $(LIBFT) $(MLX_LIB) $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -D BONUS=1 -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT) $(MLXFLAGS)

$(OBJS_DIR)/bonus/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -D BONUS=1 -c $< -o $@

# 3D版のターゲット
3d: $(LIBFT) $(MLX_LIB) $(NAME_3D)

$(NAME_3D): $(OBJS_3D) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -D MODE_3D=1 -o $(NAME_3D) $(OBJS_3D) $(LIBFT) $(MLXFLAGS)

$(OBJS_DIR)/3d/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -D MODE_3D=1 -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	$(MAKE) clean -C $(FT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(NAME_3D)
	$(MAKE) fclean -C $(FT_DIR)

re: fclean all
