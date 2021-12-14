/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:38:03 by esafar            #+#    #+#             */
/*   Updated: 2021/12/12 19:36:59 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	hotrace(void)
{
	char		*buffer;
	t_hash_map	h_map;
	t_bounds	bd;
	size_t		size;

	size = 0;
	buffer = rd_input(0, &size);
	h_map.n_grp = 1;
	init_hash_map(&h_map);
	parse_input(&h_map, buffer, &bd);
	fetch_data(&h_map, buffer, &bd);
	free(buffer);
	free(h_map.groups);
	write_to_buf(NULL, true);
}

int	main(void)
{
	hotrace();
	return (0);
}
