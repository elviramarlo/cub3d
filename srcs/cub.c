/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 21:34:07 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 13:01:07 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	hooks(t_cub *cub)
{
	mlx_hook(cub->window, DESTROY_NOTIFY, 0L, destroy, cub);
	mlx_hook(cub->window, KEY_PRESS, 1L << 0, key_press, cub);
	mlx_hook(cub->window, KEY_RELEASE, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->mlx, raycasting, cub);
	mlx_loop(cub->mlx);
}

static void	textures(t_cub *cub)
{
	char	**text[4];
	int		i;

	cub->img.img = mlx_new_image(cub->mlx, cub->eje_x, cub->eje_y);
	text[0] = &cub->text_north;
	text[1] = &cub->text_south;
	text[2] = &cub->text_west;
	text[3] = &cub->text_east;
	i = 0;
	while (i < 4)
	{
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, *text[i],
				&cub->width[i], &cub->height[i]);
		if (!cub->textures[i].img)
			print_error("Error with textures");
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img,
				&cub->textures[i].bits_per_pixel, &cub->textures[i].line_length,
				&cub->textures[i].endian);
		i++;
	}
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
}

static void	orientation2(t_cub *cub)
{
	if (cub->map.player_o == 'E')
	{
		cub->raycast.dir_x = 0;
		cub->raycast.dir_y = 1;
		cub->raycast.plane_x = 0.66;
		cub->raycast.plane_y = 0;
	}
	if (cub->map.player_o == 'W')
	{
		cub->raycast.dir_x = 0;
		cub->raycast.dir_y = -1;
		cub->raycast.plane_x = -0.66;
		cub->raycast.plane_y = 0;
	}
}

static void	orientation(t_cub *cub)
{
	if (cub->map.player_o == 'N')
	{
		cub->raycast.dir_x = -1;
		cub->raycast.dir_y = 0;
		cub->raycast.plane_x = 0;
		cub->raycast.plane_y = 0.66;
	}
	if (cub->map.player_o == 'S')
	{
		cub->raycast.dir_x = 1;
		cub->raycast.dir_y = 0;
		cub->raycast.plane_x = 0;
		cub->raycast.plane_y = -0.66;
	}
	orientation2(cub);
}

void	start_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		print_error("Something went wrong with the MLX");
	cub->window = mlx_new_window(cub->mlx, cub->eje_x, cub->eje_y, "CUB3D");
	if (!cub->window)
		print_error("Error opening the window");
	cub->raycast.pos_x = cub->map.player_pos_x - 0.5;
	cub->raycast.pos_y = cub->map.player_pos_y - 0.5;
	cub->raycast.move_speed = 0.1;
	cub->raycast.rot_speed = 0.1;
	orientation(cub);
	textures(cub);
	hooks(cub);
}
