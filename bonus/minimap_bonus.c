/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:06:46 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:15:31 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	draw_n_pixels(t_cub *cub, int i, int i2, int color)
{
	int	x;
	int	x2;
	int	n_pixels;

	x = 0;
	n_pixels = 5;
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
	if ((int)cub->raycast.pos_x == i && (int)cub->raycast.pos_y == i2)
		*color = 13321013;
}

void	bonus_minimap(t_cub *cub)
{
	int	x;
	int	y;
	int	w;
	int	q;
	int	color;

	x = 0;
	w = 0;
	color = 0;
	while (cub->map.matrix[x])
	{
		y = 0;
		q = 0;
		while (cub->map.matrix[x][y])
		{
			set_color(cub, x, y, &color);
			if (cub->map.matrix[x][y] != ' ')
				draw_n_pixels(cub, q + y, w + x, color);
			y++;
			q = q + 5;
		}
		w = w + 5;
		x++;
	}
}
