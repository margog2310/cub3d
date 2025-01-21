/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:46:34 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/13 06:29:55 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*next_lst;
	t_list	*last_lst;

	last_lst = NULL;
	if (lst == NULL)
		return (NULL);
	next_lst = lst;
	while (next_lst)
	{
		if (next_lst->next == NULL)
		{
			last_lst = next_lst;
			break ;
		}
		next_lst = next_lst->next;
	}
	return (last_lst);
}
