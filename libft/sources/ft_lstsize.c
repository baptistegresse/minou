/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:34:23 by bgresse           #+#    #+#             */
/*   Updated: 2023/01/11 11:48:51 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}