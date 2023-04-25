/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:41 by edufour           #+#    #+#             */
/*   Updated: 2023/04/25 13:41:15 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(int nb, int size)
{
	char	*buffer;
	int		i;

	if (nb < 0 || size < 0)
		return (NULL);
	buffer = malloc (nb * size);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < nb * size)
	{	
		buffer[i] = 0;
		i++;
	}
	return (buffer);
}

char	**get_stash(void)
{
	static char	**stash;

	if (stash == NULL)
		stash = ft_calloc(1, sizeof(char *));
	return (stash);
}

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

char	*safe_return(char *return_str, char **free_stash, char *free_line)
{
	if (*free_stash)
		free (*free_stash);
	if (free_stash)
		free (free_stash);
	if (free_line)
		free (free_line);
	free_stash = NULL;
	*free_stash = NULL;
	free_line = NULL;
	return (return_str);
}

int	ft_strchr(char *str, char search)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{	
		if (str[i] == search)
			return (i);
		i++;
	}
	return (-1);
}

int	read_stash(char **stash, char *next_line)
{
	int	eol;
	int	end;

	end = 0;
	while (*stash[end])
		end ++;
	eol = ft_strchr(*stash, '\n');
	if (eol == -1)
	{	
		next_line = make_line(next_line, stash, 0, end);
		return (FLAG_CONTINUE);
	}
	next_line = make_line(next_line, stash, 0, eol);
	return (FLAG_RETURN);
}

//calls read until an eol is found or read returns 0. Build next_line and saves, if needed, the unused
//str in stash.
char	*process_read(int fd, char *next_line, char	**stash)
{
	int		read_bytes;
	char	*tmp;

	while (ft_strchr(next_line, '\n') == 0 && read_bytes > 0)
	{
		tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!tmp)
			return (safe_return(NULL, next_line, stash));
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (ft_strchr(tmp, '\n') >= 0)
			*stash = make_line(NULL, tmp, ft_strchr(tmp, '\n'), BUFFER_SIZE);
		next_line = make_line(next_line, tmp, 0, ft_strlen(tmp));
	}
	if (read_bytes == -1 || read_bytes == 0 && next_line[0] == 0)
		return (safe_return(NULL, next_line, stash));
	return (next_line);
}

char	*get_next_line(int fd)
{
	int		return_flag;
	char	*next_line;
	char	**stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = get_stash();
	if (stash == NULL)
		return (NULL);
	next_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	return_flag = read_stash(stash, next_line);
	if (return_flag == FLAG_RETURN)
		return (safe_return(next_line, NULL, NULL));
	if (return_flag == FLAG_ERROR)
		return (safe_return(NULL, stash, next_line));
	process_read(fd, next_line, stash);
	return (next_line);
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