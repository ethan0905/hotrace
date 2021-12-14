/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:44:44 by esafar            #+#    #+#             */
/*   Updated: 2021/12/12 19:40:34 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	iter_pointer_and_insert_h(t_hash_map *h_map, \
		t_parse *data, t_bounds *bd, char *buffer)
{
	++bd->end;
	while (buffer[bd->end] != '\n' && buffer[bd->end] != 0)
		bd->end++;
	data->c = buffer[bd->end];
	buffer[bd->end] = 0;
	insert(h_map, &buffer[bd->begin]);
	if (data->c == 0)
		exit(1);
	bd->begin = bd->end + 1;
	bd->end = bd->begin;
}

void	parse_input(t_hash_map *h_map, char *buffer, t_bounds *bd)
{
	t_parse	data;

	bd->begin = 0;
	bd->end = 0;
	while (true)
	{
		data.c = buffer[bd->end];
		if (data.c == 0)
			exit(1);
		if (data.c == '\n')
		{
			buffer[bd->end] = 0;
			data.sz = bd->end - bd->begin;
			if (data.sz == 0)
				break ;
			iter_pointer_and_insert_h(h_map, &data, bd, buffer);
		}
		else
			bd->end++;
	}
}
