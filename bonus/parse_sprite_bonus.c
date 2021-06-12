/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:12:44 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/12 22:11:10 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	open_fd(t_cub *cub)
{
	cub->fd.t_sprite = open(cub->text_sprite, O_RDONLY);
	if (cub->fd.t_sprite < 0)
		print_error("Textura del sprite incorrecta");
	cub->check.sprite++;
	cub->check.num_elems++;
}

void	parse_sprite(t_cub *cub, char *line)
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
		if (line[i] != '\0' && line[i] != ' ' && cub->text_sprite)
			print_error("Demasiadas texturas del sprite");
		if (line[i] != ' ')
		{
			x = i;
			while (line[i] != '\0' && line[i] != ' ')
			{
				i++;
				len++;
			}
			cub->text_sprite = ft_substr(line, x, len);
		}
	}
	open_fd(cub);
}
