/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:49:00 by anoukan           #+#    #+#             */
/*   Updated: 2025/02/21 14:49:01 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../../include/cube3d.h"

 static uint32_t	rgb_to_hex(int red, int green, int blue)
 {
 	uint32_t	hex;

 	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
 		|| blue > 255)
 	{
 		fprintf(stderr,
 			"Erreur: Les valeurs RGB doivent être entre 0 et 255\n");
 		return (0);
 	}
 	hex = ((uint32_t)red << 24) | ((uint32_t)green
<< 16) | ((uint32_t)blue << 8) | 0xFF;
 	return (hex);
 }

 mlx_image_t	*cube(t_game *game, uint32_t color)
 {
 	mlx_image_t	*image;
 	int			i;
 	int			j;

 	i = 0;
 	printf("Creating a cube with color: 0x%X\n", color);
 	// RGB color in hexadecimal
 	image = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
 	if (!image)
 		ft_error("Error: Could not create cube image\n");
 	// Fill the image with the given color
 	while (i < TILE_SIZE)
 	{
 		j = 0;
 		while (j < TILE_SIZE)
 		{
 			mlx_put_pixel(image, i, j, color);
 			j++;
 		}
 		i++;
 	}
 	printf("Cube creation complete.\n");
 	return (image);
 }

 void	init_map(t_game *game)
 {
 	int			border;
 	mlx_image_t	*white_img;
 	mlx_image_t	*black_img;
 	char		**map;
 	int			i;
 	int			j;

 	printf("Initializing the map visuals...\n");
 	white_img = cube(game, rgb_to_hex(255, 255, 255));
 	black_img = cube(game, rgb_to_hex(0, 0, 0));
 	border = 2;
 	i = 0;
 	map = game->data->map;
 	printf("Map layout:\n");
 	while (map[i])
 	{
 		printf("%s\n", map[i]);
 		i++;
 	}
 	i = 0;
 	while (map[i])
 	{
 		j = 0;
 		while (map[i][j] && map[i][j] != '\n')
 		{
 			if (map[i][j] != ' ')
 				mlx_image_to_window(game->mlx, black_img, j * TILE_SIZE, i
 					* TILE_SIZE);
 			if (map[i][j] == '1')
 				mlx_image_to_window(game->mlx, black_img, j * TILE_SIZE
 					+ border, i * TILE_SIZE + border);
 			else if (map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'E'
 				|| map[i][j] == 'S' || map[i][j] == 'N')
 				mlx_image_to_window(game->mlx, white_img, j * TILE_SIZE
 					+ border, i * TILE_SIZE + border);
 			j++;
 		}
 		i++;
 	}
 	printf("Map visuals initialization complete.\n");
 }

 void	draw_square(mlx_image_t *img, uint32_t color)
 {
 	int	i;
 	int	j;

 	for (i = 0; i < TILE_SIZE; i++)
 	{
 		for (j = 0; j < TILE_SIZE; j++)
 		{
 			mlx_put_pixel(img, j, i, color);
 		}
 	}
 }

 void	debug_player(t_game *game)
 {
 	mlx_image_t	*image;

 	printf("Initializing player debug image...\n");
 	image = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
 	if (!image)
 		ft_error("Error: Could not initialize player image\n");
 	if (!game->data)
 	{
 		printf("Error: Game data is NULL\n");
 		return ;
 	}
 	printf("Player position: (%d, %d)\n", game->data->player_x,
 		game->data->player_y);
 	draw_square(image, rgb_to_hex(255, 0, 0));
 	mlx_image_to_window(game->mlx, image, game->player->x, game->player->y);
 	printf("Player debug image initialized successfully.\n");
 }
