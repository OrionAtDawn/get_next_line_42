/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:47:16 by edufour           #+#    #+#             */
/*   Updated: 2023/04/07 11:49:25 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 'return_signal' :
if 0  -> continue
if 1  -> return 'next_line'
if -1 -> return NULL (error)
if -2 -> nothing to read (if next_line is empty, return -1, else return next_line)
*/

/*
1 : Process stash. 
If it is empty, return NULL and set return_value to 0.
If it contains a \n, return the content until \n (included) is found. Set return value to 1. If there is something after the \n, order the stash. Else reset it. 
If it did not contain an eol, return the whole content of the stash and set return value to 0.

2 : Process read.
Call read. (read_bytes = read(fd, read_line, BUFFER_SIZE))
If read returns 0, verify that next_line is empty. If not, return 1. Else return -1.
If read returns -1, return -1.
**the end of read_line is not BUFFER_SIZE. It's read_bytes.
If read returns > 0 and contains an eol, move it's content up to the oel into next_line(read_line[0] - read_line[i]). 
 Store the rest in the stash(read_line[i] - read_line[read_bytes]), and return 1.
If it does not contain an eol, move it's content to next_line (read_line[0]-read_line[read_bytes]) and call the function process_read again.

Side functions : 
	cat_line(char **src, char **dst, int index, int n) : 
		Copies n bytes from src[index] to the end of dst.
	
	order_stash(char **stash, int n) :
		shifts every character from the n'th + 1 to n bytes to the right. Sets the n last bytes to 0.
*/

char	*get_next_line(int fd)
{
	int			*return_flag;

	return_flag = 0; n
}