/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:16:14 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/20 00:42:18 by mtriston         ###   ########.fr       */
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

static char		*check_over(char *over, char **line)
{
	char *new_line_ptr;
	int i;

	new_line_ptr = NULL;
	i = 0;
	if (over)
	{
		if ((new_line_ptr = ft_strchr(over, '\n')))
		{
			*new_line_ptr = '\0';
			*line = ft_strdup(over);
			over = ft_strcpy(over, ++new_line_ptr);
		}
		else
		{
			*line = ft_strdup(over);
			while (i < BUFFER_SIZE)
				over[i++] = '\0';
		}
	}
	else
		*line = ft_strdup("");
	return (new_line_ptr);
}

static int		next_line(int fd, char *over, char **line)
{
	char		*buf;
	char		*new_line_ptr;
	int			read_bytes;

	if (BUFFER_SIZE < 1 || !(buf = malloc((BUFFER_SIZE + 1) * sizeof(char))) \
	|| fd < 0 || !line || (read(fd, buf, 0) != 0))
		return (-1);
	new_line_ptr = check_over(over, line);
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
	free(buf);
	if (read_bytes != -1 && (read_bytes || ft_strlen(*line)))
		return (1);
	return ((read_bytes != -1) ? 0 : -1);
}

static gnl_list *new_list(int fd)
{
	int i;
	gnl_list *list;

	i = 0;
	if (!(list = (gnl_list *)malloc(sizeof(gnl_list))))
		return (NULL);
	if (!(list->over = (char *)malloc(BUFFER_SIZE * sizeof(char))))
		return (NULL);
	while (i < BUFFER_SIZE)
		list->over[i++] = '\0';
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
