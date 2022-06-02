/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_north_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:01:04 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:30:51 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	open_fd(t_cub *cub)
{
	cub->fd.t_north = open(cub->text_north, O_RDONLY);
	if (cub->fd.t_north < 0)
		print_error("Incorrect north texture");
	cub->check.north++;
	cub->check.num_elems++;
}

void	parse_north(t_cub *cub, char *line)
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
		if (line[i] != '\0' && line[i] != ' ' && cub->text_north)
			print_error("Too many north textures");
		if (line[i] != ' ')
		{
			x = i;
			while (line[i] != '\0' && line[i] != ' ')
			{
				i++;
				len++;
			}
			cub->text_north = ft_substr(line, x, len);
		}
	}
	open_fd(cub);
}
