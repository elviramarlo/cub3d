/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_west.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:08:20 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/07 19:41:13 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	open_fd(t_cub *cub)
{
	cub->fd.t_west = open(cub->text_west, O_RDONLY);
	if (cub->fd.t_west < 0)
		print_error("Textura oeste incorrecta");
	cub->check.west++;
	cub->check.num_elems++;
}

void	parse_west(t_cub *cub, char *line)
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
		if (line[i] != '\0' && line[i] != ' ' && cub->text_west)
			print_error("Demasiadas texturas oeste");
		if (line[i] != ' ')
		{
			x = i;
			while (line[i] != '\0' && line[i] != ' ')
			{
				i++;
				len++;
			}
			cub->text_west = ft_substr(line, x, len);
		}
	}
	open_fd(cub);
}
