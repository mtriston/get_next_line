/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:16:20 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/22 19:36:25 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

typedef struct	gnl
{
	int			fd;
	char		over[BUFFER_SIZE + 1];
	struct gnl	*next;
}				gnl_list;

int		get_next_line(int fd, char **line);

char	*ft_strcpy(char *dest, const char *src);

char	*ft_strdup(char const *s);

size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c);

void		ft_lstclear(gnl_list **lst);

#endif
