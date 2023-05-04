/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:04:55 by edufour           #+#    #+#             */
/*   Updated: 2023/05/04 16:10:44 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> 
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strjoin(char *base, char *add);
void	*ft_calloc(size_t nb, size_t size);
int		ft_strchr(char *str, char search);
int		ft_strlen(const char *s);
char	*read_to_stash(char *stash, int fd);
char	*stash_to_line(char *stash);
char	*keep_in_stash(char *stash);
char	*get_next_line(int fd);
void	safe_free(char **to_free);

#endif