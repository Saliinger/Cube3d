/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:31:58 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/18 16:49:18 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft/libft.h"
# include "../libft/gnl/get_next_line.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_key
{
	char	*key;
	int		len;
	char	**target_char;
	int		**target_int;
}		t_key;


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

t_data		parsing(char **args);

#endif
