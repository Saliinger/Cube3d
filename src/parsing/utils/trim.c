/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-23 16:35:49 by jalbiser          #+#    #+#             */
/*   Updated: 2025-01-23 16:35:49 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

void	trim(char *str)
{
	int length;
	int start;
	int end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && ft_isspace(str[start]))
		start++;
	while (end >= start && ft_isspace(str[end]))
		end--;
	length = end - start + 1;
	ft_memmove(str, str + start, length);
	str[length] = '\0';
}