/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_east.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:08:48 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 13:17:37 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	open_fd(t_cub *cub)
{
	cub->fd.t_east = open(cub->text_east, O_RDONLY);
	if (cub->fd.t_east < 0)
		print_error("Incorrect east texture");
	cub->check.east++;
	cub->check.num_elems++;
}

void	parse_east(t_cub *cub, char *line)
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
		if (line[i] != '\0' && line[i] != ' ' && cub->text_east)
			print_error("Too many east textures");
		if (line[i] != ' ')
		{
			x = i;
			while (line[i] != '\0' && line[i] != ' ')
			{
				i++;
				len++;
			}
			cub->text_east = ft_substr(line, x, len);
		}
	}
	open_fd(cub);
}
