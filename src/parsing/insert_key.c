/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:33:20 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/30 19:16:28 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	insert_key(char *value, char **target_char, int **target_int)
{
	if (!value)
		return (0);
	trim(value);
	if (target_char)
	{
		if (*target_char)
			free(*target_char);
		*target_char = ft_strdup(value);
		if (!*target_char)
			return (0);
	}
	else if (target_int)
	{
		if (!parsed_color(target_int, value))
			return (0);
	}
	return (1);
}
