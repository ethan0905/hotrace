/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:57:17 by esafar            #+#    #+#             */
/*   Updated: 2021/12/12 20:57:29 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	init_find_var(t_swt_hash *hash, \
	t_find *data, char *buf)
{
	hash->s = ft_hash(buf);
	data->k = 0;
	data->idx = hash->h.position % SZ;
}

inline void	find(t_hash_map *h_map, char *buf, size_t sz)
{
	t_swt_hash	hash;
	t_find		data;

	init_find_var(&hash, &data, buf);
	while (data.k < h_map->n_grp)
	{
		data.match = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_set1_epi8(
						hash.h.meta), h_map->groups[data.idx].metadata));
		if (data.match)
		{
			data.i = -1;
			while (++data.i < GROUP_SZ)
			{
				if (data.match & (1 << data.i) && \
				!ft_strcmp(buf, h_map->groups[data.idx].data[data.i]))
					return (write_to_buf(h_map->groups[data.idx].data[data.i]
							+ sz + 1, true));
			}
		}
		data.k++;
		data.idx += SZ;
	}
	write_to_buf(buf, false);
	write_to_buf(": Not found.", true);
}
