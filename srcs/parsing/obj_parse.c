/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:47:51 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/12 15:23:37 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "miniRT.h"
#include "mlx_app.h"

int	parse_sphere(char *data, t_app *app)
{
	char		**split;
	int			i;
	t_sphere	sphere;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 3)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &sphere.center) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &sphere.radius) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[2], &sphere.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (obj_add_sphere(&sphere, &app->scene) == FAILURE)
		return (ft_split_free(split), FAILURE);
	return (ft_split_free(split), SUCCESS);
}

int	parse_plane(char *data, t_app *app)
{
	char	**split;
	int		i;
	t_plane	plane;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 4)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &plane.center) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &plane.direc) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[2], &plane.size) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[3], &plane.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (obj_add_plane(&plane, &app->scene) == FAILURE)
		return (ft_split_free(split), FAILURE);
	return (ft_split_free(split), SUCCESS);
}

int	parse_cylinder(char *data, t_app *app)
{
	char		**split;
	int			i;
	t_cylinder	cylinder;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 5)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &cylinder.center) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &cylinder.direc) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[2], &cylinder.radius) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[3], &cylinder.height) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[4], &cylinder.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (obj_add_cylinder(&cylinder, &app->scene) == FAILURE)
		return (ft_split_free(split), FAILURE);
	return (ft_split_free(split), SUCCESS);
}

int parse_cone(char *data, t_app *app)
{
	char **split;
	int i;
	t_cone cone;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 5)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &cone.center) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &cone.direc) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[2], &cone.radius) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[3], &cone.height) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[4], &cone.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (obj_add_cone(&cone, &app->scene) == FAILURE)
		return (ft_split_free(split), FAILURE);
	return (ft_split_free(split), SUCCESS);
}
