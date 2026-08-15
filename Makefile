# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:14:29 by wini              #+#    #+#              #
#    Updated: 2026/08/14 21:57:36 by mtakiyos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
MLX_DIR = libs/minilibx-linux
LIBFT_DIR = libs/libft

INCLUDES = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)

SRC =	$(SRC_DIR)/cub3D.c \
		$(SRC_DIR)/controls/events.c \
		$(SRC_DIR)/controls/player.c \
		$(SRC_DIR)/inits/game.c \
		$(SRC_DIR)/inits/img.c \
		$(SRC_DIR)/inits/map.c \
		$(SRC_DIR)/inits/player.c \
		$(SRC_DIR)/parse/file_validation.c \
		$(SRC_DIR)/parse/header.c \
		$(SRC_DIR)/parse/header_utils_2.c \
		$(SRC_DIR)/parse/map_utils_3.c \
		$(SRC_DIR)/parse/map.c \
		$(SRC_DIR)/parse/flood_fill.c \
		$(SRC_DIR)/parse/player.c \
		$(SRC_DIR)/parse/file_utils.c \
		$(SRC_DIR)/parse/header_utils.c \
		$(SRC_DIR)/parse/map_utils_2.c \
		$(SRC_DIR)/parse/map_utils.c \
		$(SRC_DIR)/parse/player_utils.c \
		$(SRC_DIR)/render/dda.c \
		$(SRC_DIR)/render/draw.c \
		$(SRC_DIR)/render/minimap.c \
		$(SRC_DIR)/render/minimap_utils.c \
		$(SRC_DIR)/render/raycast.c \
		$(SRC_DIR)/render/render.c \
		$(SRC_DIR)/render/textures.c \
		$(SRC_DIR)/utils/clear.c \
		$(SRC_DIR)/utils/math_utils.c

OBJS = $(SRC:.c=.o)

MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_A = $(LIBFT_DIR)/libft.a

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g2 -O0 -fsanitize=leak
endif



all: mlx libft $(NAME)

game: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -L$(LIBFT_DIR) -lft $(MLX_LIBS) -o $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -L$(LIBFT_DIR) -lft $(MLX_LIBS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft:
	@$(MAKE) -C $(LIBFT_DIR)

mlx:
	@$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)

clean-game:
	rm -f $(OBJS) $(NAME)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

MAP ?= maps/valid/simple.cub

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all \
		--suppressions=cub3d.supp ./$(NAME) $(MAP)

.PHONY: all clean clean-game fclean re mlx libft game leaks
