/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:04:25 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/28 23:13:47 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse(t_mcraft *mcraft, char *file)
{
    int fd;
    char **elements;
    
    fd = open(file, O_RDONLY);
    if (fd < 0)
        exit_err("Failed to open file or file non-existent.");
    elements = parse_elements(mcraft, fd);
    if (!elements)
        exit_err("Error while parsing map elements.");
    mcraft->map = create_map(fd, mcraft);
    if (!mcraft->map)
        exit_err("Invalid map.");
    return (0);
}