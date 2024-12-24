/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masnus <masnus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:42:33 by masnus            #+#    #+#             */
/*   Updated: 2024/12/24 09:36:02 by masnus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file_to_buffer(int fd, char *existing_data)
{
	int		bytes_read;
	char	*buffer;

	if (!existing_data)
		existing_data = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(existing_data), existing_data = NULL, NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), buffer = NULL, free(existing_data), existing_data = NULL, NULL);
		buffer[bytes_read] = '\0';
		existing_data = ft_strjoin(existing_data, buffer);
		if (!existing_data)
			return (free(buffer), buffer = NULL, NULL);
		if (ft_strchr(existing_data, '\n'))
			break ;
	}
	return (free(buffer), buffer = NULL, existing_data);
}

char	*extract_line_from_buffer(char *buffered_data)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffered_data || !buffered_data[0])
		return (NULL);
	while (buffered_data[i] && buffered_data[i] != '\n')
		i++;
	if (buffered_data[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
	{
		line[i] = buffered_data[i];
		i++;
	}
	if (buffered_data[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*remove_extracted_line(char *buffered_data)
{
	char	*remaining_data;
	int		i;
	int		j;

	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
		i++;
	if (!buffered_data[i])
		return (free(buffered_data), buffered_data = NULL, NULL);
	i++;
	remaining_data = malloc(sizeof(char) * (ft_strlen(buffered_data) - i + 1));
	if (!remaining_data)
		return (free(buffered_data), buffered_data = NULL, NULL);
	j = 0;
	while (buffered_data[i])
		remaining_data[j++] = buffered_data[i++];
	remaining_data[j] = '\0';
	return (free(buffered_data), buffered_data = NULL, remaining_data);
}

char	*get_next_line(int fd)
{
	static char	*buffered_data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (free(buffered_data), buffered_data = NULL, NULL);
	buffered_data = read_file_to_buffer(fd, buffered_data);
	if (!buffered_data)
		return (free(buffered_data), buffered_data = NULL, NULL);
	line = extract_line_from_buffer(buffered_data);
	if (!line)
		return (free(buffered_data), buffered_data = NULL, NULL);
	buffered_data = remove_extracted_line(buffered_data);
	return (line);
}
