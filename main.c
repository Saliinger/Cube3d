/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:07:51 by anoukan           #+#    #+#             */
/*   Updated: 2025/02/20 22:39:40 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cube3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	data = parsing(av);
	if (exec(&data))
		return (1);
	return (0);
}
