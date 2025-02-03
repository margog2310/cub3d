/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:08:21 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/03 22:23:13 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// return a pointer to the main struct
t_mcraft	*get_mcraft(t_mcraft *mcraft)
{
	static t_mcraft	*ptr;

	if (!mcraft)
		return (ptr);
	ptr = mcraft;
	return (mcraft);
}
