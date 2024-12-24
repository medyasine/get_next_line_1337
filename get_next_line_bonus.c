/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masnus <masnus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:49:04 by masnus            #+#    #+#             */
/*   Updated: 2024/12/24 09:38:01 by masnus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_append_to_buffer(int fd, char *current_buffer)
{
	int		bytes_read;
	char	*temp_buffer;

	if (!current_buffer)
		current_buffer = ft_strdup("");
	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (free(current_buffer), current_buffer = NULL, NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp_buffer), temp_buffer = NULL, free(current_buffer), current_buffer = NULL,
				NULL);
		temp_buffer[bytes_read] = '\0';
		current_buffer = ft_strjoin(current_buffer, temp_buffer);
		if (!current_buffer)
			return (free(temp_buffer), temp_buffer = NULL, NULL);
		if (ft_strchr(current_buffer, '\n'))
			break ;
	}
	return (free(temp_buffer), temp_buffer = NULL, current_buffer);
}

char	*extract_next_line(char *current_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!current_buffer || !current_buffer[0])
		return (NULL);
	while (current_buffer[i] && current_buffer[i] != '\n')
		i++;
	if (current_buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (current_buffer[i] && current_buffer[i] != '\n')
	{
		line[i] = current_buffer[i];
		i++;
	}
	if (current_buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_remaining_buffer(char *current_buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (current_buffer[i] && current_buffer[i] != '\n')
		i++;
	if (!current_buffer[i])
		return (free(current_buffer), current_buffer = NULL, NULL);
	i++;
	new_buffer = malloc(sizeof(char) * (ft_strlen(current_buffer) - i + 1));
	if (!new_buffer)
		return (free(current_buffer), current_buffer = NULL, NULL);
	j = 0;
	while (current_buffer[i])
		new_buffer[j++] = current_buffer[i++];
	new_buffer[j] = '\0';
	return (free(current_buffer), current_buffer = NULL, new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*file_buffers[OPEN_MAX];
	char		*line;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (free(file_buffers[fd]), file_buffers[fd] = NULL, NULL);
	file_buffers[fd] = read_and_append_to_buffer(fd, file_buffers[fd]);
	if (!file_buffers[fd])
		return (free(file_buffers[fd]), file_buffers[fd] = NULL, NULL);
	line = extract_next_line(file_buffers[fd]);
	if (!line)
		return (free(file_buffers[fd]), file_buffers[fd] = NULL, NULL);
	file_buffers[fd] = update_remaining_buffer(file_buffers[fd]);
	return (line);
}
