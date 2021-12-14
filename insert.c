/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:41:47 by esafar            #+#    #+#             */
/*   Updated: 2021/12/12 20:42:09 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	need_space(t_hash_map *h_map, t_swt_hash hash, t_insert data, char *buf)
{
	((char *)&h_map->groups[data.idx].metadata)[data.i] = (char)hash.h.meta;
	h_map->groups[data.idx].data[data.i] = buf;
}

void	insert(t_hash_map *h_map, char *buf)
{
	t_swt_hash	hash;
	t_insert	data;

	hash.s = ft_hash(buf);
	data.k = 0;
	data.idx = hash.h.position % SZ;
	while (data.k < h_map->n_grp)
	{
		data.i = -1;
		data.match = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_set1_epi8(
						(char)SWT_EMPTY), h_map->groups[data.idx].metadata));
		if (data.match)
		{
			while (++data.i < GROUP_SZ)
			{
				if (data.match & (1 << data.i))
					return (need_space(h_map, hash, data, buf));
			}
		}
		data.idx += SZ;
		data.k++;
	}
	expand_map(h_map, buf, hash);
}

void	init_data(t_hash_map *h_map, t_expand *data, t_group *tmp)
{
	h_map->groups = tmp;
	data->i = SZ * h_map->n_grp;
	data->mx = SZ * (h_map->n_grp + 1);
}

void	expand_map(t_hash_map *h_map, char *buf, t_swt_hash hash)
{
	t_group		*tmp;
	t_expand	data;

	tmp = malloc(sizeof(t_group) * SZ * (h_map->n_grp + 1));
	ft_memcpy(tmp, h_map->groups, sizeof(t_group) * SZ * h_map->n_grp);
	free(h_map->groups);
	init_data(h_map, &data, tmp);
	while (data.i < data.mx)
	{
		h_map->groups[data.i].metadata = _mm_set1_epi8((char)SWT_EMPTY);
		data.j = 0;
		while (data.j < GROUP_SZ)
		{
			h_map->groups[data.i].data[data.j] = NULL;
			data.j++;
		}
		data.i++;
	}
	data.idx = (hash.h.position % SZ) + SZ * (h_map->n_grp);
	h_map->n_grp++;
	((char *)&h_map->groups[data.idx].metadata)[0] = (char)hash.h.meta;
	h_map->groups[data.idx].data[0] = buf;
}
