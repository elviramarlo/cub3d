/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 23:47:48 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:35:17 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	parse_elements(t_cub *cub, char *line)
{
	printf("%s\n", line);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ' && !cub->check.north)
		parse_north(cub, line);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' '
		&& !cub->check.south)
		parse_south(cub, line);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' '
		&& !cub->check.west)
		parse_west(cub, line);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' '
		&& !cub->check.east)
		parse_east(cub, line);
	else if (line[0] == 'S' && line[1] == ' ' && !cub->check.sprite)
		parse_sprite(cub, line);
	/* else if (line[0] == 'R' && line[1] == ' ' && !cub->check.resol)
		parse_resolution(cub, line); */
	else if (line[0] == 'F' && line[1] == ' ' && !cub->check.floor)
		parse_floor(cub, line);
	else if (line[0] == 'C' && line[1] == ' ' && !cub->check.ceiling)
		parse_ceiling(cub, line);
	else if (line[0] != '\0')
		print_error("Argumentos incorrectos");
}
