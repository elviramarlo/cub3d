/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_space_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 23:08:38 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 23:10:40 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	key_space(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->key.key_space)
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
