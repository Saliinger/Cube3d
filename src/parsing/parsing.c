/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:32:16 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/18 02:47:59 by jalbiser         ###   ########.fr       */
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

void	parsed_color(char *colors, t_data *data, int type)
{
	char	**values;
	int		i;
	int		val;

	values = ft_split(colors, ',');
	if (!values)
		return ;
	if (ft_split_count(values) != 3)
	{
		free_split(values);
		return ;
	}
	if (type)
		data->ceiling = malloc(sizeof(int) * 3);
	else
		data->floor = malloc(sizeof(int) * 3);
	i = 0;
	while (values[i])
	{
		if (ft_strlen(values[i]) > 3 || (val = ft_atoi(values[i])) < 0
			|| val > 255)
		{
			free_split(values);
			return ;
		}
		if (type)
			data->ceiling[i] = val;
		else
			data->floor[i] = val;
		i++;
	}
	free_split(values);
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
		parsed_color(line + i, data, 0);
	else if (ft_strcmp(type, "C") == 0 && !data->ceiling)
		parsed_color(line + i, data, 1);
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

int	get_map(char *file, t_data *data)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		
		free(line);
	}
}

int	parsing(char **args, t_data *data)
{
	if (!args[1])
		return (printf("Error: No file provided\n"), 0);
	if (!ends_with_cub(args[1]))
		return (printf("Error: The file must have the .cub extension\n"), 0);
	if (!get_keys(args[1], data))
		return (printf("Error: Failed to recover keys\n"), 0);
	// if (!get_map(args[1], data))
	// 	return (printf("Error: failed to get map information"), 0);
	return (1);
}
int	main(int argc, char **argv)
{
	t_data data;
	int ret;

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
			printf("%s", data.map[i]);
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