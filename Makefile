# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 16:21:20 by mganchev          #+#    #+#              #
#    Updated: 2025/01/22 17:08:30 by ssottori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============== COLORS ==================
MAKEFLAGS += --silent
RED=\033[1;31m
GREEN=\033[1;32m
BLUE=\033[1;34m
CYAN=\033[1;36m
NC=\033[0m

# ============== FLAGS ==================
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
RM = rm -rf
NAME = cub3d

# ==== Directories
SRC_DIR = srcs
BUILD_DIR = build
LIBFT_DIR = $(SRC_DIR)/libft
MLX_DIR = minilibx-linux
INC = include
IFLAGS = -I$(INC) -I$(LIBFT_DIR)/include

# ==== MLX & Libft
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = $(LIBFT_DIR)/libft.a

# =============== SRCS ==================
SRCS = main.c \
		cleanup.c \
		map_parse.c \
		map_valid.c \

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# =============== BUILD ==================
all: banner $(LIBFT) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(LIBFT):
	@echo "[$(CYAN)CUB3D$(NC)] - Compiling libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(BUILD_DIR) $(OBJS) $(LIBFT)
	@echo "[$(GREEN)CUB3D$(NC)] - Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIBFT)
	@echo "[$(GREEN)✅ CUB3D READY!$(NC)] - Run with ./$(NAME) map.cub"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "[$(BLUE)CUB3D$(NC)] - Compiling: $<"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# =============== CLEAN ==================
clean:
	@echo "[$(RED)CUB3D$(NC)] - Cleaning object files..."
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "[$(RED)CUB3D$(NC)] - Cleaning executable file..."
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

# =============== BANNER ==================

banner:
	@echo "[$(CYAN)======================================$(NC)]"
	@echo "[$(CYAN)        🔥 Compiling CUB3D 🔥$(NC)         ]"
	@echo "[$(CYAN)======================================$(NC)]"

.PHONY: all clean fclean re banner