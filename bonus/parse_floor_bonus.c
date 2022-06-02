/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:09:40 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:32:42 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	color_int(t_cub *cub)
{
	cub->color_f_r = ft_atoi(cub->cfr);
	if (cub->color_f_r < 0 || cub->color_f_r > 255)
		print_error("Incorrect value of the color of the floor");
	cub->color_f_g = ft_atoi(cub->cfg);
	if (cub->color_f_g < 0 || cub->color_f_g > 255)
		print_error("Incorrect value of the color of the floor");
	cub->color_f_b = ft_atoi(cub->cfb);
	if (cub->color_f_b < 0 || cub->color_f_b > 255)
		print_error("Incorrect value of the color of the floor");
	cub->color_f_trgb = create_trgb(0, cub->color_f_r,
			cub->color_f_g, cub->color_f_b);
	cub->check.floor++;
	cub->check.num_elems++;
}

static void	color_string(t_cub *cub, char *line, int *i)
{
	int	x;
	int	len;

	len = 0;
	x = *i;
	while (ft_isdigit(line[*i]))
	{
		*i = *i + 1;
		len++;
	}
	while (line[*i] == ' ')
		*i = *i + 1;
	if (line[*i] == ',')
		*i = *i + 1;
	else if (line[*i] != ',' && line[*i])
		print_error("A comma is missing between the floor values");
	if (!cub->cfr)
		cub->cfr = ft_substr(line, x, len);
	else if (!cub->cfg)
		cub->cfg = ft_substr(line, x, len);
	else if (!cub->cfb)
		cub->cfb = ft_substr(line, x, len);
	len = 0;
}

void	parse_floor(t_cub *cub, char *line)
{
	int	i;

	i = 1;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]))
			color_string(cub, line, &i);
		if (line[i] != ' ' && line[i] && !(ft_isdigit(line[i])))
			print_error("Invalid characters on the floor");
	}
	if (!cub->cfr || !cub->cfg || !cub->cfb)
		print_error("Floor information missing");
	color_int(cub);
}
