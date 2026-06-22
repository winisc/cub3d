# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wini <wini@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:14:29 by wini              #+#    #+#              #
#    Updated: 2026/06/21 23:47:42 by wini             ###   ########.fr        #
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

SRC = $(SRC_DIR)/cub3D.c $(SRC_DIR)/player.c $(SRC_DIR)/map.c

SRC_BONUS = $(SRC_DIR_BONUS)/cub3D_bonus.c

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_A = $(LIBFT_DIR)/libft.a

all: mlx libft $(NAME)

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
	@chmod +x $(MLX_DIR)/configure
	@$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re mlx libft
