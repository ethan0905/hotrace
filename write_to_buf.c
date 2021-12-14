/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:39:27 by esafar            #+#    #+#             */
/*   Updated: 2021/12/12 20:39:41 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

size_t	check_if_idx_eq_bsize(t_writer *writer, size_t i)
{
	if (writer->idx == BUFF_SZ)
	{
		i = 0;
		write(STDOUT_FILENO, writer->buffer, BUFF_SZ);
		while (i < BUFF_SZ)
			writer->buffer[i++] = 0;
		writer->idx = 0;
	}
	return (i);
}

void	write_to_buf(char *str, bool nl)
{
	static t_writer	writer;
	size_t			i;

	if (str == NULL)
	{
		write(STDOUT_FILENO, writer.buffer, writer.idx);
		exit(1);
	}
	while (*str != '\0')
	{
		writer.buffer[writer.idx] = *str;
		writer.idx++;
		str++;
		i = check_if_idx_eq_bsize(&writer, i);
	}
	if (nl)
	{
		writer.buffer[writer.idx++] = '\n';
		i = check_if_idx_eq_bsize(&writer, i);
	}
}
