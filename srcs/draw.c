/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:08:27 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/08 16:44:29 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	draw_walls(t_cub *cub, int x, int draw, int color)
{
	draw = cub->raycast.drawstart;
	while (draw <= cub->raycast.drawend)
	{
		cub->raycast.tex_y = (int)cub->raycast.tex_pos
			& (cub->height[cub->raycast.tex_num] - 1);
		cub->raycast.tex_pos += cub->raycast.step;
		color = my_pixel_get(&cub->textures[cub->raycast.tex_num],
				cub->raycast.tex_x, cub->raycast.tex_y);
		my_mlx_pixel_put(&cub->img, x, draw, color);
		draw++;
	}
}

/**
** Cast the texture coordinate to integer,
** and mask with (texHeight - 1) in case of overflow
**/

void	draw_pixels(t_cub *cub, int x)
{
	int	draw;
	int	color;

	draw = 0;
	color = 0;
	while (draw <= cub->eje_y / 2)
	{
		my_mlx_pixel_put(&cub->img, x, draw, cub->color_c_trgb);
		draw++;
	}
	draw = cub->eje_y / 2;
	while (draw < cub->eje_y)
	{
		my_mlx_pixel_put(&cub->img, x, draw, cub->color_f_trgb);
		draw++;
	}
	draw_walls(cub, x, draw, color);
}

/**
** calculate value of wallX
** How much to increase the texture coordinate per screen pixel
** Starting texture coordinate
**/

static void	texturing_calculation_2(t_cub *cub)
{
	if (cub->raycast.side == 0 && cub->raycast.raydir_x > 0)
		cub->raycast.tex_x = cub->width[cub->raycast.tex_num]
			- cub->raycast.tex_x - 1;
	if (cub->raycast.side == 1 && cub->raycast.raydir_y < 0)
		cub->raycast.tex_x = cub->width[cub->raycast.tex_num]
			- cub->raycast.tex_x - 1;
	cub->raycast.step = 1.0 * cub->height[cub->raycast.tex_num]
		/ cub->raycast.line_height;
	cub->raycast.tex_pos = (cub->raycast.drawstart - cub->eje_y
			/ 2 + cub->raycast.line_height / 2) * cub->raycast.step;
}

void	texturing_calculation(t_cub *cub)
{
	double	wallX;

	if (cub->raycast.side == 0 && cub->raycast.raydir_x < 0)
		cub->raycast.tex_num = 0;
	else if (cub->raycast.side == 0 && cub->raycast.raydir_x > 0)
		cub->raycast.tex_num = 1;
	else if (cub->raycast.side == 1 && cub->raycast.raydir_y < 0)
		cub->raycast.tex_num = 2;
	else if (cub->raycast.side == 1 && cub->raycast.raydir_y > 0)
		cub->raycast.tex_num = 3;
	if (cub->raycast.side == 0)
		wallX = cub->raycast.posY + cub->raycast.perpWallDist
			* cub->raycast.raydir_y;
	else
		wallX = cub->raycast.posX + cub->raycast.perpWallDist
			* cub->raycast.raydir_x;
	wallX -= floor((wallX));
	cub->raycast.tex_x = (int)(wallX
			* (double)(cub->width[cub->raycast.tex_num]));
	texturing_calculation_2(cub);
}
