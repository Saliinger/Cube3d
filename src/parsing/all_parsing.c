/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:32:16 by jalbiser          #+#    #+#             */
/*   Updated: 2025/01/30 19:29:56 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

//int main(int argc, char **argv)
//{
//  t_data data;
//
//  if (argc != 2)
//  {
//      printf("Usage: %s <path_to_cub_file>\n", argv[0]);
//      return (1);
//  }
//
//  data = parsing(argv);
//
//  printf("North Texture: %s\n", data.no_texture);
//  printf("South Texture: %s\n", data.so_texture);
//  printf("West Texture: %s\n", data.we_texture);
//  printf("East Texture: %s\n", data.ea_texture);
//
//  printf("Floor color: [%d, %d, %d]\n", data.floor[0], data.floor[1], data.floor[2]);
//  printf("Ceiling color: [%d, %d, %d]\n", data.ceiling[0], data.ceiling[1], data.ceiling[2]);
//
//	if (data.map)
//  {
//      printf("Map:\n");
//      for (int i = 0; data.map[i]; i++)
//      {
//          printf("%s\n", data.map[i]);
//      }
//  }
//
//  free_data(&data);
//
//  return (0);
//}