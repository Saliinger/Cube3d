/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:07:51 by anoukan           #+#    #+#             */
/*   Updated: 2025/03/28 16:19:10 by anoukan          ###   ########.fr       */
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
