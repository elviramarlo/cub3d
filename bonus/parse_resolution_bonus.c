/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:10:29 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:30:14 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	make_resolution(t_cub *cub)
{
	int	x;
	int	y;

	cub->eje_x = 1000;
	cub->eje_y = 1000;
	mlx_get_screen_size(cub->mlx, &x, &y);
	if (cub->eje_x < 0 || cub->eje_x > x)
		cub->eje_x = x;
	if (cub->eje_y < 0 || cub->eje_y > y)
		cub->eje_y = y;
	if (cub->eje_x < 50 || cub->eje_y < 50)
		print_error("Resolución muy pequeña (mínimo 50 50)");
}