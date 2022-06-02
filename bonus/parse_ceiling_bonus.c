/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ceiling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:10:01 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:35:35 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	color_int(t_cub *cub)
{
	cub->color_c_r = ft_atoi(cub->ccr);
	if (cub->color_c_r < 0 || cub->color_c_r > 255)
		print_error("Incorrect value of the color of the ceiling");
	cub->color_c_g = ft_atoi(cub->ccg);
	if (cub->color_c_g < 0 || cub->color_c_g > 255)
		print_error("Incorrect value of the color of the ceiling");
	cub->color_c_b = ft_atoi(cub->ccb);
	if (cub->color_c_b < 0 || cub->color_c_b > 255)
		print_error("Incorrect value of the color of the ceiling");
	cub->color_c_trgb = create_trgb(0, cub->color_c_r,
			cub->color_c_g, cub->color_c_b);
	cub->check.ceiling++;
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
		print_error("A comma is missing between the ceiling values");
	if (!cub->ccr)
		cub->ccr = ft_substr(line, x, len);
	else if (!cub->ccg)
		cub->ccg = ft_substr(line, x, len);
	else if (!cub->ccb)
		cub->ccb = ft_substr(line, x, len);
	len = 0;
}

void	parse_ceiling(t_cub *cub, char *line)
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
			print_error("Invalid characters on the ceiling");
	}
	if (!cub->ccr || !cub->ccg || !cub->ccb)
		print_error("Ceiling information missing");
	color_int(cub);
}
