# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 16:21:20 by mganchev          #+#    #+#              #
#    Updated: 2025/01/28 23:08:32 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent
RED=\033[1;31m
GREEN=\033[1;32m
BLUE=\033[1;34m
CYAN=\033[1;36m
YEL=\033[1;33m
NC=\033[0m

# ============== FLAGS ==================
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -g
RM = rm -rf
NAME = cub3d

# ==== Directories
SRC_DIR = srcs
BUILD_DIR = obj
LIBS_DIR = libs
LIBFT_DIR = $(LIBS_DIR)/libft
MLX_DIR = $(LIBS_DIR)/mlx
INC = inc
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
		parse_file/parse.c \
		parse_file/parse_elements.c \
        parse_file/parse_map.c \
        parse_file/map_valid.c \
        parse_file/parse_utils.c \
        parse_file/file_valid.c \
        game.c \
        player.c \
		utils.c \

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# =============== BUILD ==================
all: banner $(LIBFT) $(NAME) todo

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./libs/mlx > /dev/null 2>&1
	@echo "[$(YEL)MLX$(NC)] - Compiling MinilibX..."
	@make -C ./libs/mlx > /dev/null 2>&1
	@echo "[$(GREEN)✅ MLX Ready!$(NC)]"

$(LIBFT):
	@echo "[$(CYAN)LIBFT$(NC)] - Compiling libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "[$(GREEN)CUB3D$(NC)] - Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIBFT)
	@echo "[$(GREEN)✅ CUB3D READY!$(NC)] - $(GREEN)Run with ./$(NAME) map.cub$(NC)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "[$(BLUE)CUB3D$(NC)] - Compiling: $<"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# =============== CLEAN ==================
clean:
	@echo "[$(RED)CUB3D$(NC)] - Cleaning object files..."
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "[$(RED)CUB3D$(NC)] - Cleaning executable file..."
	@$(RM) $(NAME)
	@$(RM) $(BUILD_DIR)
	@$(RM) $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)

re: fclean mlx all

# =============== BANNER ==================

banner:
	@echo "[$(CYAN)======================================$(NC)]"
	@echo "[$(CYAN)        🔥 Compiling CUB3D 🔥$(NC)         ]"
	@echo "[$(CYAN)======================================$(NC)]"
	@echo "$(YEL)⚠️  Remember to run 'make mlx' if you haven't already! ⚠️$(NC)"

#can delete this eventually and add instructions for how to run cub3d
todo:
	@echo "$(CYAN)======================================$(NC)"
	@echo "$(RED)	   📌TODO LIST:$(NC)"
	@echo "$(CYAN)======================================$(NC)"
	@echo "$(YEL)📌 Hello, if you've made it this far, that means it compiles. YAY 🎉$(NC)"
	@echo "$(YEL)💀 But I don’t know what $(RED)errors$(YEL) will pop up once you try to run it...$(NC)"
	@echo "$(NC)1. Fix mouse click coordinate issue... idk how to yet$(NC)"
	@echo "$(NC)2. 🔥 Fkin fixxx the seg fault (losing my mind)$(NC)"
	@echo "$(NC)3. Try to check map validation (pls work)$(NC)"
	@echo "$(CYAN)======================================$(NC)"

.PHONY: all clean fclean re banner