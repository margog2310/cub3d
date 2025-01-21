/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:39:44 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/13 04:59:45 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*next_lst;

	next_lst = lst;
	count = 0;
	while (next_lst)
	{
		next_lst = next_lst->next;
		count++;
	}
	return (count);
}
