/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:08:27 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:07:46 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	draw_n_pixels(int n_pixels, t_cub *cub, int i, int i2, int color)
{
	int	x;
	int	x2;

	x = 0;
	while (x < n_pixels)
	{
		x2 = 0;
		while (x2 < n_pixels)
		{
			my_mlx_pixel_put(&cub->img, i + x + 5, i2 + x2 + 5, color);
			x2++;
		}
		x++;
	}
}

static void	set_color(t_cub *cub, int i, int i2, int *color)
{
	if (cub->map.matrix[i][i2] == '1')
		*color = 128;
	else if (cub->map.matrix[i][i2] == '0' || cub->map.matrix[i][i2] == '3')
		*color = 16044095;
	else if (cub->map.matrix[i][i2] == '2')
		*color = 5422720;
	if ((int)cub->raycast.posX == i && (int)cub->raycast.posY == i2)
		*color = 13321013;
}

static void	bonus_mapa(t_cub *cub)
{
	int w = 0;
	int x = 0;
	int y = 0;
	int q = 0;
	int color = 321123321;

	while (cub->map.matrix[x])
	{
		y = 0;
		q = 0;
		while(cub->map.matrix[x][y])
		{
			set_color(cub, x, y, &color);
			if (cub->map.matrix[x][y] != ' ')
				draw_n_pixels(5, cub, q + y, w + x, color);
			y++;
			q+= 5;
		}
		w += 5;
		x++;	
	}
}

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
	bonus_mapa(cub);
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
	if (cub->map.matrix[cub->raycast.mapX][cub->raycast.mapY] == '2')
			cub->raycast.tex_num = 4;
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
