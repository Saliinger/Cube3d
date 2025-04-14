/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:07:51 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/14 19:34:27 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cube3d.h"

int	main(int ac, char **av)
{
	t_data	data;

if (ac != 2)
{	printf("nique ta grang mere la pute"); return (0);}
	data = parsing(av);
	if (exec(&data))
		return (1);
	return (0);
}
