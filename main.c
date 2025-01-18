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
	if (parsing(av, &data))
		return (1);
	if (exec(&data))
		return (1);
	return(0);
}
