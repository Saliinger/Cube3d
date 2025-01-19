#include "../../include/cube3d.h"

int map_height(char **map)
{
	int i = 0;
	while (map[i])
		i++;
	return (i);
}

int map_width(char **map)
{
	int i = 0;
	int j;
	int max_w = 0;
	int vide;
	while (map[i])
	{
		vide = 0;
		j = 0;
		while (map[i][j]
		       && map[i][j] != '0' && map[i][j] != '1'
		       && map[i][j] != 'E' && map[i][j] != 'W'
		       && map[i][j] != 'S' && map[i][j] != 'N')
			vide++;
		while (map[i][j + vide])
			j++;
		if (j > max_w)
			max_w = j;
		i++;
	}
	return (max_w);
}
