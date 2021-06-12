/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matrix_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 00:56:36 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:37:15 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	checkiar_mapa(t_cub *cub, int x, int y)
{
	while (cub->map.matrix[x])
	{
		printf("[%s]\n", cub->map.matrix[x]);
		while (cub->map.matrix[x][y])
		{
			if ((cub->map.matrix[x][y] == '0' || cub->map.matrix[x][y] == '2')
				&& (x == 0 || y == 0))
				print_error("Open map");
			if ((cub->map.matrix[x][y] == '0' || cub->map.matrix[x][y] == '2')
				&& cub->map.matrix[x + 1] == NULL)
				print_error("Open map");
			if (cub->map.matrix[x][y] == '0' || cub->map.matrix[x][y] == '2')
			{
				cub->check.matrix_zero = 1;
				if (cub->map.matrix[x - 1][y] == ' '
					|| cub->map.matrix[x + 1][y] == ' '
					|| cub->map.matrix[x][y - 1] == ' '
					|| cub->map.matrix[x][y + 1] == ' '
					|| cub->map.matrix[x][y + 1] == '\0')
					print_error("Open map");
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void	check_matrix(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (cub->map.lines < 3 || cub->map.max_len_line < 3)
		print_error("El mapa es demasiado corto");
	if (!cub->map.player_o)
		print_error("No se ha dado la posición del jugador");
	checkiar_mapa(cub, x, y);
	if (!cub->check.matrix_zero)
		print_error("Tiene que haber mínimo un 0 en el mapa");
	close_fds(cub);
}
