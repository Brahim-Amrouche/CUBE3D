/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:46:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 13:39:13 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
#define CUB3D_PARSING_H
#include "cub3d.h"

#define WINDOW_HEIGHT   1080
#define WINDOW_WIDTH    1920
// int_parser.c
t_boolean	ft_str_is_integer(const char *str, int *res);

// floor_parser.c
void        floor_parser(char *line, t_cub3d *cub3d);

// textures_parser.c
void		parse_textures(t_cub3d *cub3d);

// map_parser.c
t_boolean   is_start_pos(char c);
void        map_parser(t_cub3d *cub3d);

// main_parser.c
void    cub3d_parser(int argc, char *argv[], t_cub3d *cub3d);

#endif