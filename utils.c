/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:59:53 by frthierr          #+#    #+#             */
/*   Updated: 2021/12/12 19:41:02 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

size_t	ft_hash(char *str)
{
	size_t	hash;
	size_t	prime;

	if (sizeof(size_t) == 8)
		hash = 0xcbf29ce484222325ull;
	else
		hash = 0x811c9dc5ull;
	if (sizeof(size_t) == 8)
		prime = 1099511628211ull;
	else
		prime = 16777619ull;
	while (*str != '\0')
	{
		hash ^= *str++;
		hash *= prime;
	}
	return (hash);
}

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (len--)
		*d++ = *s++;
	return (dest);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while ((t1[i] != '\0' || t2[i] != '\0'))
	{
		if (t1[i] != t2[i])
			return (t1[i] - t2[i]);
		else
			i++;
	}
	return (0);
}

void	init_hash_map(t_hash_map *h_map)
{
	size_t		i;
	size_t		j;
	size_t		mapsize;

	i = 0;
	j = 0;
	mapsize = SZ * sizeof(t_group);
	h_map->groups = malloc(mapsize);
	while (i < SZ)
	{
		h_map->groups[i].metadata = _mm_set1_epi8((char)SWT_EMPTY);
		j = 0;
		while (j < GROUP_SZ)
			h_map->groups->data[j++] = NULL;
		i++;
	}
}

void	fetch_data(t_hash_map *h_map, char *buffer, t_bounds *bd)
{
	char	c;
	size_t	sz;

	bd->end++;
	bd->begin = bd->end;
	while (true)
	{
		c = buffer[bd->end];
		if (c == '\n' || c == 0)
		{
			sz = bd->end - bd->begin;
			if (sz == 0)
				return ;
			buffer[bd->end] = 0;
			find(h_map, &buffer[bd->begin], sz);
			if (c == 0)
				return ;
			bd->end++;
			bd->begin = bd->end;
		}
		else
			bd->end++;
	}
}
