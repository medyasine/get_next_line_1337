/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masnus <masnus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:07:06 by masnus            #+#    #+#             */
/*   Updated: 2024/11/17 11:29:56 by masnus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t    ft_strlen(const char *s)
{
    size_t    i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char    *ft_strdup(const char *s)
{
    size_t    len;
    size_t    i;
    char    *new_s;

    len = ft_strlen(s) + 1;
    new_s = malloc(len);
    if (!new_s)
        return (NULL);
    i = 0;
    while (s[i])
    {
        new_s[i] = s[i];
        i++;
    }
    new_s[i] = '\0';
    return (new_s);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *str;
    size_t    i;

    if (!s)
        return (NULL);
    if (start >= ft_strlen(s))
        return (ft_strdup(""));
    if (len > ft_strlen(s) - start)
        len = ft_strlen(s) - start;
    str = malloc(len + 1);
    if (!str)
        return (NULL);
    i = 0;
    while (i < len)
        str[i++] = s[start++];
    str[i] = '\0';
    return (str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	j;

	if (dsize == 0)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dsize <= dest_len)
		return (src_len + dsize);
	j = 0;
	while (src[j] && (dest_len + j) < (dsize - 1))
	{
		dst[dest_len + j] = src[j];
		j++;
	}
	dst[dest_len + j] = '\0';
	return (dest_len + src_len);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    char    *str;
    size_t    total;

    if (!s1)
        s1 = ft_strdup("");
    if (!s2)
        s2 = ft_strdup("");
    total = ft_strlen(s1) + ft_strlen(s2);
    str = malloc(total + 1);
    if (!str)
        return (NULL);
    str[0] = '\0';
    ft_strlcat(str, s1, total + 1);
    ft_strlcat(str, s2, total + 1);
    return (str);
}