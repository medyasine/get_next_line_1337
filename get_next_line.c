/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masnus <masnus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:07:01 by masnus            #+#    #+#             */
/*   Updated: 2024/11/17 11:32:28 by masnus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static int has_new_line(char *buffer)
{
    int i;

    if (!buffer)
        return (-1);
    i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char    *get_next_line(int fd)
{
    char        *buffer;
    static char *rem;
    char        *line;
    char        *temp;
    int         bytes;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    line = rem ? ft_strdup(rem) : ft_strdup("");
    if (!line)
    {
        free(buffer);
        return (NULL);
    }
    free(rem);
    rem = NULL;
    while (has_new_line(line) == -1)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes <= 0)
        {
            free(buffer);
            if (bytes == 0 && *line)
                return (line);
            free(line);
            return (NULL);
        }
        buffer[bytes] = '\0';
        temp = ft_strjoin(line, buffer);
        free(line);
        if (!temp)
        {
            free(buffer);
            return (NULL);
        }
        line = temp;
    }
    free(buffer);
    bytes = has_new_line(line);
    rem = ft_strdup(line + bytes + 1);
    line[bytes + 1] = '\0';
    return (line);
}