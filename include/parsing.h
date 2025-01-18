/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:31:58 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/18 02:46:37 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft/libft.h"
# include "../libft/gnl/get_next_line.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_data
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		*floor;
	int		*ceiling;
	char	**map;
}			t_data;

int	parsing(char **args, t_data *data);

#endif
