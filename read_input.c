/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:10:10 by esafar            #+#    #+#             */
/*   Updated: 2021/12/12 19:40:39 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char	*ret_buffer(t_data *data, size_t *size)
{
	*size = data->sz + data->red;
	return (data->buff);
}

void	continue_reading(t_data *data)
{
	data->new_buffer = malloc(sizeof(char) * (data->sz + data->red + BUFF_SZ));
	if (data->new_buffer == NULL)
		exit(1);
	data->i = 0;
	while (data->i < data->sz + data->red)
	{
		data->new_buffer[data->i] = data->buff[data->i];
		data->i++;
	}
	while (data->i < data->sz + data->red + BUFF_SZ)
		data->new_buffer[data->i++] = 0;
	data->sz += data->red;
	data->tmp = data->buff;
	data->buff = data->new_buffer;
	free(data->tmp);
}

char	*rd_input(int fd, size_t *size)
{
	t_data	data;

	data.i = 0;
	data.sz = 0;
	data.buff = malloc(sizeof(char) * BUFF_SZ);
	if (!data.buff)
		exit(0);
	while (data.i < BUFF_SZ)
		data.buff[data.i++] = 0;
	while (true)
	{
		data.red = read(fd, data.buff + data.sz, BUFF_SZ);
		if (data.red < BUFF_SZ)
			return (ret_buffer(&data, size));
		else
			continue_reading(&data);
	}
	return (data.buff);
}
