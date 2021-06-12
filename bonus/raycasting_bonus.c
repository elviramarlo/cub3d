/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:48:50 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:12:09 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

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
			cub->raycast.sidedist_x += cub->raycast.deltaDistX;
			cub->raycast.mapX += cub->raycast.stepX;
			cub->raycast.side = 0;
		}
		else
		{
			cub->raycast.sidedist_y += cub->raycast.deltaDistY;
			cub->raycast.mapY += cub->raycast.stepY;
			cub->raycast.side = 1;
		}
		if (cub->map.matrix[cub->raycast.mapX][cub->raycast.mapY] == '1'
			|| cub->map.matrix[cub->raycast.mapX][cub->raycast.mapY] == '2')
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
		cub->raycast.perpWallDist = (cub->raycast.mapX - cub->raycast.posX
				+ (1 - cub->raycast.stepX) / 2) / cub->raycast.raydir_x;
	else
		cub->raycast.perpWallDist = (cub->raycast.mapY - cub->raycast.posY
				+ (1 - cub->raycast.stepY) / 2) / cub->raycast.raydir_y;
	cub->raycast.line_height = (int)(cub->eje_y / cub->raycast.perpWallDist);
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
		cub->raycast.stepX = -1;
		cub->raycast.sidedist_x = (cub->raycast.posX - cub->raycast.mapX)
			* cub->raycast.deltaDistX;
	}
	else
	{
		cub->raycast.stepX = 1;
		cub->raycast.sidedist_x = (cub->raycast.mapX + 1.0 - cub->raycast.posX)
			* cub->raycast.deltaDistX;
	}
	if (cub->raycast.raydir_y < 0)
	{
		cub->raycast.stepY = -1;
		cub->raycast.sidedist_y = (cub->raycast.posY - cub->raycast.mapY)
			* cub->raycast.deltaDistY;
	}
	else
	{
		cub->raycast.stepY = 1;
		cub->raycast.sidedist_y = (cub->raycast.mapY + 1.0 - cub->raycast.posY)
			* cub->raycast.deltaDistY;
	}
}

/*
** calculate ray position and direction
** length of ray from one x or y-side to next x or y-side
**/

static void	calculate_ray(t_cub *cub, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)(cub->eje_x) - 1;
	cub->raycast.raydir_x = cub->raycast.dirX + cub->raycast.planeX * cameraX;
	cub->raycast.raydir_y = cub->raycast.dirY + cub->raycast.planeY * cameraX;
	cub->raycast.mapX = (int)(cub->raycast.posX);
	cub->raycast.mapY = (int)(cub->raycast.posY);
	cub->raycast.deltaDistX = fabs(1 / cub->raycast.raydir_x);
	cub->raycast.deltaDistY = fabs(1 / cub->raycast.raydir_y);
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
