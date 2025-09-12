/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:40:39 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/12 08:50:37 by maximegdfr       ###   ########.fr       */
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
# include <ctype.h>
# include <X11/keysym.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define	ERR_UTIL			"Map is missing. Muste be : ./cub3d /path/to/map.cub"
# define	ERR_FORMAT			"Invalid file format. Must be a .cub file."
# define	ERR_OPEN			"Opening file failed."
# define	ERR_TEX_MIS			"Textures are missing."
# define	ERR_TEX_SYN			"Textures are incorrectly writted.\n\
Must be : (NO, SO, WE or EA) path/to/texture.xpm"
# define	ERR_COL_MIS			"Colors are missing."
# define 	ERR_COL_SYN			"Colors are incorrectly writted.\n\
Must be : (C or F) 0-255, 0-255, 0-255."
# define	ERR_COL_VAL			"Invalid RGB value. Must be between 0 and 255."
# define	ERR_MAP_TOO_SMALL	"Map is not at least 3 lines high."
# define	ERR_MAP_NO_WALLS	"Map is not surrounded by walls."
# define	ERR_MAP_LAST		"Map is not the last element in file."
# define	ERR_MAP_INV			"Map description is either wrong or incomplete."
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
# define	ERR_MAP_NOT_CLOSED	"Map not closed. (or invalid)"
# define	ERR_MAP_MIS			"Map is missing."

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
	char	*north;        // Texture file path
	char	*south;
	char	*east;
	char	*west;
	t_img	img;          // Texture image data
}	t_tex;

typedef struct s_map
{
	char	**grid;     // 2D map grid in chars
	int		width;      // Map width
	int		height;     // Map height
	int		first_line;
	int		last_line;
	int		has_player;
	int		player_x;
	int		player_y;
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
	t_color		ceilling;      // Ceiling color
	int			screen_w;     // Screen width
	int			screen_h;     // Screen height
	int			**z_buffer;   // Z-buffer for depth
}	t_game;

typedef enum e_state
{
	BEFORE_MAP,
	IN_MAP,
	AFTER_MAP
}	t_state;

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

/*   Functions   */
int		check_file_format(char *filename);
int		parsing(int ac, char **av);
int		parsing_map(t_game *game, char *filename);
int		parsing_texture(char *line);

// read_map.c
int		init_map(t_map *map);
int		parsing_data(t_game *game, char *filename);
int		get_file_info(t_game *game, int fd);
int		parsing_line(t_game *game, t_state *state, char *line);
int		get_texture_info(t_game *game, char *line);
int		fill_texture_info(t_game *game, char *line, int *i);
char	*get_path_texture(char *line, int *i);
int		fill_color_ceilling(t_game *game, char *line, int *i);
int		extract_value(char *line, int value, int *i, int digits_count);
int		fill_rgb(t_color *color_to_fill, int *index_rgb, int value);
int		fill_color_floor(t_game *game, char *line, int *i);
int		get_map_info(t_game *game, char *line);
int		line_is_empty(char *line);
int		is_valid_char(char c);
int		check_line_is_map(char *line);
int		select_parser(t_game *game, t_state *state, char *line);
int		is_map_line(t_game *game, char *line);


int		copy_map(t_game *game, char *line);
int		allocation_map(t_game *game, t_list *lines);
int		finalize_copy(t_game *game, t_list *lines);
int		get_max_width(t_list *lines);

/*  Map checking   */

// print_map.c
void	print_map(char **map);

// extend_map.c
char	**extend_map(char **map);

// floodfill.c
int		flood_fill_outside(char **map, t_pos pos);

// utils.c
int		error(char *msg);
char	**ft_arrdup(char **arr);
void	ft_free_split(char **array);

#endif
