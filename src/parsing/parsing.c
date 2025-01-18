/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:32:16 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/18 19:20:47 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

bool ft_str_is_numeric(const char *str)
{
    if (!str || !*str)
        return (false);
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (false);
        str++;
    }
    return (true);
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

void free_data(t_data *data)
{
    int i;

    i = 0;
    free(data->no_texture);
    free(data->so_texture);
    free(data->we_texture);
    free(data->ea_texture);
    free(data->floor);
    free(data->ceiling);

    if (data->map)
    {
        while (data->map[i])
        {
            free(data->map[i]);
            data->map[i] = NULL;
            i++;
        }
        free(data->map);
        data->map = NULL;
    }
}

void	init_data(t_data *data)
{
	data->player_x = -1;
	data->player_y = -1;
	data->player_direction = '\0';
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	data->map = NULL;
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void trim(char *str)
{
    int start = 0;
    int end = ft_strlen(str) - 1;

    while (str[start] && ft_isspace((unsigned char)str[start]))
        start++;
    while (end >= start && ft_isspace((unsigned char)str[end]))
        end--;
    int length = end - start + 1;
    ft_memmove(str, str + start, length);
    str[length] = '\0';
}

void	init_keys(t_key *keys, t_data *data)
{
	keys[0] = (t_key){"NO", 2, &data->no_texture, NULL};
	keys[1] = (t_key){"SO", 2, &data->so_texture, NULL};
	keys[2] = (t_key){"WE", 2, &data->we_texture, NULL};
	keys[3] = (t_key){"EA", 2, &data->ea_texture, NULL};
	keys[4] = (t_key){"F", 1, NULL, &data->floor};
	keys[5] = (t_key){"C", 1, NULL, &data->ceiling};
}

int parsed_color(int **target, char *value)
{
    char    **values;
    int     val;
    int     i;

    i = 0;
    values = ft_split(value, ',');
    if (!values || ft_split_count(values) != 3)
        return (free_split(values), 0);
    *target = malloc(sizeof(int) * 3);
    if (!*target)
        return (free_split(values), 0);
    while (values[i])
    {
        trim(values[i]);  // Ajout du trim pour gérer les espaces
        if (!ft_str_is_numeric(values[i])) // Vérification que c'est bien un nombre
            return (free(*target), free_split(values), 0);
        val = ft_atoi(values[i]);
        if (val < 0 || val > 255)
            return (free(*target), free_split(values), 0);
        (*target)[i] = val;
        i++;
    }
    free_split(values);
    return (1);
}

int insert_key(char *value, char **target_char, int **target_int)
{
    if (!value)
        return (0);
    trim(value);
    if (target_char)
    {
        if (*target_char)  // Éviter les fuites mémoire
            free(*target_char);
        *target_char = ft_strdup(value);
        if (!*target_char)
            return (0);
    }
    else if (target_int)
    {
        if (!parsed_color(target_int, value))
            return (0);
    }
    return (1);
}
static bool is_empty_line(const char *line)
{
    while (*line)
    {
        if (!ft_isspace(*line))
            return (false);
        line++;
    }
    return (true);
}

static int verify_data(t_data *data)
{
    if (!data->no_texture || !data->so_texture || !data->we_texture || 
        !data->ea_texture || !data->floor || !data->ceiling)
    {
        printf("Error: Missing required configuration elements\n");
        return (0);
    }
    return (1);
}

int	alloc_map_size(char *file, t_data *data)
{
    int     fd;
    char    *line;
	int		i;

	i = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (printf("Error: failed to open the file\n"), 0);
    while ((line = get_next_line(fd)) != NULL)
    {
        trim(line);
		if (ft_strrchr("01", line[0]))
			i++;
        free(line);
    }
    close(fd);
	if (i)
		data->map = malloc(sizeof(char *) * (i + 1));
	else
		return (0);
    return (1);
}

int parser(char *file, t_data *data)
{
    int     fd;
    char    *line;
    t_key   keys[6];
    int     keys_i;
    bool    found;
	char	*dup_line;
	int		z;

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
        if (*line == '\0')  // Ignorer les lignes vides
        {
            free(line);
			free(dup_line);
            continue;
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
                break;
            }
            keys_i++;
        }
        if (!found && !is_empty_line(line))  // Fonction à ajouter pour vérifier les lignes vides
        {
			if (ft_strrchr("01", line[0]))
			{
				if (dup_line[ft_strlen(dup_line) - 1] == '\n')
					data->map[z] = ft_strndup(dup_line, (ft_strlen(dup_line) - 1));
				else
					data->map[z] = ft_strdup(dup_line);
				z++;
			}
			else
			{
				printf("Error: Invalid identifier in line: %s\n", line);
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
    return (verify_data(data));  // Fonction à ajouter pour vérifier que toutes les données sont présentes
}

int check_adjacent_spaces(t_data *data, int i, int j)
{
    // Si on trouve un espace, vérifier qu'il est entouré de murs ou d'autres espaces
    if (data->map[i][j] == ' ')
        return (1);
    
    // Si c'est un mur, c'est toujours valide
    if (data->map[i][j] == '1')
        return (1);
    
    // Pour les autres caractères (0, N, S, E, W), vérifier qu'ils sont entourés correctement
    // Vérifier la ligne au-dessus
    if (i == 0 || !data->map[i - 1][j] || data->map[i - 1][j] == ' ')
        return (0);
    // Vérifier la ligne en-dessous
    if (!data->map[i + 1] || !data->map[i + 1][j] || data->map[i + 1][j] == ' ')
        return (0);
    // Vérifier le caractère à gauche
    if (j == 0 || data->map[i][j - 1] == ' ')
        return (0);
    // Vérifier le caractère à droite
    if (!data->map[i][j + 1] || data->map[i][j + 1] == ' ')
        return (0);
    
    return (1);
}

int wall_map(t_data *data)
{
    size_t i;
    size_t j;
    size_t max_len;

    // Trouver la longueur maximale des lignes
    max_len = 0;
    i = 0;
    while (data->map[i])
    {
        size_t len = ft_strlen(data->map[i]);
        if (len > max_len)
            max_len = len;
        i++;
    }

    // Vérifier chaque position de la carte
    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (!check_adjacent_spaces(data, i, j))
                return (0);
            j++;
        }
        // Vérifier que les espaces à la fin de lignes plus courtes sont valides
        while (j < max_len)
        {
            if (i > 0 && data->map[i - 1][j] && data->map[i - 1][j] != ' ' && data->map[i - 1][j] != '1')
                return (0);
            if (data->map[i + 1] && data->map[i + 1][j] && data->map[i + 1][j] != ' ' && data->map[i + 1][j] != '1')
                return (0);
            j++;
        }
        i++;
    }
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
				if (!data->player_direction && data->player_x == -1 && data->player_y == -1)
				{
					data->player_direction = data->map[i][a];
					data->player_y = i;
					data->player_x = a;
				}
				else
					return (printf("Error: duplicate player position\n"), 0);
			}
			a++;
		}
		i++;
	}
	if (!data->player_direction)
		return (printf("Error: problem retrieving player position\n"), 0);
	return (1);
}

int	valid_map(t_data *data)
{
	int	i;
	int	a;

	i = 0;
	while (data->map[i])
	{
		a = 0;
		while (data->map[i][a])
		{
			if (!ft_strchr(" 01NSWE", data->map[i][a]))
			{
                return (printf("Error: invalid character in map => %c\n", data->map[i][a]), 0);
			}
			a++;
		}
		i++;
	}
	return (1);
}

t_data	parsing(char **args)
{
	t_data	result;

	init_data(&result);
	if (!args[1])
		return (printf("Error: No file provided\n"), exit(1), result);
	if (!ends_with_cub(args[1]))
		return (printf("Error: The file must have the .cub extension\n"), exit(1), result);
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

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        printf("Usage: %s <path_to_cub_file>\n", argv[0]);
        return (1);
    }

    data = parsing(argv);

    printf("North Texture: %s\n", data.no_texture);
    printf("South Texture: %s\n", data.so_texture);
    printf("West Texture: %s\n", data.we_texture);
    printf("East Texture: %s\n", data.ea_texture);

    printf("Floor color: [%d, %d, %d]\n", data.floor[0], data.floor[1], data.floor[2]);
    printf("Ceiling color: [%d, %d, %d]\n", data.ceiling[0], data.ceiling[1], data.ceiling[2]);

	if (data.map)
    {
        printf("Map:\n");
        for (int i = 0; data.map[i]; i++)
        {
            printf("%s\n", data.map[i]);
        }
    }
	
    free_data(&data);

    return (0);
}
