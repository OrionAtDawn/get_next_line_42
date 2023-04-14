/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:41 by edufour           #+#    #+#             */
/*   Updated: 2023/04/14 14:30:51 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*stash;				
	char		*return_line;
	int			line_lenght;

	line_lenght = 0;
	if (stash == NULL)
		stash = ft_calloc(BUFFER_SIZE, sizeof(char));
	next_line = create_line("\0", stash, &stash);
	while (next_line[line_lenght])
		line_lenght++;
	if (next_line[line_lenght] != '\n')
		next_line = process_read(fd, next_line, &stash);
	if (next_line == NULL)
	{	
		if (stash)
			free (stash);
		return (NULL);
	}
	while (next_line[line_lenght])
		line_lenght++;
	return_line = ft_calloc(line_lenght, sizeof(char));
	return_line = next_line;
	return (return_line);
}

int main()
{
	
}