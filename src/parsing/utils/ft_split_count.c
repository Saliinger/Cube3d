/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 16:18:30 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-23 16:18:30 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

int	ft_split_count(char **split)
{
	int	count;

	if (!split)
		return (0);
	count = 0;
	while (split[count])
		count++;
	return (count);
}
