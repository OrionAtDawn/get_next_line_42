/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:47:16 by edufour           #+#    #+#             */
/*   Updated: 2023/04/12 15:38:10 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Review rules on allocation. In which instances should you allocate memory ?
Make sure strings end with a "\0"
Free allocated variables
*/

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

char	*create_line(char *src, char *dst, char **adress_stash)
{
	//returns the content up to a '\n' or the end of dst. (How will you know it's the end ? '\0' ?)
	// if a '\n' was found, keeps what's left after in stash.
}

char	*process_read(int fd, char *base, char **adress_stash)
{
	char	*next_line;
	char	*tmp;
	int		read_bytes;
	int		line_lenght;

	next_line = base;			//make sure this works
	line_lenght = 0;
	read_bytes = read(fd, tmp, BUFFER_SIZE);
	if (read_bytes == -1 || (read_bytes == 0 && next_line[0] == 0))
		return (NULL);
	next_line = create_line(next_line, tmp, adress_stash);
	while (next_line[line_lenght])
		line_lenght++;
	if (next_line[line_lenght] != '\n')
		next_line = process_read(fd, next_line, adress_stash);
	return(next_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stash;				
	char		*return_line;
	int			line_lenght;

	line_lenght = 0;
	if (stash == NULL)
		stash = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	next_line = create_line("\0", stash, &stash);
	while (next_line[line_lenght])
		line_lenght++;
	if (next_line[line_lenght] != '\n')
		next_line = process_read(fd, next_line, &stash);
	while(next_line[line_lenght])
		line_lenght++;
	return_line = ft_calloc(line_lenght, sizeof(char));
	return_line = next_line;
	return(next_line);
}
