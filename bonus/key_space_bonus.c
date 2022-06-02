/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_space_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 23:08:38 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:13:55 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	key_space(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->key.key_space)
	{
		x = (int)(cub->raycast.pos_x + cub->raycast.dir_x);
		y = (int)(cub->raycast.pos_y + cub->raycast.dir_y);
		if (cub->map.matrix[x][y] == '2')
			cub->map.matrix[x][y] = '3';
		else if (cub->map.matrix[x][y] == '3')
			cub->map.matrix[x][y] = '2';
		cub->key.key_space = 0;
	}
}
