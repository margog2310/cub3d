/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:00:24 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/21 19:19:48 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
long long			ft_atoi(const char *str);
int					ft_strlen(const char *str);
int					ft_power(int nb, int power);
int					ft_puthexnbr(unsigned int nbr, int uppercase);
int					ft_putchar_fd(char c, int fd);
int					ft_print_ptr(void *ptr);
int					ft_putstr_fd(char *s, int fd);
int					ft_putnbr_fd(int n, int fd);
int					ft_putunbr_fd(int n, int fd);
int					ft_printf(const char *fmt, ...);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_itoa(int n);
char				*get_next_line(int fd);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				**ft_split(const char *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_strnstr(const char *str, const char *sub, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void				ft_swap(int *a, int *b);
void				ft_swap_char(char *a, char *b);
void				ft_bzero(void *s, size_t n);
void				ft_putendl_fd(char *s, int fd);
void				free_grid(char **grid, int line_count);
void				ft_print_grid(char **grid, int rows, int cols);
void				ft_grid_size(char **grid, int *rows, int *cols);
void				*skip_set(char *str, char *set);
void				**ft_allocate_grid(int rows, int cols, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_list_remove_if(t_list **begin_list, void *data_ref,
						int (*cmp)());
void				ft_lstiter(t_list *lst, void (*f)(void *));
size_t				ft_nbrlen(int n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);

#endif