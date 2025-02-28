/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:06:01 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/30 19:15:04 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_data	parsing(char **args)
{
	t_data	result;

	init_data(&result);
	if (!args[1])
		return (printf("Error: No file provided\n"), exit(1), result);
	if (!valid_extension(args[1]))
		return (printf("Error: The file must have the .cub extension\n"),
			exit(1), result);
	if (!parser(args[1], &result))
		return (free_data(&result), exit(1), result);
	if (!wall_map(&result))
		return (free_data(&result), exit(1), result);
	if (!get_position_player(&result))
		return (free_data(&result), exit(1), result);
	if (!valid_map(&result))
		return (free_data(&result), exit(1), result);
	return (result);
}
