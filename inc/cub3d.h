/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:40:39 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/01 17:47:03 by mgodefro         ###   ########.fr       */
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

# define	ERR_UTIL "The map is missing. Muste be : ./cub3d /path/to/map.cub"
# define	ERR_FORMAT "Invalid file format. Must be a .cub file."
# define	ERR_OPEN "Opening file failed."
# define	ERR_TEX_MIS "Textures are missing."
# define	ERR_TEX_SYN "Textures are incorrectly writted.\n\
Must be : (NO, SO, WE or EA) path/to/texture.xpm"
# define	ERR_COL_MIS "Colors are missing."
# define 	ERR_COL_SYN "Colors are incorrectly writted.\n\
Must be : (C or F) 0-255, 0-255, 0-255."
# define	ERR_COL_VAL "Invalid RGB value. Must be between 0 and 255."
# define	ERR_MAP_TOO_SMALL "Map is not at least 3 lines high."
# define	ERR_MAP_NO_WALLS "Map is not surrounded by walls."
# define	ERR_MAP_LAST "Map is not the last element in file."
# define	ERR_MAP_INV "Map description is either wrong or incomplete."

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
void	error(char *msg);
int		parsing(int ac, char **av);

#endif
