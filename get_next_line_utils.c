/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:53:01 by edufour           #+#    #+#             */
/*   Updated: 2023/05/03 11:41:43 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

int	ft_strchr(char *str, char search)
{
	size_t	i;

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

//frees, if needed, stash and any given line. Returns 'return_str'
char	*safe_return(char *return_str, char ***free_stash, char **free_line)
{
	if (**free_stash)
		free (**free_stash);
	**free_stash = NULL;
	if (*free_stash)
		free (*free_stash);
	*free_stash = NULL;
	if (*free_line)
		free (*free_line);
	*free_line = NULL;
	return (return_str);
}

void	*ft_calloc(size_t nb, size_t size)
{
	char	*buffer;

	if (nb < 0 || size < 0)
		return (NULL);
	buffer = malloc (nb * size);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, nb * size);
	return (buffer);
}
