/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:31:49 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:40:15 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	keys_rotate_right(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cub->key.key_right)
	{
		old_dir_x = cub->raycast.dir_x;
		cub->raycast.dir_x = cub->raycast.dir_x * cos(-cub->raycast.rot_speed)
			- cub->raycast.dir_y * sin(-cub->raycast.rot_speed);
		cub->raycast.dir_y = old_dir_x * sin(-cub->raycast.rot_speed)
			+ cub->raycast.dir_y * cos(-cub->raycast.rot_speed);
		old_plane_x = cub->raycast.plane_x;
		cub->raycast.plane_x = cub->raycast.plane_x
			* cos(-cub->raycast.rot_speed) - cub->raycast.plane_y
			* sin(-cub->raycast.rot_speed);
		cub->raycast.plane_y = old_plane_x * sin(-cub->raycast.rot_speed)
			+ cub->raycast.plane_y * cos(-cub->raycast.rot_speed);
	}
}

static void	keys_rotate_left(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cub->key.key_left)
	{
		old_dir_x = cub->raycast.dir_x;
		cub->raycast.dir_x = cub->raycast.dir_x * cos(cub->raycast.rot_speed)
			- cub->raycast.dir_y * sin(cub->raycast.rot_speed);
		cub->raycast.dir_y = old_dir_x * sin(cub->raycast.rot_speed)
			+ cub->raycast.dir_y * cos(cub->raycast.rot_speed);
		old_plane_x = cub->raycast.plane_x;
		cub->raycast.plane_x = cub->raycast.plane_x
			* cos(cub->raycast.rot_speed) - cub->raycast.plane_y
			* sin(cub->raycast.rot_speed);
		cub->raycast.plane_y = old_plane_x * sin(cub->raycast.rot_speed)
			+ cub->raycast.plane_y * cos(cub->raycast.rot_speed);
	}
}

static void	keys_ws(t_cub *cub)
{
	int	x;
	int	y;

	x = cub->map.matrix[(int)(cub->raycast.pos_x + cub->raycast.dir_x
			* cub->raycast.movespeed)][(int)(cub->raycast.pos_y)];
	y = cub->map.matrix[(int)(cub->raycast.pos_x)][(int)(cub->raycast.pos_y
			+ cub->raycast.dir_y * cub->raycast.movespeed)];
	if (cub->key.key_w)
	{
		if (x != '1' && x != '2')
			cub->raycast.pos_x += cub->raycast.dir_x * cub->raycast.movespeed;
		if (y != '1' && y != '2')
			cub->raycast.pos_y += cub->raycast.dir_y * cub->raycast.movespeed;
	}
	x = cub->map.matrix[(int)(cub->raycast.pos_x - cub->raycast.dir_x
			* cub->raycast.movespeed)][(int)(cub->raycast.pos_y)];
	y = cub->map.matrix[(int)(cub->raycast.pos_x)][(int)(cub->raycast.pos_y
			- cub->raycast.dir_y * cub->raycast.movespeed)];
	if (cub->key.key_s)
	{
		if (x != '1' && x != '2')
			cub->raycast.pos_x -= cub->raycast.dir_x * cub->raycast.movespeed;
		if (y != '1' && y != '2')
			cub->raycast.pos_y -= cub->raycast.dir_y * cub->raycast.movespeed;
	}
}

static void	keys_ad(t_cub *cub)
{
	int	x;
	int	y;

	x = cub->map.matrix[(int)(cub->raycast.pos_x - cub->raycast.plane_x
			* cub->raycast.movespeed)][(int)(cub->raycast.pos_y)];
	y = cub->map.matrix[(int)(cub->raycast.pos_x)][(int)(cub->raycast.pos_y
			- cub->raycast.plane_y * cub->raycast.movespeed)];
	if (cub->key.key_a)
	{
		if (x != '1' && x != '2')
			cub->raycast.pos_x -= cub->raycast.plane_x * cub->raycast.movespeed;
		if (x != '1' && x != '2')
			cub->raycast.pos_y -= cub->raycast.plane_y * cub->raycast.movespeed;
	}
	x = cub->map.matrix[(int)(cub->raycast.pos_x + cub->raycast.plane_x
			* cub->raycast.movespeed)][(int)(cub->raycast.pos_y)];
	y = cub->map.matrix[(int)(cub->raycast.pos_x)][(int)(cub->raycast.pos_y
			+ cub->raycast.plane_y * cub->raycast.movespeed)];
	if (cub->key.key_d)
	{
		if (x != '1' && x != '2')
			cub->raycast.pos_x += cub->raycast.plane_x * cub->raycast.movespeed;
		if (x != '1' && x != '2')
			cub->raycast.pos_y += cub->raycast.plane_y * cub->raycast.movespeed;
	}
}

void	keys(t_cub *cub)
{
	keys_ws(cub);
	keys_ad(cub);
	keys_rotate_right(cub);
	keys_rotate_left(cub);
	key_space(cub);
}
