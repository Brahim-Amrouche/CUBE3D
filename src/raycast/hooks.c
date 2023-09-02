/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:59:39 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/17 17:11:32:48oulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int    close_window(void)
{
	t_cub3d *cub3d;

	cub3d = get_cub3d(NULL);
	while (*(cub3d->imgs))
	{
		mlx_destroy_image(cub3d->mlx, *(cub3d->imgs));
		cub3d->imgs++;
	}
	mlx_destroy_window(cub3d->mlx, cub3d->window);
	ft_free(0, TRUE);
	exit(0);
	return (0);
}

void	print_map(t_cub3d *cub3d)
{
	// int x;
	// int y;

	printf("player at x = %lf, y = %lf\n", cub3d->raycaster.player_x, cub3d->raycaster.player_y);
	// printf("direction at  at x = %lf, y = %lf\n", cub3d->raycaster.direction_x, cub3d->raycaster.direction_y);
	// printf("FOV at x = %lf , y = %lf\n", cub3d->raycaster.camera_x, cub3d->raycaster.camera_y);
	// y = 0;
	// while(cub3d->mini_map[y])
	// {
	// 	x = 0;
	// 	while (cub3d->mini_map[y][x])
	// 	{
	// 		printf("%c, ", cub3d->mini_map[y][x]);
	// 		x++;
	// 	}
	// 	printf("\n");
	// 	y++;
	// }
}

void	open_door(t_cub3d *cub3d)
{
    t_raycaster_data	*raycaster;
	t_door 				**temp;
	t_door				*door;
	t_door				**open_doors;
	int					x;
	int					y;

	raycaster = &cub3d->raycaster;
	x = raycaster->player_x + 0.5 * raycaster->direction_x;
	y = raycaster->player_y + 0.5 * raycaster->direction_y;
	if (cub3d->mini_map[y][x] != 'D')
		return ;
	open_doors = cub3d->door;
	while (open_doors && *open_doors)
	{
		if ((*open_doors)->x == x && (*open_doors)->y == y)
			return ;
		open_doors++;
	}
	door = ft_malloc(sizeof(t_door), m_info(NULL, 1, NULL, 0));
	if (!door)
		exit_cub3d(ENOMEM, "couldn't malloc for door");
	door->x = x;
	door->y = y;
	door->open = 0.0;
	door->opening = TRUE;
	temp = cub3d->door;
	cub3d->door = add_element_to_array(temp, &door, sizeof(t_door *));
	ft_free_node(1, temp);
}

static int	keyboard_press_hooks(int keycode,t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == W_KEY)
		cub3d->move_vertical = 1;
	else if (keycode == S_KEY)
		cub3d->move_vertical = -1;
	else if (keycode == D_KEY)
		cub3d->move_horizontal = 1;
	else if (keycode == A_KEY)
		cub3d->move_horizontal = -1;
	else if (keycode == LEFT_KEY)
		cub3d->rotation_dir = -1;
	else if (keycode == RIGHT_KEY)
		cub3d->rotation_dir = 1;
	else if (keycode == C_KEY) //clean this
		open_door(cub3d);
	else if (keycode == SLASH_KEY) //clean this
		print_map(cub3d);
	
	return (0);
}

static int	keyboard_release_hooks(int keycode,t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == S_KEY || keycode == W_KEY)
		cub3d->move_vertical = 0;
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		cub3d->rotation_dir = 0;
	else if (keycode == A_KEY || keycode == D_KEY)
		cub3d->move_horizontal = 0;
	return (0);
}

static t_boolean	check_map(int x, int y, t_cub3d *cub3d)
{
	float	xm;
	float	ym;
	int ratio;

	ratio = cub3d->minimap.unit;
	xm = (float) (x - (cub3d->minimap.width) / 2) / ratio  + cub3d->raycaster.player_x;
	ym = (float) (y - (cub3d->minimap.height) / 2) / ratio + cub3d->raycaster.player_y;
	if (ym >= 0 && ym < (int) cub3d->raycaster.rows_count
		&& xm >= 0 && xm < (int) cub3d->mini_map_line_len[(int) ym]
		&& cub3d->mini_map[(int) ym][(int) xm] == '0'
		)
		return (TRUE);
	else
		return (FALSE);
}
	// xm = (x - cub3d->minimap.width / 2) / cub3d->minimap.unit  + cub3d->raycaster.player_x;
	// ym = (y - cub3d->minimap.height / 2) / cub3d->minimap.unit + cub3d->raycaster.player_y;
	// if (ym >= 0 && ym < (int) cub3d->raycaster.rows_count
	// 	&& xm >= 0 && xm < (int) cub3d->mini_map_line_len[ym]
	// 	&& cub3d->mini_map[ym][xm] == '0'
	// 	)

void	draw_minimap(t_cub3d *cub3d)
{
	int	x;
	int	y;

	cub3d->minimap.size = 10;
	cub3d->minimap.unit = 10;
	cub3d->minimap.height = WINDOW_HEIGHT / cub3d->minimap.size;
	cub3d->minimap.width = WINDOW_WIDTH / cub3d->minimap.size;
	y =  0;
	while (y < cub3d->minimap.height)
	{
		x =  0;
		while (x < cub3d->minimap.width)
		{
			if (y > (cub3d->minimap.height - cub3d->minimap.unit) / 2 && y < (cub3d->minimap.height + cub3d->minimap.unit) / 2
				&& x > (cub3d->minimap.width - cub3d->minimap.unit) / 2 && x < (cub3d->minimap.width + cub3d->minimap.unit) / 2)
				cub3d_pixel_put(cub3d, x, y, 0xff0000);
			else if (check_map(x, y, cub3d))
				cub3d_pixel_put(cub3d, x, y, 0xffffff);
			else if (x < 2 || x > cub3d->minimap.width - 3
					|| y < 2 || y > cub3d->minimap.height - 3)
				cub3d_pixel_put(cub3d, x, y, 0xaaaaaa);
			else
				cub3d_pixel_put(cub3d, x, y, 0x000000);
			x++;
		}
		y++;
	}
	t_projected_point start;
	t_projected_point end;
	t_raycaster_data *raycaster;

	int length = 500;
    raycaster = &cub3d->raycaster;
	start.x = cub3d->minimap.width / 2;
	start.y = cub3d->minimap.height / 2;
	end.x = start.x + length * (raycaster->direction_x * 100
        + raycaster->camera_x * 102);
    end.y = start.y + length * (raycaster->direction_y * 100
        + raycaster->camera_y * 102);
	cub3d_draw_line(cub3d, start, end);
	end.x = start.x + length * (raycaster->direction_x * 100
        - raycaster->camera_x * 102);
    end.y = start.y + length * (raycaster->direction_y * 100
        - raycaster->camera_y * 102);
	cub3d_draw_line(cub3d, start, end);
}

void	animate_doors(t_cub3d *cub3d, t_door **doors)
{
	int i;
	float	step;
	float	door_radius;
	t_door **temp;

	if (!doors)
		return ;
	i = 0;
	step = 0.03;
	door_radius = 0.3;
	while (doors[i])
	{
		if (doors[i]->open < -0.01)
		{
			temp = cub3d->door;
			cub3d->door = rm_element_from_array(temp, doors + i, sizeof(t_door *));
			ft_free_node(1, doors[i]);
			ft_free_node(1, temp);
			doors = cub3d->door;
			continue ;
		}
		else if (doors[i]->open > 2)
			doors[i]->opening = FALSE;
		// printf("door y is %d, player , %d\n", doors[i]->y, (int) cub3d->raycaster.player_y);
		if (cub3d->raycaster.player_y + door_radius > (double) doors[i]->y && cub3d->raycaster.player_y - door_radius < (double) doors[i]->y + 1
			&& cub3d->raycaster.player_x + door_radius > (double) doors[i]->x && cub3d->raycaster.player_x - door_radius < (double) doors[i]->x + 1)
		{
			i++;
			continue ;
		}
		if (doors[i]->opening)
			doors[i]->open += step;
		else
			doors[i]->open -= step;
		
		// doors[i]->open += (step * (-1 + 2 * doors[i]->opening));
		i++;
	}
}

int	refresh(t_cub3d *cub3d)
{
	static int fps;
	
	if (fps > 500)
	{
		// if (cub3d->door_open < 0 || cub3d->door_open > 2)
		// 	cub3d->door_step *= -1;
		// cub3d->door_open += cub3d->door_step;
		animate_doors(cub3d, cub3d->door);
		if (cub3d->move_vertical || cub3d->move_horizontal)
			move_player(cub3d);
		if (cub3d->rotation_dir)
			rotate_player(cub3d);
		draw_cub3d(cub3d);
		draw_minimap(cub3d);
		fps = 0;
		cub3d->texturen++;
		if (cub3d->texturen > 4)
			cub3d->texturen = 0;
	}
	fps++;
	return (0);
}

// int	mouse_rotation(int x, int y, t_cub3d *cub3d)
// {
// 	if (x - cub3d->mouse_x > 0)
// 	{
		
// 		cub3d->rotation_dir = 1;
// 	}
// 	return (0);
// }	

void	cub3d_hooks(t_cub3d *cub3d)
{
	cub3d->mouse_x = WINDOW_HEIGHT / 2;
	cub3d->mouse_y = WINDOW_WIDTH / 2;
	// mlx_hook(cub3d->window, MOTIONNOTIFY, POINTERMOTIONMASK, rotate_hook,
	// 	fdf);
	mlx_hook(cub3d->window, DESTROYNOTIFY, NOEVENTMASK, close_window,(void *) NULL);
	mlx_hook(cub3d->window, KEYPRESS, KEYPRESSMASK, keyboard_press_hooks, cub3d);
	mlx_hook(cub3d->window, KEYRELEASE, KEYRELEASEMASK, keyboard_release_hooks, cub3d);
	mlx_loop_hook(cub3d->mlx, refresh, cub3d);
}
