/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:14:02 by elvmarti          #+#    #+#             */
/*   Updated: 2021/05/19 16:55:48 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	iter_cub_list(t_cub *cub, t_list *lst, void (*f)(t_cub *, void *))
{
	t_list	*ptr;

	if (lst)
	{
		while (lst)
		{
			ptr = lst->next;
			f(cub, lst->content);
			lst = ptr;
		}
	}
}
