/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:04:46 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 16:35:59 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "miniRT.h"
#include "parsing.h"

int	parse_double(char *data, void *value)
{
	double	*d;

	d = (double *)value;
	if (ft_isdouble(data) == 0)
		return (FAILURE);
	*d = ft_atof(data);
	return (SUCCESS);
}

int	parse_vec(char *data, void *value)
{
	char	**split;
	int		i;
	t_vec *vec;

	vec = (t_vec *)value;
	i = 0;
	split = ft_split(data, ",");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 3)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[0], &vec->x) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &vec->y) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[2], &vec->z) == FAILURE)
		return (ft_split_free(split), FAILURE);
	return (ft_split_free(split), SUCCESS);
}

int	parse_color(char *data, void *value)
{
	t_vec	*rgb;

	rgb = (t_vec *)value;
	if (parse_vec(data, rgb) == FAILURE)
		return (FAILURE);
	if (rgb->x < 0 || rgb->x > 255)
		return (FAILURE);
	if (rgb->y < 0 || rgb->y > 255)
		return (FAILURE);
	if (rgb->z < 0 || rgb->z > 255)
		return (FAILURE);
	return (SUCCESS);
}

int parse_texture(char *data, void *value)
{
	char	**file;
	int		fd;

	file = (char **)value;
	fd = open(data, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	close(fd);
	*file = data;
	return (SUCCESS);
}
