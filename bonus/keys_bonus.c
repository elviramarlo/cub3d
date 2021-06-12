/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:31:49 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:08:42 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

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

static void	key_space(t_cub *cub)
{
	int	x;
	int	y;
	if(cub->key.key_space)
	{
		x = (int)(cub->raycast.posX + cub->raycast.dirX);
		y = (int)(cub->raycast.posY + cub->raycast.dirY);
		if (cub->map.matrix[x][y] == '2')
			cub->map.matrix[x][y] = '3';
		else if (cub->map.matrix[x][y] == '3')
			cub->map.matrix[x][y] = '2';
		cub->key.key_space = 0;
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
	int x = cub->map.matrix[(int)(cub->raycast.posX + cub->raycast.dirX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)];
	int y = cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				+ cub->raycast.dirY * cub->raycast.moveSpeed)];
	if (cub->key.key_w)
	{
		if (x != '1' && x != '2')
			cub->raycast.posX += cub->raycast.dirX * cub->raycast.moveSpeed;
		if (y != '1' && y != '2')
			cub->raycast.posY += cub->raycast.dirY * cub->raycast.moveSpeed;
	}
	x = cub->map.matrix[(int)(cub->raycast.posX - cub->raycast.dirX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)];
	y = cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				- cub->raycast.dirY * cub->raycast.moveSpeed)];
	if (cub->key.key_s)
	{
		if (x != '1' && x!= '2')
			cub->raycast.posX -= cub->raycast.dirX * cub->raycast.moveSpeed;
		if (y != '1' && y != '2')
			cub->raycast.posY -= cub->raycast.dirY * cub->raycast.moveSpeed;
	}
}

static void	keys_ad(t_cub *cub)
{
	int x;
	int y;

	x = cub->map.matrix[(int)(cub->raycast.posX - cub->raycast.planeX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)];
	y =  cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				- cub->raycast.planeY * cub->raycast.moveSpeed)];
	if (cub->key.key_a)
	{
		if (x != '1' && x != '2')
			cub->raycast.posX -= cub->raycast.planeX * cub->raycast.moveSpeed;
		if (x != '1' && x != '2')
			cub->raycast.posY -= cub->raycast.planeY * cub->raycast.moveSpeed;
	}

	x = cub->map.matrix[(int)(cub->raycast.posX + cub->raycast.planeX
				* cub->raycast.moveSpeed)][(int)(cub->raycast.posY)];
	y = cub->map.matrix[(int)(cub->raycast.posX)][(int)(cub->raycast.posY
				+ cub->raycast.planeY * cub->raycast.moveSpeed)];
	if (cub->key.key_d)
	{
		if (x != '1' && x != '2')
			cub->raycast.posX += cub->raycast.planeX * cub->raycast.moveSpeed;
		if (x != '1' && x != '2')
			cub->raycast.posY += cub->raycast.planeY * cub->raycast.moveSpeed;
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
