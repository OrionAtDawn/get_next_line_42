/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:53:01 by edufour           #+#    #+#             */
/*   Updated: 2023/04/07 12:03:22 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*Fix : if the end of the file was reached. Manage in read function ? 
(if read_size < BUFFER_SIZE && read_size > 0)
Yes.
And, if read returns 0, verify that next_line is empty. If not, return next_line.
Else, return NULL*/

//Beware when copying/moving stuff around, not to override something.

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

/* Processes the "stash". 
If "stash" is empty, returns NULL. (if i == 0)
If "stash" contains a '\n' (eol < i), calls "create_line" to create the segment to return, 
calls order_stash to re-order itself and sets return_flag to 1.
If "stash" does not contain a '\n'(if eol == i), calls "move_data" to update "next_line",
calls order_stash to empty itself and returns 0.
*/
char	*process_stash(char **stash, int *return_flag)
{
	int		i;
	int		eol;
	char	*segment;

	i = 0;
	eol = 0;
	while (stash[i] != 0)
		i++;
	if (i == 0)
		return (NULL);
	while (stash[eol] != '\n' && eol < i)
		eol ++;
	segment = create_line(*stash, "\0", 0, eol);
	order_stash(stash, *stash, eol);
	return (segment);
}

char	*process_read(int fd, char **stash, int *return_flag)
{
	int		read_bytes;
	char	*buff;
	char	*segment;
	int		i;
	int		eol;

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_bytes = read(fd, buff, BUFFER_SIZE);
	if (read_bytes == -1)
	{	
		return_flag = -1;
		return (NULL);
	}
	if (read_bytes = 0)
	{	
		return_flag = -2;
		return (NULL);
	}
	while (buff <)
}

/*
	Creates the return values of process_stash and process_read.
	Creates next_line from the return values of process_stash and process_read.
	Also handles the return_flag.
*/

char	*create_line(char *src, char *dst, int nb_bytes)
{
	
}

/*
sets the stash to 0.
Copies content from i_start to i_end in stash. 
*/
void	order_stash(char **stash, char *content, int i_start, int i_end)
{

}


