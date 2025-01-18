/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:32:16 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/18 15:47:06 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_split_count(char **split)
{
	int	count;

	if (!split)
		return (0);
	count = 0;
	while (split[count])
		count++;
	return (count);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

bool	ends_with_cub(const char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	parsed_color(char *colors, t_data *data, int type)
{
	char	**values;
	int		i;
	int		val;

	values = ft_split(colors, ',');
	if (!values)
		return (0);
	if (ft_split_count(values) != 3 || values[2][0] == '\n')
	{
		free_split(values);
		return (0);
	}
	if (type)
		data->ceiling = malloc(sizeof(int) * 3);
	else
		data->floor = malloc(sizeof(int) * 3);
	i = 0;
	while (values[i])
	{
		val = ft_atoi(values[i]);
		if (val < 0 || val > 255 || values[i][0] == '-')
		{
			free_split(values);
			return (0);
		}
		if (type)
			data->ceiling[i] = val;
		else
			data->floor[i] = val;
		i++;
	}
	free_split(values);
	return (1);
}

int	key_insert(char *type, t_data *data, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strcmp(type, "NO") == 0 && !data->no_texture)
		data->no_texture = ft_strndup(line + i, (ft_strlen(line) - i - 1));
	else if (ft_strcmp(type, "SO") == 0 && !data->so_texture)
		data->so_texture = ft_strndup(line + i, (ft_strlen(line) - i - 1));
	else if (ft_strcmp(type, "WE") == 0 && !data->we_texture)
		data->we_texture = ft_strndup(line + i, (ft_strlen(line) - i - 1));
	else if (ft_strcmp(type, "EA") == 0 && !data->ea_texture)
		data->ea_texture = ft_strndup(line + i, (ft_strlen(line) - i - 1));
	else if (ft_strcmp(type, "F") == 0 && !data->floor)
	{
		if (!parsed_color(line + i, data, 0))
			return (0);
	}
	else if (ft_strcmp(type, "C") == 0 && !data->ceiling)
	{
		if (!parsed_color(line + i, data, 1))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	key_verif(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO", 2) == 0 && (line[2] && line[2] == ' '))
	{
		if (!key_insert("NO", data, line + 3))
			return (0);
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && (line[2] && line[2] == ' '))
	{
		if (!key_insert("SO", data, line + 3))
			return (0);
	}
	else if (ft_strncmp(line, "WE", 2) == 0 && (line[2] && line[2] == ' '))
	{
		if (!key_insert("WE", data, line + 3))
			return (0);
	}
	else if (ft_strncmp(line, "EA", 2) == 0 && (line[2] && line[2] == ' '))
	{
		if (!key_insert("EA", data, line + 3))
			return (0);
	}
	else if ((line[0] && line[0] == 'F') && (line[1] && line[1] == ' '))
	{
		if (!key_insert("F", data, line + 2))
			return (0);
	}
	else if ((line[0] && line[0] == 'C') && (line[1] && line[1] == ' '))
	{
		if (!key_insert("C", data, line + 2))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	get_keys(char *file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		if (ft_strchr(" 01", line[0]))
			break ;
		if (line[0] != '\0' && line[0] != '\n')
		{
			if (!key_verif(line, data))
				return (free(line), 0);
		}
		free(line);
	}
	return (1);
}

int	get_map_size(char *file, t_data *data)
{
	char	*line;
	int		fd;
	int		started;
	int		index;

	index = 0;
	started = 0;
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strchr(" 01", line[0]))
			started = 1;
		if (started)
			index++;
		free(line);
	}
	if (index)
	{
		data->map = malloc(sizeof(char *) * index);
		if (!data->map)
			return (0);
	}
	return (index);
}

int	get_map(char *file, t_data *data)
{
	char	*line;
	int		fd;
	int		started;
	int		index;

	index = 0;
	started = 0;
	fd = open(file, O_RDONLY);
	if (!get_map_size(file, data))
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strchr(" 01", line[0]))
			started = 1;
		if (started)
		{
			if (line[ft_strlen(line) - 1] == '\n')
				data->map[index] = ft_strndup(line, (ft_strlen(line) - 1));
			else
				data->map[index] = ft_strdup(line);
			index++;
		}
		free(line);
	}
	data->map[index] = NULL;
	return (1);
}

int	wall_map(t_data *data)
{
	int	i;
	int	a;

	// Vérifier la première ligne
	i = 0;
	while (data->map[0][i])
	{
		if (data->map[0][i] != '1' && data->map[0][i] != ' ')
			return (0); // La map n'est pas bien entourée de murs
		i++;
	}
	// Vérifier les lignes intermédiaires
	i = 1;
	while (data->map[i + 1]) // Exclure la dernière ligne
	{
		a = 0;
		// Ignorer les espaces au début
		while (data->map[i][a] && data->map[i][a] == ' ')
			a++;
		if (data->map[i][a] != '1') // Le premier mur
			return (0);
		// Aller à la fin en ignorant les espaces
		while (data->map[i][a])
			a++;
		a--;
		while (a >= 0 && data->map[i][a] == ' ')
			a--;
		if (data->map[i][a] != '1') // Le dernier mur
			return (0);
		i++;
	}
	// Vérifier la dernière ligne
	a = 0;
	while (data->map[i][a])
	{
		if (data->map[i][a] != '1' && data->map[i][a] != ' ')
			return (0); // La map n'est pas bien entourée de murs
		a++;
	}
	return (1); // La map est bien entourée de murs
}

int	verif_map(t_data *data)
{
	if (!wall_map(data))
		return (0);
	return (1);
}

int	verif_keys(t_data *data)
{
	if (!data->so_texture || !data->no_texture || !data->we_texture
		|| !data->ea_texture || !data->floor || !data->ceiling)
		return (0);
	return (1);
}

int	get_position_player(t_data *data)
{
	int	i;
	int	a;

	i = 0;
	while (data->map[i])
	{
		a = 0;
		while (data->map[i][a])
		{
			if (ft_strchr("NSWE", data->map[i][a]))
			{
				if (!data->direction && data->x == -1 && data->y == -1)
				{
					data->direction = data->map[i][a];
					data->y = i;
					data->x = a;
				}
				else
					return (0);
			}
			a++;
		}
		i++;
	}
	if (!data->direction)
		return (0);
	return (1);
}

int	parsing(char **args, t_data *data)
{
	if (!args[1])
		return (printf("Error: No file provided\n"), 0);
	if (!ends_with_cub(args[1]))
		return (printf("Error: The file must have the .cub extension\n"), 0);
	if (!get_keys(args[1], data))
		return (printf("Error: Failed to recover keys\n"), 0);
	if (!verif_keys(data))
		return (printf("Error: Failed to recover keys\n"), 0);
	if (!get_map(args[1], data))
		return (printf("Error: failed to get map information\n"), 0);
	if (!verif_map(data))
		return (printf("Error: the map is not valid\n"), 0);
	if (!get_position_player(data))
		return (printf("Error: problem retrieving player position\n"), 0);
	return (1);
}
int	main(int argc, char **argv)
{
	t_data data;
	int ret;

	data.x = -1;
	data.y = -1;
	data.direction = '\0';
	data.no_texture = NULL;
	data.so_texture = NULL;
	data.we_texture = NULL;
	data.ea_texture = NULL;
	data.map = NULL;
	data.ceiling = NULL;
	data.floor = NULL;

	// Appel de la fonction parsing
	ret = parsing(argv, &data);

	if (ret == 1)
	{
		// Affichage des résultats de la parsing
		printf("Parsing successful!\n");

		printf("PLAYER direction: %c\n", data.direction);
		printf("PLAYER X: %d\n", data.x);
		printf("PLAYER Y: %d\n", data.y);

		printf("NO texture: %s\n", data.no_texture);
		printf("SO texture: %s\n", data.so_texture);
		printf("WE texture: %s\n", data.we_texture);
		printf("EA texture: %s\n", data.ea_texture);
		printf("Floor color: %d, %d, %d\n", data.floor[0], data.floor[1],
			data.floor[2]);
		printf("Ceiling color: %d, %d, %d\n", data.ceiling[0], data.ceiling[1],
			data.ceiling[2]);

		printf("Map:\n");
		for (int i = 0; data.map[i] != NULL; i++)
			printf("%s\n", data.map[i]);
	}
	else
	{
		// Affichage d'un message d'erreur en cas d'échec
		printf("Parsing failed!\n");
	}

	// Libérer la mémoire allouée
	if (data.no_texture)
		free(data.no_texture);
	if (data.so_texture)
		free(data.so_texture);
	if (data.we_texture)
		free(data.we_texture);
	if (data.ea_texture)
		free(data.ea_texture);
	if (data.map)
	{
		for (int i = 0; data.map[i] != NULL; i++)
			free(data.map[i]);
		free(data.map);
	}

	return (0);
}