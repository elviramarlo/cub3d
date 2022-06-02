/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:48:50 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:09:38 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 ** Jump to next map square, OR in x-direction, OR in y-direction;
 ** and check if ray has hit a wall
 **/

static void	calculate_hit(t_cub *cub)
{
	cub->raycast.hit = 0;
	while (cub->raycast.hit == 0)
	{
		if (cub->raycast.sidedist_x < cub->raycast.sidedist_y)
		{
			cub->raycast.sidedist_x += cub->raycast.delta_dist_x;
			cub->raycast.map_x += cub->raycast.step_x;
			cub->raycast.side = 0;
		}
		else
		{
			cub->raycast.sidedist_y += cub->raycast.delta_dist_y;
			cub->raycast.map_y += cub->raycast.step_y;
			cub->raycast.side = 1;
		}
		if (cub->map.matrix[cub->raycast.map_x][cub->raycast.map_y] == '1')
			cub->raycast.hit = 1;
	}
}

/**
 ** Calculate distance projected on camera direction
 ** Calculate height of line to draw on screen
 ** calculate lowest and highest pixel to fill in current stripe
 **/

static void	calculate_distance(t_cub *cub)
{
	if (cub->raycast.side == 0)
		cub->raycast.perp_wall_dist = (cub->raycast.map_x - cub->raycast.pos_x
				+ (1 - cub->raycast.step_x) / 2) / cub->raycast.raydir_x;
	else
		cub->raycast.perp_wall_dist = (cub->raycast.map_y - cub->raycast.pos_y
				+ (1 - cub->raycast.step_y) / 2) / cub->raycast.raydir_y;
	cub->raycast.line_height = (int)(cub->eje_y / cub->raycast.perp_wall_dist);
	cub->raycast.drawstart = -cub->raycast.line_height / 2 + cub->eje_y / 2;
	if (cub->raycast.drawstart < 0)
		cub->raycast.drawstart = 0;
	cub->raycast.drawend = cub->raycast.line_height / 2 + cub->eje_y / 2;
	if (cub->raycast.drawend >= cub->eje_y)
		cub->raycast.drawend = cub->eje_y - 1;
}

static void	calculate_steps(t_cub *cub)
{
	if (cub->raycast.raydir_x < 0)
	{
		cub->raycast.step_x = -1;
		cub->raycast.sidedist_x = (cub->raycast.pos_x - cub->raycast.map_x)
			* cub->raycast.delta_dist_x;
	}
	else
	{
		cub->raycast.step_x = 1;
		cub->raycast.sidedist_x = (cub->raycast.map_x + 1.0
				- cub->raycast.pos_x) * cub->raycast.delta_dist_x;
	}
	if (cub->raycast.raydir_y < 0)
	{
		cub->raycast.step_y = -1;
		cub->raycast.sidedist_y = (cub->raycast.pos_y - cub->raycast.map_y)
			* cub->raycast.delta_dist_y;
	}
	else
	{
		cub->raycast.step_y = 1;
		cub->raycast.sidedist_y = (cub->raycast.map_y + 1.0
				- cub->raycast.pos_y) * cub->raycast.delta_dist_y;
	}
}

/**
** calculate ray position and direction
** length of ray from one x or y side to next x or y side
**/

static void	calculate_ray(t_cub *cub, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)(cub->eje_x) - 1;
	cub->raycast.raydir_x = cub->raycast.dir_x + cub->raycast.plane_x * cameraX;
	cub->raycast.raydir_y = cub->raycast.dir_y + cub->raycast.plane_y * cameraX;
	cub->raycast.map_x = (int)(cub->raycast.pos_x);
	cub->raycast.map_y = (int)(cub->raycast.pos_y);
	cub->raycast.delta_dist_x = fabs(1 / cub->raycast.raydir_x);
	cub->raycast.delta_dist_y = fabs(1 / cub->raycast.raydir_y);
}

int	raycasting(t_cub *cub)
{
	int		x;

	x = 0;
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, cub->window);
	while (x < cub->eje_x)
	{
		calculate_ray(cub, x);
		calculate_steps(cub);
		calculate_hit(cub);
		calculate_distance(cub);
		texturing_calculation(cub);
		draw_pixels(cub, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img.img, 0, 0);
	keys(cub);
	return (0);
}
