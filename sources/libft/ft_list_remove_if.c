/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:14:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/04 18:24:09 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*temp;

	if (*begin_list == NULL)
		return ;
	temp = *begin_list;
	if (cmp(temp->content, data_ref) == 0)
	{
		*begin_list = (*begin_list)->next;
		free(temp->content);
		free(temp);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_list_remove_if(&(*begin_list)->next, data_ref, cmp);
}
