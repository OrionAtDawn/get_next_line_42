/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:41 by edufour           #+#    #+#             */
/*   Updated: 2023/05/03 11:42:22 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//returns the adress of a pointer to stash. Allocates stash when first called.
char	**get_stash(void)
{
	static char	**stash;

	if (stash == NULL)
	{
		stash = ft_calloc(1, sizeof(char *));
		*stash = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	return (stash);
}

/*Allocates sufficient space for a copy of 'add[start]' - 'add[stop]' 
appended at the end of 'base'. Frees 'base', and returns new_line.*/
char	*make_line(char *base, char *add, size_t start, size_t stop)
{
	char	*new_line;
	size_t	i_base;
	size_t	i_add;
	size_t	i_new;

	i_base = 0;
	i_add = stop - start;
	if (!base)
		base = ft_calloc(1, 1);
	while (base[i_base])
		i_base++;
	new_line = ft_calloc(i_base + i_add + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i_new = 0;
	i_base = 0;
	while (base[i_base])
		new_line[i_new++] = base[i_base++];
	free(base);
	while (start < stop)
		new_line[i_new++] = add[start++];
	new_line[i_new] = '\0';
	return (new_line);
}

char	*process_stash(char **stash)
{
	int		eol;
	char	*next_line;

	eol = ft_strchr(*stash, '\n');
	if (eol == -1)
	{
		next_line = make_line(NULL, *stash, 0, ft_strlen(*stash));
		ft_bzero(*stash, ft_strlen(*stash));
	}
	else
	{
		next_line = make_line(NULL, *stash, 0, eol + 1);
		eol = ft_strchr(*stash, '\n');
		*stash = make_line(NULL, *stash, eol + 1, ft_strlen(*stash));
	}
	return (next_line);
}

/*Creates make_line from stash.
Calls read until an eol is found or read returns 0. 
Build next_line and saves, if needed, the unused str in stash.*/
char	*process_read(int fd, char	**stash)
{
	int		eol;
	int		read_bytes;
	char	*tmp;
	char	*next_line;

	next_line = process_stash(stash);
	read_bytes = 1;
	while (ft_strchr(next_line, '\n') == -1 && read_bytes > 0)
	{
		tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!tmp)
			return (safe_return(NULL, &stash, &next_line));
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		eol = ft_strchr(tmp, '\n');
		if (eol > -1)
			*stash = make_line(NULL, tmp, eol + 1, ft_strlen(tmp));
		else
			eol = ft_strlen(tmp);
		next_line = make_line(next_line, tmp, 0, eol + 1);
		free (tmp);
	}
	if (read_bytes == -1 || (read_bytes == 0 && next_line[0] == '\0'))
		return (safe_return(NULL, &stash, &next_line));
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	**stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = get_stash();
	if (stash == NULL || *stash == NULL)
		return (NULL);
	return (process_read(fd, stash));
}


#include <fcntl.h>
#include <stdio.h>
int main()
{
	int	fd;
	char	*line;
	fd = open("text.txt", O_RDONLY);

	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free (line);
}

