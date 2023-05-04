/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:53:01 by edufour           #+#    #+#             */
/*   Updated: 2023/05/04 13:02:22 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> 
#include <stdlib.h>

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

void	*ft_calloc(size_t nb, size_t size)
{
	char	*buffer;
	size_t	i;

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

//Allocates enough memory to append 'add' to 'base', does the operation, 
//frees 'base' and returns the new allocated char *.
char	*ft_strjoin(char *base, char *add)
{
	char		*new_line;
	int			i_base;
	int			i_add;

	i_base = -1;
	i_add = -1;
	if (!base)
		base = calloc(1, 1);
	if (!add)
		return (NULL);
	new_line = malloc(ft_strlen(base) + ft_strlen(add) + 1);
	if (!new_line)
		return (NULL);
	while (base[++i_base])
		new_line[i_base] = base[i_base];
	free (base);
	base = NULL;
	while (add[++i_add])
		new_line[i_base + i_add] = add[i_add];
	new_line[i_base + i_add] = '\0';
	return (new_line);
}
