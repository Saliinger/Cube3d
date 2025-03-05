#include "../../../include/exec.h"

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
 {
 	int	dx;
 	int	dy;
 	int	sx;
 	int	sy;
 	int	err;
 	int	e2;

 	if (x0 < 0 || x0 >= WIN_WIDTH || y0 < 0 || y0 >= WIN_HEIGHT || x1 < 0
 		|| x1 >= WIN_WIDTH || y1 < 0 || y1 >= WIN_HEIGHT)
 		return ;
 	dx = abs(x1 - x0);
 	dy = abs(y1 - y0);
 	sx = x0 < x1 ? 1 : -1;
 	sy = y0 < y1 ? 1 : -1;
 	err = dx - dy;
 	while (1)
 	{
 		mlx_put_pixel(game->window->fpv, x0, y0, color);
 		if (x0 == x1 && y0 == y1)
 			break ;
 		e2 = 2 * err;
 		if (e2 > -dy)
 		{
 			err -= dy;
 			x0 += sx;
 		}
 		if (e2 < dx)
 		{
 			err += dx;
 			y0 += sy;
 		}
 	}
 }


void map(t_game *game)
{

}