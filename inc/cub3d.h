/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:40:39 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/01 18:28:30 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* Librairies */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <X11/keysym.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define	ERR_UTIL			"The map is missing. Must be : ./cub3d /path/to/map.cub"
# define	ERR_FORMAT			"Invalid file format. Must be a .cub file."
# define	ERR_MISSING_PLAYER	"Player is missing on the map."
# define	ERR_MALLOC			"Malloc failed."
# define	ERR_INVALID_MAP		"Invalid map."
# define	ERR_OUT_OF_BOUNDS	"Checked position out of the map."
# define	ERR_MISSING_LINE	"Missing line"
# define	ERR_OUT_OF_LINE		"Position out of the line."
# define	ERR_SPACE_MISPLACED	"Mispaced space."
# define	ERR_INVALID_CHAR	"Invalid char on the map."
# define	ERR_FLOOD_FAIL		"Flood fill error."
# define	ERR_MAP_NOT_CLOSED	"Map not closed."

/* Structures */
typedef struct s_pos
{
	double	x;
	double	y;
	double	yaw;        // Player orientation (o to 360)
}	t_pos;				// Coordinates and orientation

typedef struct s_img
{
	void	*img;        // Pointer to image object (MLX)
	char	*addr;       // Address of image data
	int		bpp;         // Bits per pixel
	int		line_len;    // Length of a line in bytes
	int		endian;      // (jai oublie mais c necessaire pr les textures)
	int		width;       // Image width in pixels
	int		height;      // Image height in pixels
}	t_img;

typedef struct s_player
{
	t_pos	pos;          // Player position
	double	move_speed;   // Movement speed
	double	rot_speed;    // Rotation speed
}	t_player;

typedef struct s_ray
{
	double	camera_x;        // Camera X coordinate (for raycasting)
	t_pos	ray_dir;         // Ray direction vector
	t_pos	map;             // Current map square
	t_pos	side_dist;       // Distance to next side
	t_pos	delta_dist;      // Distance between sides
	double	perp_wall_dist;  // Perpendicular wall distance
	t_pos	step;            // Step direction (x/y)
	int		hit;             // Wall hit flag
	int		side;            // Side of wall hit (NS/EW)
}	t_ray;

typedef struct s_tex
{
	char	*path;        // Texture file path
	t_img	img;          // Texture image data
}	t_tex;

typedef struct s_map
{
	char	**grid;     // 2D map grid in chars
	int		width;      // Map width
	int		height;     // Map height
}	t_map;

typedef struct s_color
{
	int	r;            // Red
	int	g;            // Green
	int	b;            // Blue
	int	value;        // Combined RGB color value
}	t_color;

typedef struct s_game
{
	void		*mlx;         // MLX instance pointer
	void		*win;         // MLX window pointer
	t_img		img;          // Main image buffer
	t_player	player;       // Player data
	t_map		map;          // Map data
	t_tex		tex[4];       // Textures: 0=N, 1=S, 2=W, 3=E
	t_color		floor;        // Floor color
	t_color		ceiling;      // Ceiling color
	int			screen_w;     // Screen width
	int			screen_h;     // Screen height
	int			**z_buffer;   // Z-buffer for depth
}	t_game;

/* Functions */
int		check_file_format(char *filename);
int		parsing(int ac, char **av);

// utils.c
int		error(char *msg);
char	**ft_arrdup(char **arr);

#endif
