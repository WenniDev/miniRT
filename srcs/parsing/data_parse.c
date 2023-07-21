/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:04:46 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/21 15:28:37 by jopadova         ###   ########.fr       */
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
		return (print_error(FUNC, WRNG_DOUBLE, -1));
	*d = ft_atof(data);
	return (SUCCESS);
}

int	parse_vec(char *data, void *value)
{
	char	**split;
	int		i;
	t_vec	*vec;

	vec = (t_vec *)value;
	i = 0;
	split = ft_split(data, ",");
	if (!split)
		return (print_error(FUNC, MALLOC_ERR, -1));
	while (split[i])
		i++;
	if (i != 3)
		return (ft_split_free(split), print_error(FUNC, WRNG_VEC_VAL, -1));
	if (parse_double(split[0], &vec->x) == FAILURE)
		return (ft_split_free(split), print_error(FUNC, WRNG_VEC, -1));
	if (parse_double(split[1], &vec->y) == FAILURE)
		return (ft_split_free(split), print_error(FUNC, WRNG_VEC, -1));
	if (parse_double(split[2], &vec->z) == FAILURE)
		return (ft_split_free(split), print_error(FUNC, WRNG_VEC, -1));
	return (ft_split_free(split), SUCCESS);
}

int	parse_color(char *data, void *value)
{
	t_vec	*rgb;

	rgb = (t_vec *)value;
	if (parse_vec(data, rgb) == FAILURE)
		return (print_error(FUNC, WRNG_RGB, -1));
	if (rgb->x < 0 || rgb->x > 255)
		return (print_error(FUNC, WRNG_RGB, -1));
	if (rgb->y < 0 || rgb->y > 255)
		return (print_error(FUNC, WRNG_RGB, -1));
	if (rgb->z < 0 || rgb->z > 255)
		return (print_error(FUNC, WRNG_RGB, -1));
	*rgb = vec_mult(*rgb, 1.0 / 255.0);
	return (SUCCESS);
}

int	parse_texture(char *data, void *value)
{
	char	**file;
	int		fd;

	file = (char **)value;
	if (ft_strncmp(data + ft_strlen(data) - 4, ".xpm", 4))
		return (print_error(FUNC, WRNG_TX_EXT, -1));
	fd = open(data, O_RDONLY);
	if (fd < 0)
		return (print_error(FUNC, TX_NOT_FND, -1));
	close(fd);
	*file = data;
	return (SUCCESS);
}

int	get_nb_data(t_f_parse data[7])
{
	int	i;

	i = 0;
	while (data[i].value)
		i++;
	return (i);
}
