/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 21:34:07 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:07:25 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	hooks(t_cub *cub)
{
	mlx_hook(cub->window, DESTROY_NOTIFY, 0L, destroy, cub);
	mlx_hook(cub->window, KEY_PRESS, 1L << 0, key_press, cub);
	mlx_hook(cub->window, KEY_RELEASE, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->mlx, raycasting, cub);
	mlx_loop(cub->mlx);
}

static void	textures(t_cub *cub)
{
	char	**text[5];
	int		i;

	cub->img.img = mlx_new_image(cub->mlx, cub->eje_x, cub->eje_y);
	text[0] = &cub->text_north;
	text[1] = &cub->text_south;
	text[2] = &cub->text_west;
	text[3] = &cub->text_east;
	text[4] = &cub->text_sprite;
	i = 0;
	while (i < 5)
	{
		cub->textures[i].img = mlx_xpm_file_to_image(cub->mlx, *text[i],
				&cub->width[i], &cub->height[i]);
		if (!cub->textures[i].img)
			print_error("Error con las texturas");
		cub->textures[i].addr = mlx_get_data_addr(cub->textures[i].img,
				&cub->textures[i].bits_per_pixel, &cub->textures[i].line_length,
				&cub->textures[i].endian);
		i++;
	}
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
}

static void	orientation2(t_cub *cub)
{
	if (cub->map.player_o == 'E')
	{
		cub->raycast.dirX = 0;
		cub->raycast.dirY = 1;
		cub->raycast.planeX = 0.66;
		cub->raycast.planeY = 0;
	}
	if (cub->map.player_o == 'W')
	{
		cub->raycast.dirX = 0;
		cub->raycast.dirY = -1;
		cub->raycast.planeX = -0.66;
		cub->raycast.planeY = 0;
	}
}

static void	orientation(t_cub *cub)
{
	if (cub->map.player_o == 'N')
	{
		cub->raycast.dirX = -1;
		cub->raycast.dirY = 0;
		cub->raycast.planeX = 0;
		cub->raycast.planeY = 0.66;
	}
	if (cub->map.player_o == 'S')
	{
		cub->raycast.dirX = 1;
		cub->raycast.dirY = 0;
		cub->raycast.planeX = 0;
		cub->raycast.planeY = -0.66;
	}
	orientation2(cub);
}

void	start_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		print_error("No se pudo inicializar la mlx");
	cub->window = mlx_new_window(cub->mlx, cub->eje_x, cub->eje_y, "CUB3D");
	if (!cub->window)
		print_error("Fallo al abrir la ventana");
	cub->raycast.posX = cub->map.player_pos_x - 0.5;
	cub->raycast.posY = cub->map.player_pos_y - 0.5;
	cub->raycast.moveSpeed = 0.1;
	cub->raycast.rotSpeed = 0.1;
	orientation(cub);
	textures(cub);
	hooks(cub);
}
