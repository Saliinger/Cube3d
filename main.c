/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:07:51 by anoukan           #+#    #+#             */
/*   Updated: 2025/01/17 21:08:28 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cube3d.h"

int main(int ac, char **av)
{
	t_data data;

	(void)ac;
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
	if (!parsing(av, &data))
		return (1);
	if (exec(&data))
		return (1);
	return(0);
}
