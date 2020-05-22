/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:16:14 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/22 22:26:04 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static int		check_over(char *over, char **new_line_ptr, char **line)
{
	*new_line_ptr = NULL;
	if (over && *over)
	{
		if ((*new_line_ptr = ft_strchr(over, '\n')))
		{
			**new_line_ptr = '\0';
			if (!(*line = ft_strdup(over)))
				return (-1);
			over = ft_strcpy(over, ++*new_line_ptr);
		}
		else
		{
			if (!(*line = ft_strdup(over)))
				return (-1);
			over[0] = '\0';
		}
	}
	else
		if (!(*line = ft_strdup(over)))
			return (-1);
	return (1);
}

static int		next_line(int fd, char *over, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	char		*new_line_ptr;
	int			read_bytes;

	if (BUFFER_SIZE < 1 || fd < 0 || !line || (read(fd, buf, 0) != 0) || \
	!(check_over(over, &new_line_ptr, line)))
		return (-1);
	while (!new_line_ptr && (read_bytes = read(fd, buf, BUFFER_SIZE)))
	{
		buf[read_bytes] = '\0';
		if ((new_line_ptr = ft_strchr(buf, '\n')))
		{
			*new_line_ptr = '\0';
			over = ft_strcpy(over, ++new_line_ptr);
		}
		*line = ft_strjoin(*line, buf);
	}
	if (read_bytes != -1 && (read_bytes || ft_strlen(*line)))
		return (1);
	return ((read_bytes != -1) ? 0 : -1);
}

static gnl_list *new_list(int fd)
{
	gnl_list *list;

	if (!(list = (gnl_list *)malloc(sizeof(gnl_list))))
		return (NULL);
	list->fd = fd;
	list->next = NULL;
	return (list);
}

int get_next_line(int fd, char **line)
{
	static gnl_list	*begin_list;
	gnl_list		*ptr;
	int				flag;
	if (!begin_list)
		if (!(begin_list = new_list(fd)))
			return (-1);
	ptr = begin_list;
	while(ptr)
	{
		if (ptr->fd == fd)
		{
			flag = next_line(fd, ptr->over, line);
			break ;
		}
		else if (ptr->next == NULL)
		{
			if (!(ptr->next = new_list(fd)))
				flag = -1;
			else
				flag = next_line(fd, ptr->next->over, line);
		}
		ptr = ptr->next;
	}
	if (flag <= 0)
		ft_lstclear(&begin_list);
	return (flag);
}
