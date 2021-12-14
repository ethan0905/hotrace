/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 10:33:49 by esafar            #+#    #+#             */
/*   Updated: 2021/12/12 19:33:01 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <unistd.h>
# include <stdbool.h>  
# include <stdio.h>
# include <stdlib.h>
# include <x86intrin.h>
# include <string.h>

# define BUFF_SZ 4096 // buffer size
# define GROUP_SZ 16
# define SZ 4096

typedef struct s_group
{
	__m128i	metadata;
	char	*data[GROUP_SZ];
}				t_group;

typedef struct s_hash_map
{
	t_group	*groups;
	size_t	n_grp;
}				t_hash_map;

struct					s_swt_hash
{
	size_t				meta : 7;
	size_t				position : 57;
};

typedef union u_swt_hash
{
	struct s_swt_hash	h;
	size_t				s;
}				t_swt_hash;

typedef enum e_metadata
{
	SWT_EMPTY = 0b10000000,
	SWT_FULL_MASK = 0b01111111
}				t_metadata;

typedef struct s_bounds
{
	size_t	begin;
	size_t	end;
}				t_bounds;

typedef struct s_data
{
	char	*buff;
	char	*new_buffer;
	char	*tmp;
	size_t	sz;
	size_t	red;
	size_t	i;
}				t_data;

typedef struct s_parse
{
	char	c;
	size_t	sz;
}				t_parse;

typedef struct s_writer
{
	char	buffer[BUFF_SZ];
	size_t	idx;
}				t_writer;

typedef struct s_insert
{
	size_t		idx;
	int			match;
	size_t		k;
	size_t		i;
}				t_insert;

typedef struct s_expand
{
	size_t	i;
	size_t	j;
	size_t	mx;
	size_t	idx;
}				t_expand;

typedef struct s_find
{
	size_t		idx;
	int			i;
	int			match;
	size_t		k;
}				t_find;

//READ INPUT
char	*rd_input(int fd, size_t *size);
void	continue_reading(t_data *data);
char	*ret_buffer(t_data *data, size_t *size);

void	parse_input(t_hash_map *h_map, char *buffer, t_bounds *bd);
void	iter_pointer_and_insert_h(t_hash_map *h_map, t_parse *data, \
				t_bounds *bd, char *buffer);

void	insert(t_hash_map *h_map, char *buf);
void	need_space(t_hash_map *h_map, t_swt_hash hash, \
	t_insert data, char *buf);
void	init_data(t_hash_map *h_map, t_expand *data, t_group *tmp);
void	expand_map(t_hash_map *h_map, char *buf, t_swt_hash hash);

size_t	ft_hash(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	find(t_hash_map *h_map, char *buf, size_t sz);
void	init_find_var(t_swt_hash *hash, t_find *data, char *buf);

void	init_hash_map(t_hash_map *h_map);
void	fetch_data(t_hash_map *h_map, char *buffer, t_bounds *bd);

void	write_to_buf(char *str, bool nl);
size_t	check_if_idx_eq_bsize(t_writer *writer, size_t i);

int		ft_strcmp(const char *s1, const char *s2);

#endif