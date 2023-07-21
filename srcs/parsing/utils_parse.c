/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:06:20 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/19 15:35:27 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "miniRT.h"

double	ft_atof(const char *str)
{
	int		sign;
	double	result;
	double	factor;

	sign = 1;
	result = 0.0;
	factor = 0.1;
	while ((*str == ' ' || (*str >= '\t' && *str <= '\r')))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
		result = result * 10 + (*(str++) - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result += (*(str++) - '0') * factor;
			factor *= 0.1;
		}
	}
	return (result * sign);
}

void	ft_split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_isdouble(char *str)
{
	if ((*str == '-' || *str == '+') && ft_isdigit(*(str + 1)))
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (1);
	else if (*str == '.' && ft_isdigit(*(++str)))
	{
		str++;
		while (*str && ft_isdigit(*str))
			str++;
		if (*str == '\0')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	check_nb_value(char **split, int nb)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != nb)
		return (FAILURE);
	return (SUCCESS);
}

int	is_separator(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}
