#include "../../include/cube3d.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

// add free game if an exit occur