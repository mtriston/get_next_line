/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:16:14 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/18 22:00:06 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len;
	int		i;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = (char *)s1;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	if (!(new_str = (char *)malloc(len * sizeof(char))))
		return (NULL);
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	free(tmp);
	return (new_str);
}

static char		*check_over(char *over, char **line)
{
	char *new_line_ptr;

	new_line_ptr = NULL;
	if (over)
	{
		if ((new_line_ptr = ft_strchr(over, '\n')))
		{
			*new_line_ptr = '\0';
			new_line_ptr++;
			*line = ft_strdup(over);
			over = ft_strcpy(over, new_line_ptr);
		}
		else
		{
			*line = ft_strdup(over);
		}
	}
	else
		*line = ft_strdup("");
	return (new_line_ptr);
}

int				get_next_line(int fd, char **line)
{
	static char	*over;
	char		buf[BUFFER_SIZE + 1];
	char		*new_line_ptr;
	int			read_bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, buf, 0 != 0))
		return (-1);
	new_line_ptr = check_over(over, line);
	while (!new_line_ptr && (read_bytes = read(fd, buf, BUFFER_SIZE)))
	{
		buf[read_bytes] = '\0';
		if ((new_line_ptr = ft_strchr(buf, '\n')))
		{
			*new_line_ptr = '\0';
			free(over);
			over = ft_strdup(++new_line_ptr);
		}
		*line = ft_strjoin(*line, buf);
	}
	if (read_bytes != -1 && (read_bytes || ft_strlen(over) || ft_strlen(*line)))
		return (1);
	free(over);
	return (0);
}
