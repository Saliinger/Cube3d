/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:27:51 by jalbiser          #+#    #+#             */
/*   Updated: 2025/04/16 21:10:02 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	parsed_color(int **target, char *value)
{
	char	**values;
	int		val;
	int		i;

	i = 0;
	values = ft_split(value, ',');
	if (!values || ft_split_count(values) != 3)
		return (free_split(values), 0);
	*target = malloc(sizeof(int) * 3);
	if (!*target)
		return (free_split(values), 0);
	while (values[i])
	{
		trim(values[i]);
		if (!ft_str_is_numeric(values[i]))
			return (free_split(values), 0);
		val = ft_atoi(values[i]);
		if (val < 0 || val > 255)
			return (free_split(values), 0);
		(*target)[i] = val;
		i++;
	}
	free_split(values);
	return (1);
}
