/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:31:58 by jalbiser          #+#    #+#             */
/*   Updated: 2025/02/21 14:47:47 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/gnl/get_next_line.h"
# include "../libft/libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_key
{
	char	*key;
	int		len;
	char	**target_char;
	int		**target_int;
}			t_key;

typedef struct s_data
{
	int		player_x;
	int		player_y;
	char	player_direction;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		*floor;
	int		*ceiling;
	char	**map;
}			t_data;

typedef struct s_parser_data
{
	t_key	keys[6];
	int		z;
}			t_parser_data;

t_data		parsing(char **args);
void		init_data(t_data *data);
bool		valid_extension(char *file);
bool		ft_str_is_numeric(char *str);
int			ft_split_count(char **split);
void		free_split(char **split);
void		free_data(t_data *data);
bool		ft_isspace(char c);
void		trim(char *str);
void		init_keys(t_key *keys, t_data *data);
int			parsed_color(int **target, char *value);
int			insert_key(char *value, char **target_char, int **target_int);
bool		is_empty_line(char *line);
int			verify_data(t_data *data, int print);
int			alloc_map_size(char *file, t_data *data);
int			valid_map(t_data *data);
int			get_position_player(t_data *data);
int			wall_map(t_data *data);
int			parser(char *file, t_data *data);
int			process_line(t_data *data, char *line, char *dup_line,
				t_parser_data *p_data);
int			handle_key_match(char *line, t_key *keys, int keys_i);
int			process_map_line(t_data *data, char *line, char *dup_line, int *z);

#endif
