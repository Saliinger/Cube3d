/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:32:16 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/18 00:59:05 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

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

int	parse_color(char *color, t_data *data, int type)
{
	char	**values;
	int		i;
	int		val;

	values = ft_split(color, ',');
	if (!values)
		return (0);
	if (ft_split_count(values) != 3)
	{
		free_split(values);
		return (0);
	}
	i = 0;
	while (values[i])
	{
		if (ft_strlen(values[i]) > 3 || (val = ft_atoi(values[i])) < 0
			|| val > 255)
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

int	calcul_map_size(char *file)
{
	int		size;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	size = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\0' && line[0] != '\n' && 
			!(ft_strncmp(line, "NO ", 3) == 0 || 
			ft_strncmp(line, "SO ", 3) == 0 || 
			ft_strncmp(line, "WE ", 3) == 0 || 
			ft_strncmp(line, "EA ", 3) == 0 || 
			ft_strncmp(line, "F ", 2) == 0 || 
			ft_strncmp(line, "C ", 2) == 0))
		{
			size++;
		}
		free(line);
	}
	close(fd);
	return (size);
}


int	parser(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		map_started;
	int		z;
	int		map_size;

	z = 0;
	map_size = calcul_map_size(file);
	data->map = malloc(sizeof(char *) * map_size);
	if (!data->map)
		return (0);
	map_started = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			data->no_texture = ft_strdup(line + 3);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			data->so_texture = ft_strdup(line + 3);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			data->we_texture = ft_strdup(line + 3);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			data->ea_texture = ft_strdup(line + 3);
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (!parse_color(line + 2, data, 0))
				return (0);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (!parse_color(line + 2, data, 1))
				return (0);
		}
		else if (!map_started && line[0] != '\0' && line[0] != '\n')
		{
			map_started = 1;
		}
		if (map_started)
		{
			if (line[0] != '\0')
			{
				data->map[z] = ft_strdup(line);
				z++;
			}
		}
		free(line);
	}
	data->map[z] = NULL;
	close(fd);
	return (1);
}

//int	verif_parser(t_data *data)
//{
//	if (!data->ceiling || !data->floor || !data->no_texture || !data->so_texture
//		|| !data->ea_texture || !data->we_texture || !data->map)
//		return (1);
//	return (0);
//}

int	parsing(char **args, t_data *data)
{
	if (!args[1])
		return (printf("Error: No file provided\n"), 1);
	if (!ends_with_cub(args[1]))
		return (printf("Error: The file must have the .cub extension\n"), 1);
	if (!parser(args[1], data))
		return (printf("Error: the analysis could not be completed\n"), 1);
//	if (verif_parser(data))
//		return (printf("Error: the analysis could not be completed\n"), 1);
	return (0);
}

//int main(int argc, char **argv)
//{
//	t_data data;
//	int ret;
//
//	data.no_texture = NULL;
//	data.so_texture = NULL;
//	data.we_texture = NULL;
//	data.ea_texture = NULL;
//	data.map = NULL;
//
//	// Appel de la fonction parsing
//	ret = parsing(argv, &data);
//
//	if (ret == 0)
//	{
//		// Affichage des résultats de la parsing
//		printf("Parsing successful!\n");
//		printf("NO texture: %s\n", data.no_texture);
//		printf("SO texture: %s\n", data.so_texture);
//		printf("WE texture: %s\n", data.we_texture);
//		printf("EA texture: %s\n", data.ea_texture);
//		printf("Floor color: %d, %d, %d\n", data.floor[0], data.floor[1], data.floor[2]);
//		printf("Ceiling color: %d, %d, %d\n", data.ceiling[0], data.ceiling[1], data.ceiling[2]);
//
//		printf("Map:\n");
//		for (int i = 0; data.map[i] != NULL; i++)
//			printf("%s", data.map[i]);
//	}
//	else
//	{
//		// Affichage d'un message d'erreur en cas d'échec
//		printf("Parsing failed!\n");
//	}
//
//	// Libérer la mémoire allouée
//	if (data.no_texture)
//		free(data.no_texture);
//	if (data.so_texture)
//		free(data.so_texture);
//	if (data.we_texture)
//		free(data.we_texture);
//	if (data.ea_texture)
//		free(data.ea_texture);
//	if (data.map)
//	{
//		for (int i = 0; data.map[i] != NULL; i++)
//			free(data.map[i]);
//		free(data.map);
//	}
//
//	return 0;
//}