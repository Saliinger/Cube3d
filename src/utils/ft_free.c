#include "../../include/cube3d.h"

static void	free_texture(t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->nord)
		mlx_delete_texture(texture->nord);
	if (texture->sud)
		mlx_delete_texture(texture->sud);
	if (texture->est)
		mlx_delete_texture(texture->est);
	if (texture->ouest)
		mlx_delete_texture(texture->ouest);
	free(texture);
}

static void	free_rayon(t_rayon *rayon)
{
	if (!rayon)
		return ;
	free(rayon);
}

static void	free_window(t_window *window)
{
	if (!window)
		return ;
	if (window->fpv)
		mlx_delete_image(window->mlx, window->fpv);
	// if (window->map_2d)
	// 	mlx_delete_image(window->mlx, window->map_2d);
	mlx_terminate(window->mlx);
	free(window);
}

static void	free_player(t_player *player)
{
	if (!player)
		return ;
	free(player);
}

void	ft_free(t_game *game)
{
	free_texture(game->texture);
	free_rayon(game->rayon);
	free_window(game->window);
	free_player(game->player);
	free_data(game->data);
}