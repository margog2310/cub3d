/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:28:21 by mganchev          #+#    #+#             */
/*   Updated: 2025/02/08 20:04:04 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *remove_set(char *str, char *set)
{
    char *result;
    char *temp;

    result = malloc(ft_strlen(str) + 1);
    temp = result;
    if (!result)
        return (NULL);
    while (*str)
    {
        str = skip_set(str, set);
        if (*str)
        {
            *result = *str;
            result++;
            str++;
        }
    }
    *result = '\0';
    return (temp);
}
