/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 22:03:38 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:24:40 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

int	destroy(t_cub *cub)
{
	cub->text_east++;
	//system("leaks cub3D");
	exit(0);
	return (0);
}

int	key_release(int tecla, t_cub *cub)
{
	if (tecla == K_W)
		cub->key.key_w = 0;
	if (tecla == K_A)
		cub->key.key_a = 0;
	if (tecla == K_S)
		cub->key.key_s = 0;
	if (tecla == K_D)
		cub->key.key_d = 0;
	if (tecla == K_RIGHT)
		cub->key.key_right = 0;
	if (tecla == K_LEFT)
		cub->key.key_left = 0;
	if (tecla == SPACE)
		cub->key.key_space = 0;
	return (tecla);
}

int	key_press(int tecla, t_cub *cub)
{
	if (tecla == K_ESC)
		destroy(cub);
	if (tecla == K_W)
		cub->key.key_w = 1;
	if (tecla == K_A)
		cub->key.key_a = 1;
	if (tecla == K_S)
		cub->key.key_s = 1;
	if (tecla == K_D)
		cub->key.key_d = 1;
	if (tecla == K_RIGHT)
		cub->key.key_right = 1;
	if (tecla == K_LEFT)
		cub->key.key_left = 1;
	if (tecla == SPACE)
		cub->key.key_space = 1;
	return (tecla);
}
