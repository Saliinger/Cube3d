/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:34:12 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/30 19:34:36 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	process_line(t_data *data, char *line, char *dup_line,
		t_parser_data *p_data)
{
	int		keys_i;
	bool	found;

	found = false;
	keys_i = 0;
	while (keys_i < 6)
	{
		if (ft_strncmp(line, p_data->keys[keys_i].key,
				p_data->keys[keys_i].len) == 0
			&& ft_isspace(line[p_data->keys[keys_i].len]))
		{
			found = true;
			if (!handle_key_match(line, p_data->keys, keys_i))
				return (0);
			break ;
		}
		keys_i++;
	}
	if (!found && !is_empty_line(line))
		if (!process_map_line(data, line, dup_line, &p_data->z))
			return (0);
	return (1);
}
