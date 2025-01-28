/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 02:50:11 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/13 04:59:24 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next_lst;

	if (!lst || !f)
		return ;
	next_lst = lst;
	while (next_lst)
	{
		f(next_lst->content);
		next_lst = next_lst->next;
	}
}
