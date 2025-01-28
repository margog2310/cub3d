# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 00:20:17 by mganchev          #+#    #+#              #
#    Updated: 2025/01/21 19:10:01 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE = ./include

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCDIR = ./
OBJDIR =./build

SRCS = $(SRCDIR)/ft_atoi.c $(SRCDIR)/ft_bzero.c $(SRCDIR)/ft_calloc.c $(SRCDIR)/ft_isalnum.c \
$(SRCDIR)/ft_isalpha.c $(SRCDIR)/ft_isascii.c $(SRCDIR)/ft_isdigit.c $(SRCDIR)/ft_isprint.c \
$(SRCDIR)/ft_itoa.c $(SRCDIR)/ft_memchr.c $(SRCDIR)/ft_memcmp.c $(SRCDIR)/ft_memcpy.c \
$(SRCDIR)/ft_memmove.c $(SRCDIR)/ft_memset.c $(SRCDIR)/ft_putchar_fd.c $(SRCDIR)/ft_putendl_fd.c \
$(SRCDIR)/ft_putnbr_fd.c $(SRCDIR)/ft_putstr_fd.c $(SRCDIR)/ft_split.c $(SRCDIR)/ft_strchr.c \
$(SRCDIR)/ft_strdup.c $(SRCDIR)/ft_striteri.c $(SRCDIR)/ft_strjoin.c $(SRCDIR)/ft_strlcat.c \
$(SRCDIR)/ft_strlcpy.c $(SRCDIR)/ft_strlen.c $(SRCDIR)/ft_strmapi.c $(SRCDIR)/ft_strncmp.c \
$(SRCDIR)/ft_strnstr.c $(SRCDIR)/ft_strrchr.c $(SRCDIR)/ft_strtrim.c $(SRCDIR)/ft_substr.c \
$(SRCDIR)/ft_tolower.c $(SRCDIR)/ft_toupper.c $(SRCDIR)/ft_nbrlen.c $(SRCDIR)/ft_power.c \
$(SRCDIR)/ft_print_ptr.c $(SRCDIR)/ft_puthexnbr.c $(SRCDIR)/ft_putunbr_fd.c $(SRCDIR)/ft_swap.c \
$(SRCDIR)/ft_swap_char.c $(SRCDIR)/ft_allocate_grid.c $(SRCDIR)/ft_grid_size.c $(SRCDIR)/ft_list_remove_if.c \
$(SRCDIR)/ft_print_grid.c $(SRCDIR)/ft_realloc.c $(SRCDIR)/ft_printf.c $(SRCDIR)/get_next_line.c \
$(SRCDIR)/ft_strcmp.c $(SRCDIR)/free_grid.c $(SRCDIR)/skip_set.c

BONUS_SRCS = $(SRCDIR)/ft_lstadd_back.c $(SRCDIR)/ft_lstadd_front.c $(SRCDIR)/ft_lstclear.c \
$(SRCDIR)/ft_lstdelone.c $(SRCDIR)/ft_lstiter.c $(SRCDIR)/ft_lstlast.c \
$(SRCDIR)/ft_lstmap.c $(SRCDIR)/ft_lstnew.c $(SRCDIR)/ft_lstsize.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

${NAME}: $(OBJS) 
	@ar rcs $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus