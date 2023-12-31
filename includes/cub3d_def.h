/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:39:28 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/09 15:03:46 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEF_H
# define CUB3D_DEF_H
# include "cub3d.h"
# include "ft_garbage_collector.h"
# include "mlx.h"
# include <errno.h>
# include <math.h>
# include <X11/X.h>

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920

# define TX_NBR 16
# define TEX_DIMENSIONS 256
# define HB_RADIUS 0.3

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.02

# define DBL_MAX 1.0e30

typedef struct s_cub3d_projected_point
{
	double				x;
	double				y;
	int					clr;
}						t_projected_point;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct s_frame_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_frame_data;

typedef enum e_tx_type
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	DOOR,
	SPRITE,
	FIREHEAD1,
	FIREHEAD2,
	FIREHEAD3,
	FIREHEAD4,
	FIREHEAD5,
	NOT_DEFINED
}						t_tx_type;

typedef struct s_textures
{
	t_rgb				floor;
	t_boolean			floor_is_set;
	t_rgb				ceiling;
	t_boolean			ceiling_is_set;
	void				*tx_img[TX_NBR];
	int					tx[TX_NBR][TEX_DIMENSIONS * TEX_DIMENSIONS];
	int					tx_set[TX_NBR];
}						t_textures;

typedef struct s_player_move
{
	double				x;
	double				y;
}						t_player_move;

typedef struct s_raycaster_data
{
	size_t				rows_count;
	double				player_x;
	double				player_y;
	double				direction_x;
	double				direction_y;
	double				camera_x;
	double				camera_y;
	double				ray_x;
	double				ray_y;
	int					map_x;
	int					map_y;
	double				sidedist_x;
	double				sidedist_y;
	double				deltadist_x;
	double				deltadist_y;
	double				perpwalldist;
	int					step_x;
	int					step_y;
	t_boolean			hit;
	t_boolean			side;
	t_boolean			door;
	t_boolean			door_side;
	int					back_x;
	int					back_y;
	t_boolean			back_s;
	t_boolean			pass_door;
	double				angle;
	double				delta;
	int					draw_start;
	int					draw_end;
	double				wall_x;
	double				tex_step;
	double				tex_pos;
	int					tex_x;
	int					tex_y;
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					sprite_screenx;
	int					sprite_height;
	int					draw_startx;
	int					draw_starty;
	int					draw_endx;
	int					draw_endy;
	int					sprite_width;

}						t_raycaster_data;

typedef struct s_sprite
{
	double				x;
	double				y;
	size_t				sprite_id;
	double				distance;
}						t_sprite;

typedef struct s_minimap
{
	int					width;
	int					height;
	int					unit;
	int					size;
}						t_minimap;

typedef struct s_door
{
	int					x;
	int					y;
	float				open;
	t_boolean			opening;
}						t_door;

typedef struct s_cub3d
{
	char				**map_content;
	size_t				*content_len;
	size_t				map_len;
	size_t				*map_row_len;
	char				**mini_map;
	size_t				*mini_map_line_len;
	t_boolean			player_set;
	t_textures			texture;
	void				*mlx;
	void				*window;
	void				**imgs;
	int					img_width;
	int					img_height;
	t_frame_data		frame;
	t_player_move		p_move;
	t_raycaster_data	raycaster;
	int					move_horizontal;
	int					move_vertical;
	int					rotation_dir;
	int					mouse_rot_dir;
	t_sprite			**sprites;
	size_t				sprite_count;
	double				zbuffer[WINDOW_WIDTH];
	int					mouse_x;
	int					mouse_y;
	double				rot_multiplicator;
	int					texturen;
	t_minimap			minimap;
	t_door				**door;
}						t_cub3d;

#endif
