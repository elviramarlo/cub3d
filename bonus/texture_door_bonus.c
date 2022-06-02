/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_door_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:12:44 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:19:01 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	texture_door(t_cub *cub)
{
	cub->fd.t_door = open("./textures/door.xpm", O_RDONLY);
	if (cub->fd.t_door < 0)
		print_error("Incorrect door texture");
	cub->text_door = ft_strdup("./textures/door.xpm");
}
