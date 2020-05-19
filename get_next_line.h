/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:16:20 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/18 22:33:57 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);

char	*ft_strcpy(char *dest, const char *src);

char	*ft_strdup(char const *s);

size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c);


#endif
