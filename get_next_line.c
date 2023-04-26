/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:41 by edufour           #+#    #+#             */
/*   Updated: 2023/04/26 11:50:58 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//returns the adress of a pointer to stash. Allocates stash when first called.
char	**get_stash(void)
{
	static char	**stash;

	if (stash == NULL)
		stash = ft_calloc(1, sizeof(char *));
	return (stash);
}

//Allocates sufficient space for a copy of 'add[start]' - 'add[stop]' 
//appended at the end of 'base'. Frees 'base' and 'add', and returns new_line.
char	*make_line(char *base, char *add, int start, int stop)
{
	char	*new_line;
	int		i_base;
	int		i_add;
	int		i_new;

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
		new_line[i_new] = base[i_base++];
	free(base);
	while (start < stop)
		new_line[i_new++] = add[start++];
	if (add)
		free(add);
	new_line[i_new] = '\0';
	return (new_line);
}

//Creates make_line from stash.
//Calls read until an eol is found or read returns 0. 
//Build next_line and saves, if needed, the unused str in stash.
char	*process_read(int fd, char *next_line, char	**stash)
{
	int		eol;
	int		read_bytes;
	char	*tmp;

	eol = ft_strchr(*stash, '\n');
	if (eol == -1)
		next_line = make_line(next_line, *stash, 0, ft_strlen(*stash));
	else
		next_line = make_line(next_line, *stash, 0, eol);
	while (ft_strchr(next_line, '\n') == 0 && read_bytes > 0)
	{
		tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!tmp)
			return (safe_return(NULL, stash, next_line));
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (ft_strchr(tmp, '\n') >= 0)
			*stash = make_line(NULL, tmp, ft_strchr(tmp, '\n'), BUFFER_SIZE);
		next_line = make_line(next_line, tmp, 0, ft_strlen(tmp));
	}
	if (read_bytes == -1 || (read_bytes == 0 && next_line[0] == 0))
		return (safe_return(NULL, stash, next_line));
	return (next_line);
}

char	*get_next_line(int fd)
{
	char	*next_line;
	char	**stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = get_stash();
	if (stash == NULL)
		return (NULL);
	next_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	return (process_read(fd, next_line, stash));
}

//##################DELETE :####################
#include <fcntl.h>
#include <stdio.h>
int main()
{
//norminette !
	int	fd;
	fd = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}