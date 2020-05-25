/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:16:20 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/25 11:47:52 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	int				fd;
	char			over[BUFFER_SIZE + 1];
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);

char				*ft_strcpy(char *dest, const char *src);

char				*ft_strdup(char const *s);

size_t				ft_strlen(const char *s);

char				*ft_strchr(const char *s, int c);

void				ft_lstclear(t_list **lst);

#endif
