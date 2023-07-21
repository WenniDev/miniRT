/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:56:13 by rsabbah           #+#    #+#             */
/*   Updated: 2023/07/08 08:02:05 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	long	l;

	l = (long)nbr;
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l = -l;
	}
	if (l >= 10)
		ft_putnbr_fd(l / 10, fd);
	ft_putchar_fd(l % 10 + 48, fd);
}
