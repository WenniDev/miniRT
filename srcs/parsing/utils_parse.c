/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:06:20 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 15:07:01 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

double	ft_atof(const char *str)
{
	int		sign;
	double	result;
	double	factor;

	sign = 1;
	result = 0.0;
	factor = 0.1;
	while (ft_isspace(*str))
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