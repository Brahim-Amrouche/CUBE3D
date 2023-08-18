/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:36:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/19 00:13:34 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    move_player(t_cub3d *cub3d)
{
    int x;
    int y;
    t_raycaster_data *raycaster;

    raycaster = &cub3d->raycaster;
    y = raycaster->player_x + cub3d->move_vertical * raycaster->direction_x * (MOVE_SPEED + HB_RADIUS)
        + 0.7 * cub3d->move_horizontal * raycaster->camera_x * (MOVE_SPEED + HB_RADIUS);
    x = raycaster->player_y;
    if (cub3d->mini_map[x][y] == '0')
        raycaster->player_x += cub3d->move_vertical * raycaster->direction_x * MOVE_SPEED
            + 0.7 * cub3d->move_horizontal * raycaster->camera_x * (MOVE_SPEED + HB_RADIUS);
    y = raycaster->player_x;
    x = raycaster->player_y + cub3d->move_vertical * raycaster->direction_y * (MOVE_SPEED + HB_RADIUS)
        + 0.7 * cub3d->move_horizontal * raycaster->camera_y * (MOVE_SPEED + HB_RADIUS);
    if (cub3d->mini_map[x][y] == '0')
        raycaster->player_y += cub3d->move_vertical * raycaster->direction_y * MOVE_SPEED
        + 0.7 * cub3d->move_horizontal * raycaster->camera_y * (MOVE_SPEED + HB_RADIUS);
}

void    rotate_player(t_cub3d *cub3d)
{
    t_raycaster_data    *raycaster;
    double	            old_directionX;
    double              old_cameraX;
    double			    rot_speed;

    raycaster = &cub3d->raycaster;
    rot_speed = cub3d->rotation_dir * degree_to_rad(ROT_SPEED);
    old_directionX = raycaster->direction_x;
    old_cameraX = raycaster->camera_x;
    raycaster->direction_x = old_directionX * cos(rot_speed) - raycaster->direction_y * sin(rot_speed);
    raycaster->direction_y = old_directionX * sin(rot_speed) + raycaster->direction_y * cos(rot_speed);
    raycaster->camera_x = old_cameraX * cos(rot_speed) - raycaster->camera_y * sin(rot_speed);
    raycaster->camera_y = old_cameraX * sin(rot_speed) + raycaster->camera_y * cos(rot_speed);
}

