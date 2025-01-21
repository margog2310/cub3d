# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 16:21:20 by mganchev          #+#    #+#              #
#    Updated: 2025/01/21 17:39:35 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -g3 -Wall -Werror -Wextra

OBJDIR = ./build
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFTDIR = ./sources/libft
LIBFT = $(LIBFTDIR)/libft.a

SRCDIR = sources
SRCS = 

all: $(NAME) $(OBJS) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		mkdir -p $(@D)
		cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
		cc $(CFLAGS) $(OBJS) -o $@
		
$(OBJDIR):
		mkdir -p $(OBJDIR)	
		
$(LIBFT):
		make -C $(LIBFTDIR)	all
		
clean:
		make -C $(LIBFTDIR) clean
		rm -fr $(OBJDIR)
		
fclean: clean
		make -C $(LIBFTDIR) fclean
		rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re