/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:31:49 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/02 11:48:17 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	keys_rotate_right(t_cub *cub)
{
	double	oldDirX;
	double	oldPlaneX;

	if (cub->key.key_right)
	{
		oldDirX = cub->raycast.dirX;
		cub->raycast.dirX = cub->raycast.dirX * cos(-cub->raycast.rotSpeed)
			- cub->raycast.dirY * sin(-cub->raycast.rotSpeed);
		cub->raycast.dirY = oldDirX * sin(-cub->raycast.rotSpeed)
			+ cub->raycast.dirY * cos(-cub->raycast.rotSpeed);
		oldPlaneX = cub->raycast.planeX;
		cub->raycast.planeX = cub->raycast.planeX * cos(-cub->raycast.rotSpeed)
			- cub->raycast.planeY * sin(-cub->raycast.rotSpeed);
		cub->raycast.planeY = oldPlaneX * sin(-cub->raycast.rotSpeed)
			+ cub->raycast.planeY * cos(-cub->raycast.rotSpeed);
	}
}

static void	keys_rotate_left(t_cub *cub)
{
	double	oldDirX;
	double	oldPlaneX;

	if (cub->key.key_left)
	{
		oldDirX = cub->raycast.dirX;
		cub->raycast.dirX = cub->raycast.dirX * cos(cub->raycast.rotSpeed)
			- cub->raycast.dirY * sin(cub->raycast.rotSpeed);
		cub->raycast.dirY = oldDirX * sin(cub->raycast.rotSpeed)
			+ cub->raycast.dirY * cos(cub->raycast.rotSpeed);
		oldPlaneX = cub->raycast.planeX;
		cub->raycast.planeX = cub->raycast.planeX * cos(cub->raycast.rotSpeed)
			- cub->raycast.planeY * sin(cub->raycast.rotSpeed);
		cub->raycast.planeY = oldPlaneX * sin(cub->raycast.rotSpeed)
			+ cub->raycast.planeY * cos(cub->raycast.rotSpeed);
	}
}

static void	keys_ws(t_cub *cub)
{
	if (cub->key.key_w)
	{
		if (cub->map.matrix[(int)(cub->raycast.posX + cub->raycast.dirX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)] != '1')
			cub->raycast.posX += cub->raycast.dirX * cub->raycast.moveSpeed;
		if (cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				+ cub->raycast.dirY * cub->raycast.moveSpeed)] != '1')
			cub->raycast.posY += cub->raycast.dirY * cub->raycast.moveSpeed;
	}
	if (cub->key.key_s)
	{
		if (cub->map.matrix[(int)(cub->raycast.posX - cub->raycast.dirX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)] != '1')
			cub->raycast.posX -= cub->raycast.dirX * cub->raycast.moveSpeed;
		if (cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				- cub->raycast.dirY * cub->raycast.moveSpeed)] != '1')
			cub->raycast.posY -= cub->raycast.dirY * cub->raycast.moveSpeed;
	}
}

static void	keys_ad(t_cub *cub)
{
	if (cub->key.key_a)
	{
		if (cub->map.matrix[(int)(cub->raycast.posX - cub->raycast.planeX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)] != '1')
			cub->raycast.posX -= cub->raycast.planeX * cub->raycast.moveSpeed;
		if (cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				- cub->raycast.planeY * cub->raycast.moveSpeed)] != '1')
			cub->raycast.posY -= cub->raycast.planeY * cub->raycast.moveSpeed;
	}
	if (cub->key.key_d)
	{
		if (cub->map.matrix[(int)(cub->raycast.posX + cub->raycast.planeX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)] != '1')
			cub->raycast.posX += cub->raycast.planeX * cub->raycast.moveSpeed;
		if (cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				+ cub->raycast.planeY * cub->raycast.moveSpeed)] != '1')
			cub->raycast.posY += cub->raycast.planeY * cub->raycast.moveSpeed;
	}
}

void	keys(t_cub *cub)
{
	keys_ws(cub);
	keys_ad(cub);
	keys_rotate_right(cub);
	keys_rotate_left(cub);
}
