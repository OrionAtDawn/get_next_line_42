/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:53:01 by edufour           #+#    #+#             */
/*   Updated: 2023/04/14 15:09:51 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

void	order_stash(char **adress_stash, char *add, int eol)
{
	int	i;

	i = 0;
	while(add[eol + i])
	{	
		*adress_stash[i] = add[eol + i]; 
		i++;
	}
	while (i <= BUFFER_SIZE)
	{	
		*adress_stash[i] = '\0';
		i++;
	}
}

char	*create_line(char *src, char *to_add, char **adress_stash)
{
	int		eol;
	int		i;
	int		i_add;
	char	*line;

	eol = 0;
	i = 0;
	i_add = 0;
	line = src;
	while (to_add[i])
		i++;
	while (to_add && to_add[eol] != '\n')
		eol++;
	if (eol <= i - 1)
		order_stash(adress_stash, to_add, eol);
	i = 0;
	while (line[i])
		i++;
	while (i_add <= eol)
	{	
		line[i] = to_add[i_add];
		i++;
		i_add++;
	}
	return (line);
}

char	*process_read(int fd, char *base, char **adress_stash)
{
	char	*next_line;
	char	*tmp;
	int		read_bytes;
	int		line_lenght;

	next_line = base;
	line_lenght = 0;
	read_bytes = read(fd, tmp, BUFFER_SIZE);
	if (read_bytes == -1 || (read_bytes == 0 && next_line[0] == 0))
		return (NULL);
	next_line = create_line(next_line, tmp, adress_stash);
	while (next_line[line_lenght])
		line_lenght++;
	if (next_line[line_lenght] != '\n')
		next_line = process_read(fd, next_line, adress_stash);
	return (next_line);
}
