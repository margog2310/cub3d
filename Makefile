# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 16:21:20 by mganchev          #+#    #+#              #
#    Updated: 2025/01/24 20:39:06 by ssottori         ###   ########.fr        #
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
BUILD_DIR = obj
LIBFT_DIR = $(SRC_DIR)/libft
MLX_DIR = $(SRC_DIR)/minilibx-linux
INC = include
IFLAGS = -I$(INC) -I$(LIBFT_DIR)/include

# ==== MLX & Libft
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = $(LIBFT_DIR)/libft.a

# =============== SRCS ==================
SRCS = cub3d.c \
		init.c \
		window.c \
		render.c \
		background.c \
		events.c \
		exit.c \
		parse_map.c \
		map_valid.c \
		utils.c \

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# =============== BUILD ==================
all: banner $(LIBFT) $(NAME) todo

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(LIBFT):
	@echo "[$(CYAN)CUB3D$(NC)] - Compiling libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(BUILD_DIR) $(OBJS) $(LIBFT)
	@echo "[$(GREEN)CUB3D$(NC)] - Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIBFT)
	@echo "[$(GREEN)✅ CUB3D READY!$(NC)] - $(GREEN)Run with ./$(NAME) map.cub$(NC)"

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
	@$(RM) $(BUILD_DIR)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

# =============== BANNER ==================

banner:
	@echo "[$(CYAN)======================================$(NC)]"
	@echo "[$(CYAN)        🔥 Compiling CUB3D 🔥$(NC)         ]"
	@echo "[$(CYAN)======================================$(NC)]"

#can delete this eventually and add instructions for how to run cub3d
todo:
	@echo "$(CYAN)======================================$(NC)"
	@echo "$(RED)	   📌TODO LIST:$(NC)"
	@echo "$(CYAN)======================================$(NC)"
	@echo "$(RED)📌 Hello, if you've made it this far, that means it compiles. YAY 🎉$(NC)"
	@echo "$(RED)💀 But I don’t know what errors will pop up once you try to run it...$(NC)"
	@echo "$(NC)1. Fix mouse click coordinate issue... idk how to yet$(NC)"
	@echo "$(NC)2. 🔥 Fkin fixxx the leaksss caused by parse map (losing my mind)$(NC)"
	@echo "$(NC)3. Try to check map validation (pls work)$(NC)"
	@echo "$(CYAN)======================================$(NC)"

.PHONY: all clean fclean re banner