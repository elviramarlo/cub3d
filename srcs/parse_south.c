/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_south.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:53:57 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/07 19:40:56 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	open_fd(t_cub *cub)
{
	cub->fd.t_south = open(cub->text_south, O_RDONLY);
	if (cub->fd.t_south < 0)
		print_error("Textura sur incorrecta");
	cub->check.south++;
	cub->check.num_elems++;
}

void	parse_south(t_cub *cub, char *line)
{
	int		i;
	int		x;
	int		len;

	i = 2;
	x = 0;
	len = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] != '\0' && line[i] != ' ' && cub->text_south)
			print_error("Demasiadas texturas sur");
		if (line[i] != ' ')
		{
			x = i;
			while (line[i] != '\0' && line[i] != ' ')
			{
				i++;
				len++;
			}
			cub->text_south = ft_substr(line, x, len);
		}
	}
	open_fd(cub);
}
