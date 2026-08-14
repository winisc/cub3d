# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:14:29 by wini              #+#    #+#              #
#    Updated: 2026/08/14 12:07:32 by mtakiyos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC_DIR_BONUS = src_bonus
MLX_DIR = libs/minilibx-linux
LIBFT_DIR = libs/libft

INCLUDES = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)
INCLUDES_BONUS = -Iincludes_bonus -I$(MLX_DIR) -I$(LIBFT_DIR)

SRC =	$(SRC_DIR)/cub3D.c \
		$(SRC_DIR)/controls/events.c \
		$(SRC_DIR)/controls/player.c \
		$(SRC_DIR)/inits/game.c \
		$(SRC_DIR)/inits/img.c \
		$(SRC_DIR)/inits/map.c \
		$(SRC_DIR)/inits/player.c \
		$(SRC_DIR)/parse/file_validation.c \
		$(SRC_DIR)/parse/header.c \
		$(SRC_DIR)/parse/map.c \
		$(SRC_DIR)/parse/player.c \
		$(SRC_DIR)/parse/file_utils.c \
		$(SRC_DIR)/parse/header_utils.c \
		$(SRC_DIR)/parse/map_utils_2.c \
		$(SRC_DIR)/parse/map_utils.c \
		$(SRC_DIR)/parse/player_utils.c \
		$(SRC_DIR)/render/dda.c \
		$(SRC_DIR)/render/draw.c \
		$(SRC_DIR)/render/map.c \
		$(SRC_DIR)/render/raycast.c \
		$(SRC_DIR)/render/render.c \
		$(SRC_DIR)/render/textures.c \
		$(SRC_DIR)/utils/clear.c \
		$(SRC_DIR)/utils/math_utils.c

SRC_BONUS = $(SRC_DIR_BONUS)/cub3D_bonus.c

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

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

bonus: mlx libft $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(INCLUDES_BONUS) -L$(LIBFT_DIR) -lft $(MLX_LIBS) -o $(NAME_BONUS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SRC_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

libft:
	@$(MAKE) -C $(LIBFT_DIR)

mlx:
	@$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)

clean-game:
	rm -f $(OBJS) $(OBJS_BONUS) $(NAME) $(NAME_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean clean-game fclean re mlx libft game
