/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:41 by edufour           #+#    #+#             */
/*   Updated: 2023/04/21 15:31:05 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(int nb, int size)
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

char	*get_stash(void)
{
	static char	*stash;

	if (stash == NULL)
		stash = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
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
	new_line[i_new] = '\0';
	return (new_line);
}

char	*safe_return(char *return_str, char *free_stash, char *free_line)
{
	if (free_stash)
		free (free_stash);
	if (free_line)
		free (free_line);
	free_stash = NULL;
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

int	read_stash(char *stash, char *next_line)
{
	int	eol;
	int	end;

	end = 0;
	while (stash[end])
		end ++;
	eol = ft_strchr(stash, '\n');
	next_line = make_line(next_line, stash, 0, eol);
	//make_line();
	if (eol == end)
		return (FLAG_CONTINUE);
	return (FLAG_RETURN);
}

char	*process_read(int fd, char *next_line, char	*stash)
{
	char	*tmp;
	int		read_bytes;

	read_bytes = 1;
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (ft_strchr(tmp, '\n' != 1 && read_bytes > 0))
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == -1)
			return (safe_return(NULL, stash, next_line));
		next_line = make_line(next_line, tmp, 0, read_bytes);
	}
	if (read_bytes == 0 && tmp[0] == 0);	
}

char	*get_next_line(int fd)
{
	int		return_flag;
	char	*next_line;
	char	*stash;

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

#include <fcntl.h>
#include <stdio.h>

int main()
{
	int	fd;
	fd = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}