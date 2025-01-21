/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:58:21 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/15 23:51:59 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_next_line(char *buffer)
{
	char	*new_line;
	char	*next_line;
	size_t	line_len;

	new_line = ft_strchr(buffer, '\n');
	if (new_line)
		line_len = new_line - buffer + 1;
	else
		line_len = ft_strlen(buffer);
	next_line = malloc(line_len + 1);
	if (next_line == NULL)
		return (NULL);
	ft_strlcpy(next_line, buffer, line_len + 1);
	ft_memmove(buffer, buffer + line_len, ft_strlen(buffer + line_len) + 1);
	return (next_line);
}

char	*find_next_line(int fd, char **buffer)
{
	char		*temp;
	char		*new_line;
	static char	read_buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	new_line = ft_strchr(*buffer, '\n');
	while (!new_line)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		read_buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		temp = ft_strjoin(*buffer, read_buffer);
		if (temp == NULL)
			return (NULL);
		free(*buffer);
		*buffer = temp;
		new_line = ft_strchr(*buffer, '\n');
	}
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
		buffer[0] = '\0';
	}
	temp = find_next_line(fd, &buffer);
	if (temp == NULL || buffer[0] == '\0')
	{
		if (buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = temp;
	return (extract_next_line(buffer));
}
