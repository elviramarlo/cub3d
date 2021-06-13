/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:24:24 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/13 14:04:17 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	print_error(char *str)
{
	printf("\nError\n");
	printf(RED "\n  %s\n"RESET, str);
	system("leaks cub3D");
	exit(1);
}

void	close_fds(t_cub *cub)
{
	close(cub->fd.fd);
	close(cub->fd.t_east);
	close(cub->fd.t_north);
	close(cub->fd.t_south);
	close(cub->fd.t_west);
	close(cub->fd.t_door);
}
