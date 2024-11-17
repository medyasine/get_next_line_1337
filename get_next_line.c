/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masnus <masnus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:07:01 by masnus            #+#    #+#             */
/*   Updated: 2024/11/17 12:30:25 by masnus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_free(char **s1, char **s2)
{
	if (s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		free(*s2);
		*s2 = NULL;
	}
}

char	*ft_next(char *str, char **new_line)
{
	char	*next;
	int		index;
	int		i;

	i = 0;
	index = 0;
	index = ft_strchr(str, '\n');
	if (index == -1)
		return (NULL);
	if (str[index + 1] == 0)
	{
		ft_free(&str, NULL);
		return (NULL);
	}
	index++;
	next = ft_calloc(ft_strlen(str + index) + 1, 1);
	if (!next)
	{
		ft_free(&str, new_line);
		return (NULL);
	}
	while (str[index])
		next[i++] = str[index++];
	ft_free(&str, NULL);
	return (next);
}

char	*ft_new_line(char *str)
{
	char	*new_line;
	int		index;

	if (!str || !*str)
		return (NULL);
	index = ft_strchr(str, '\n');
	if (index == -1)
		return (str);
	else
	{
		index++;
		new_line = ft_calloc(index + 1, 1);
		if (!new_line)
			return (NULL);
	}
	while (index--)
		new_line[index] = str[index];
	return (new_line);
}

void	ft_readalloc(int fd, char **next)
{
	char	*buff;
	ssize_t	r;

	r = 1;
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
	{
		ft_free(next, NULL);
		return ;
	}
	while (ft_strchr(buff, '\n') == -1 && r != 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			ft_free(next, NULL);
			break ;
		}
		buff[r] = '\0';
		*next = ft_strjoin(*next, buff);
		if (!*next)
			break ;
	}
	ft_free(&buff, NULL);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*next;

	new_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_readalloc(fd, &next);
	if (!next)
		return (NULL);
	new_line = ft_new_line(next);
	if (!new_line)
	{
		ft_free(&next, NULL);
		return (NULL);
	}
	next = ft_next(next, &new_line);
	return (new_line);
}
