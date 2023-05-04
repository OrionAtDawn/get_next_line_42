/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:41 by edufour           #+#    #+#             */
/*   Updated: 2023/05/04 16:11:55 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Calls read until an eol in found or read returns 0/-1.
//Puts everything in stash.
char	*read_to_stash(char *stash, int fd)
{
	char	*tmp;
	int		read_bytes;

	if (stash == NULL)
		stash = ft_calloc(BUFFER_SIZE, sizeof(char));
	read_bytes = 1;
	while (ft_strchr(stash, '\n') == -1 && read_bytes > 0)
	{
		tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			safe_free(&tmp);
			safe_free(&stash);
			return (NULL);
		}
		stash = ft_strjoin(stash, tmp);
		safe_free(&tmp);
	}
	return (stash);
}

//Returns a copy of everything before the first '\n' (or '\0' if not found)
char	*stash_to_line(char *stash)
{
	int		eol;
	int		i;
	char	*next_line;

	if (stash == NULL)
		return (NULL);
	eol = ft_strchr(stash, '\n');
	if (eol == -1)
		return (ft_strjoin(NULL, stash));
	next_line = ft_calloc(eol + 2, sizeof(char));
	i = -1;
	while (++i <= eol)
		next_line[i] = stash[i];
	return (next_line);
}

//Remakes the stash so that only what's left after the first '\n' remains in it
//(prepares stash for the next call of get_next_line)
//Copies the desired portion, frees current stash, 
//then allocates a new one and calls ft_strjoin(NULL, new_stash).
char	*keep_in_stash(char *stash)
{
	int		eol;
	int		i;
	char	*new_stash;

	if (stash == NULL)
		return (NULL);
	eol = ft_strchr(stash, '\n');
	if (eol == -1)
	{
		safe_free(&stash);
		return (NULL);
	}
	eol ++;
	new_stash = ft_calloc((ft_strlen(stash) - eol) + 1, sizeof(char));
	i = 0;
	while (stash[eol])
		new_stash[i++] = stash[eol++];
	safe_free(&stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(stash, fd);
	if (stash == NULL)
		return (NULL);
	if (stash[0] == 0)
	{	
		safe_free(&stash);
		return (NULL);
	}
	next_line = stash_to_line(stash);
	stash = keep_in_stash(stash);
	return (next_line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int	fd;
// 	char	*line;
// 	fd = open("/Users/edufour/Desktop/gnl_elo/text.txt", O_RDONLY);
// 	// printf("%d", fd);

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	// while (line != NULL)
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// 	line = get_next_line(fd);
// 	// }
// 	if (line)
// 		free (line);
// }

