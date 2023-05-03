/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:04:55 by edufour           #+#    #+#             */
/*   Updated: 2023/05/03 11:41:48 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> 
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	**get_stash(void);
char	*make_line(char *base, char *add, size_t start, size_t stop);
char	*process_read(int fd, char	**stash);
char	*process_stash(char **stash);
char	*get_next_line(int fd);
int		ft_strlen(const char *s);
int		ft_strchr(char *str, char search);
char	*safe_return(char *return_str, char ***free_stash, char **free_line);
void	*ft_calloc(size_t nb, size_t size);
void	ft_bzero(void *s, size_t n);

#endif