/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:15:44 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/20 09:31:17 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"

int	print_error(char *context, char *str, int line_nb)
{
	ft_putstr_fd("Error: miniRT: ", 2);
	if (context)
	{
		ft_putstr_fd(context, 2);
		ft_putstr_fd(": ", 2);
	}
	if (line_nb >= 0)
	{
		ft_putstr_fd("line ", 2);
		ft_putnbr_fd(line_nb, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (FAILURE);
}
