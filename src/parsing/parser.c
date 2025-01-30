/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:25:45 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/30 20:02:47 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	process_map_line(t_data *data, char *line, char *dup_line, int *z)
{
	if (ft_strrchr("01", line[0]) && verify_data(data, 0))
	{
		if (dup_line[ft_strlen(dup_line) - 1] == '\n')
			data->map[*z] = ft_strndup(dup_line, (ft_strlen(dup_line) - 1));
		else
			data->map[*z] = ft_strdup(dup_line);
		(*z)++;
		return (1);
	}
	printf("Error: problem with the file\n");
	free(data->map);
	data->map = NULL;
	return (0);
}

int	handle_key_match(char *line, t_key *keys, int keys_i)
{
	if (!insert_key(line + keys[keys_i].len, keys[keys_i].target_char,
			keys[keys_i].target_int))
		return (0);
	return (1);
}

static int	cleanup_and_exit(char *line, char *dup_line, int fd)
{
	free(line);
	free(dup_line);
	close(fd);
	return (0);
}

static int	init_parser(char *file, t_data *data, t_parser_data *p_data,
		int *fd)
{
	p_data->z = 0;
	if (!alloc_map_size(file, data))
		return (printf("Error: failed to alloc map\n"), 0);
	init_keys(p_data->keys, data);
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		return (printf("Error: failed to open the file\n"), 0);
	return (1);
}

int	parser(char *file, t_data *data)
{
	int				fd;
	char			*line;
	t_parser_data	p_data;
	char			*dup_line;

	if (!init_parser(file, data, &p_data, &fd))
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		dup_line = ft_strdup(line);
		trim(line);
		if (*line != '\0' && !process_line(data, line, dup_line, &p_data))
			return (cleanup_and_exit(line, dup_line, fd));
		free(line);
		free(dup_line);
		line = get_next_line(fd);
	}
	data->map[p_data.z] = NULL;
	close(fd);
	return (verify_data(data, 1));
}
