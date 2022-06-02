/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:20:08 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 13:54:41 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>

# define K_ESC		53
# define K_W		13
# define K_A		0
# define K_S		1
# define K_D		2
# define K_LEFT		123
# define K_RIGHT	124
// X11 Events
# define KEY_PRESS				02
# define KEY_RELEASE			03
# define DESTROY_NOTIFY			17
// MLX SYNC
# define MLX_SYNC_IMAGE_WRITABLE    1
# define MLX_SYNC_WIN_FLUSH_CMD     2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

/*
** X11 EVENTS MASKS:
** # define NO_EVENT_MASK				0L
** # define KEY_PRESS_MASK				(1L<<0)
** # define KEY_RELEASE_MAS				(1L<<1)
*/
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	t_list	*list;
	int		lines;
	int		max_len_line;
	char	player_o;
	int		player_pos_x;
	int		player_pos_y;
	char	**matrix;
	int		matrix_act_line;
}				t_map;

typedef struct s_check
{
	int	north;
	int	south;
	int	east;
	int	west;
	int	floor;
	int	ceiling;
	int	num_elems;
	int	map_start;
	int	map_is_end;
	int	matrix_zero;
}				t_check;

typedef struct s_fd
{
	int	fd;
	int	t_north;
	int	t_west;
	int	t_south;
	int	t_east;
}				t_fd;

typedef struct s_key
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_left;
	int	key_right;
}				t_key;

typedef struct s_raycast
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		drawstart;
	int		drawend;
	int		tex_num;
	int		tex_y;
	int		tex_x;
	double	tex_pos;
	double	step;
	double	raydir_y;
	double	raydir_x;
	double	sidedist_x;
	double	sidedist_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		line_height;
}				t_raycast;

typedef struct s_cub
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_check		check;
	t_fd		fd;
	t_key		key;
	t_raycast	raycast;
	t_data		img; // Textura principal
	t_data		textures[4]; // Texturas de pared
	int			width[4];
	int			height[4];
	//INFO GUARDADA DE LOS ELEMENTOS
	int			eje_x;
	int			eje_y;
	char		*text_north;
	char		*text_south;
	char		*text_west;
	char		*text_east;
	int			color_f_r;
	int			color_f_g;
	int			color_f_b;
	int			color_f_trgb;
	int			color_c_r;
	int			color_c_g;
	int			color_c_b;
	int			color_c_trgb;
	char		*cfr;
	char		*cfg;
	char		*cfb;
	char		*ccr;
	char		*ccg;
	char		*ccb;
}				t_cub;

void	parse_elements(t_cub *cub, char *line);
void	parse_north(t_cub *cub, char *line);
void	parse_south(t_cub *cub, char *line);
void	parse_west(t_cub *cub, char *line);
void	parse_east(t_cub *cub, char *line);
void	parse_ceiling(t_cub *cub, char *line);
void	parse_floor(t_cub *cub, char *line);
void	parse_resolution(t_cub *cub, char *line);
void	parse_map(t_cub *cub, char *line);
void	iter_cub_list(t_cub *cub, t_list *lst, void (*f)(t_cub *, void *));
void	map_matrix1(t_cub *cub, void *content);
void	check_matrix(t_cub *cub);
void	make_resolution(t_cub *cub);
void	start_cub(t_cub *cub);
int		destroy(t_cub *cub);
int		key_press(int tecla, t_cub *cub);
int		key_release(int tecla, t_cub *cub);
int		raycasting(t_cub *cub);
void	keys(t_cub *cub);
void	draw_pixels(t_cub *cub, int x);
void	texturing_calculation(t_cub *cub);
void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);
int		my_pixel_get(t_data *data, int x, int y);
void	print_error(char *str);
void	close_fds(t_cub *cub);
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

# define RESET				"\x1b[0m"
# define WHITE				"\x1b[1m"
# define W_B_WHITE			"\x1b[47m"
# define W_B_CYAN			"\x1b[46m"
# define W_B_PURPLE			"\x1b[45m"
# define W_B_BLUE			"\x1b[44m"
# define W_B_YELLOW			"\x1b[43m"
# define W_B_GREEN			"\x1b[42m"
# define W_B_RED			"\x1b[41m"
# define WH_B_CLEAR			"\x1b[40m"
# define INVISIBLE			"\x1b[8m"
# define WHITE_BOX			"\x1b[7m"
# define WHITE_SUB			"\x1b[4m"
# define WHITE_CURS			"\x1b[3m"
# define GRAY				"\x1b[2m"
# define BLACK				"\x1b[30m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define PURPLE				"\x1b[35m"
# define CYAN				"\x1b[36m"

#endif