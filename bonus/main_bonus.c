/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:21:02 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/13 13:56:11 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static int	reading_fd(t_cub *cub, int *ret, char **line)
{
	*ret = get_next_line(cub->fd.fd, line);
	return (*ret);
}

static void	read_fd(t_cub *cub)
{
	char	*line;
	int		ret;

	while ((reading_fd(cub, &ret, &line)) >= 0)
	{
		if (cub->check.num_elems < 6)
		{
			parse_elements(cub, line);
			free(line);
		}
		else
		{
			parse_map(cub, line);
			free(line);
		}
		if (ret == 0)
			break ;
	}
	if (ret < 0)
		print_error("Fallo en la lectura del archivo");
	iter_cub_list(cub, cub->map.list, map_matrix1);
	make_resolution(cub);
	check_matrix(cub);
	start_cub(cub);
}

static void	check_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i] != '.')
	{
		if (argv[1][i] == '\0')
			print_error("Argumento incorrecto");
		i++;
	}
	if (ft_strncmp(".cub", &argv[1][i], ft_strlen(argv[1])))
		print_error("Argumento incorrecto");
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (argc < 2)
		print_error("Faltan argumentos");
	else if (argc > 2)
		print_error("Demasiados argumentos");
	else
	{
		check_argv(argv);
		cub.fd.fd = open(argv[1], O_RDONLY);
		if (cub.fd.fd < 0)
			print_error("Fallo en la apertura");
		read_fd(&cub);
	}
	return (0);
}
