/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:08:27 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:13:35 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

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
	bonus_minimap(cub);
}

/**
** Draw the color of the ceiling and the floor
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
** calculate value of wall_x
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
	double	wall_x;

	if (cub->raycast.side == 0 && cub->raycast.raydir_x < 0)
		cub->raycast.tex_num = 0;
	else if (cub->raycast.side == 0 && cub->raycast.raydir_x > 0)
		cub->raycast.tex_num = 1;
	else if (cub->raycast.side == 1 && cub->raycast.raydir_y < 0)
		cub->raycast.tex_num = 2;
	else if (cub->raycast.side == 1 && cub->raycast.raydir_y > 0)
		cub->raycast.tex_num = 3;
	if (cub->map.matrix[cub->raycast.map_x][cub->raycast.map_y] == '2')
		cub->raycast.tex_num = 4;
	if (cub->raycast.side == 0)
		wall_x = cub->raycast.pos_y + cub->raycast.perp_wall_dist
			* cub->raycast.raydir_y;
	else
		wall_x = cub->raycast.pos_x + cub->raycast.perp_wall_dist
			* cub->raycast.raydir_x;
	wall_x -= floor((wall_x));
	cub->raycast.tex_x = (int)(wall_x
			* (double)(cub->width[cub->raycast.tex_num]));
	texturing_calculation_2(cub);
}
