/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 15:25:45 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-24 15:25:45 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parser(char *file, t_data *data)
{
	int fd;
	char *line;
	t_key keys[6];
	int keys_i;
	bool found;
	char *dup_line;
	int z;

	z = 0;
	if (!alloc_map_size(file, data))
		return (printf("Error: failed to alloc map\n"), 0);
	init_keys(keys, data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error: failed to open the file\n"), 0);
	while ((line = get_next_line(fd)) != NULL)
	{
		dup_line = ft_strdup(line);
		trim(line);
		if (*line == '\0') // Ignorer les lignes vides
		{
			free(line);
			free(dup_line);
			continue ;
		}
		found = false;
		keys_i = 0;
		while (keys_i < 6)
		{
			if (ft_strncmp(line, keys[keys_i].key, keys[keys_i].len) == 0
				&& ft_isspace(line[keys[keys_i].len]))
			{
				found = true;
				if (!insert_key(line + keys[keys_i].len,
						keys[keys_i].target_char, keys[keys_i].target_int))
				{
					free(line);
					free(dup_line);
					close(fd);
					return (0);
				}
				break ;
			}
			keys_i++;
		}
		if (!found && !is_empty_line(line))
			// Fonction à ajouter pour vérifier les lignes vides
		{
			if (ft_strrchr("01", line[0]) && verify_data(data, 0))
			{
				if (dup_line[ft_strlen(dup_line) - 1] == '\n')
					data->map[z] = ft_strndup(dup_line, (ft_strlen(dup_line)
								- 1));
				else
					data->map[z] = ft_strdup(dup_line);
				z++;
			}
			else
			{
				printf("Error: problem with the file");
				free(data->map);
				data->map = NULL;
				free(line);
				free(dup_line);
				close(fd);
				return (0);
			}
		}
		free(line);
		free(dup_line);
	}
	data->map[z] = NULL;
	close(fd);
	return (verify_data(data, 1));
}
