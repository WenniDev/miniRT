/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:03:35 by rsabbah           #+#    #+#             */
/*   Updated: 2023/07/08 08:02:05 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	if (a == NULL || b == NULL)
		return (-1);
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}
