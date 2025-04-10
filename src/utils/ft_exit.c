/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:05:57 by anoukan           #+#    #+#             */
/*   Updated: 2025/04/10 18:07:27 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	ft_exit(t_game *game, int status, char *str)
{
	ft_free(game);
	if (str)
		ft_printf("%s\n", str);
	exit(status);
}
