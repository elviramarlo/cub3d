/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:08:24 by elvmarti          #+#    #+#             */
/*   Updated: 2022/06/02 14:33:31 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static void	map_matrix2(t_cub *cub, void *content)
{
	int		i;
	char	*str;

	i = 0;
	str = content;
	while (str[i])
	{
		if (str[i] == '0')
			cub->map.matrix[cub->map.matrix_act_line][i] = '0';
		else if (str[i] == '1')
			cub->map.matrix[cub->map.matrix_act_line][i] = '1';
		else if (str[i] == '2')
			cub->map.matrix[cub->map.matrix_act_line][i] = '2';
		else if (str[i] == ' ')
			cub->map.matrix[cub->map.matrix_act_line][i] = ' ';
		else if (ft_strchr("NSWE", str[i]))
			cub->map.matrix[cub->map.matrix_act_line][i] = '0';
		i++;
	}
	while (i < cub->map.max_len_line)
	{
		cub->map.matrix[cub->map.matrix_act_line][i] = ' ';
		i++;
	}
	cub->map.matrix[cub->map.matrix_act_line][i] = '\0';
}

void	map_matrix1(t_cub *cub, void *content)
{
	int	i;

	i = 0;
	if (!cub->map.matrix)
	{
		cub->map.matrix = malloc(sizeof(char *) * (cub->map.lines + 1));
		if (!cub->map.matrix)
			print_error("Fallo en la asignación de memoria");
		while (i < cub->map.lines)
		{
			cub->map.matrix[i] = malloc(sizeof(char)
					* (cub->map.max_len_line + 1));
			if (!cub->map.matrix[i])
				print_error("Fallo en la asignación de memoria");
			i++;
		}
		cub->map.matrix[i] = NULL;
	}
	map_matrix2(cub, content);
	cub->map.matrix_act_line++;
}

static void	check_orientation(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("NSWE", line[i]))
		{
			if (!cub->map.player_o)
			{
				cub->map.player_o = line[i];
				cub->map.player_pos_x = cub->map.lines;
				cub->map.player_pos_y = i + 1;
			}
			else if (cub->map.player_o)
				print_error("Hay más de una orientación del jugador");
		}
		i++;
	}
}

static void	store_list_map(t_cub *cub, char *line)
{
	int		len;
	int		i;
	char	*aux;

	i = 0;
	len = ft_strlen(line);
	if (cub->map.max_len_line < len)
		cub->map.max_len_line = len;
	cub->map.lines++;
	aux = ft_strdup(line);
	ft_lstadd_back(&cub->map.list, ft_lstnew(aux));
	check_orientation(cub, line);
}

void	parse_map(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	if (!cub->check.north || !cub->check.south || !cub->check.east
		|| !cub->check.west || !cub->check.floor || !cub->check.ceiling)
		print_error("Some element is missing before the map");
	if (line[0] == '\0' && cub->check.map_start)
		cub->check.map_is_end++;
	else if (line[0] != '\0')
	{
		cub->check.map_start = 1;
		if (cub->check.map_is_end)
			print_error("There is content after the map");
		while (line[i])
		{
			if (!ft_strchr(" 012NSEW", line[i]))
				print_error("Invalid character on the map");
			i++;
		}
		store_list_map(cub, line);
	}
}
