/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:47:51 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 08:18:02 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "miniRT.h"
#include "mlx_app.h"
#include "parsing.h"

//static const t_obj_parse	g_parser[7] = {
//{"A", {parse_double, parse_color}},
//{"c", {parse_vec, parse_vec, parse_double}},
//{"l", {parse_vec, parse_double, parse_color}},
//{"sp", {parse_vec, parse_double, parse_color}},
//{"pl", {parse_vec, parse_vec, parse_color}},
//{"cy", {parse_vec, parse_vec, parse_double, parse_double, parse_color}}
//};

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

int	parse_ambient(char *data, t_scene *scene, bool *amb_init)
{
	char	**split;
	int		i;
	t_light	light;

	i = 0;
	if (*amb_init == true)
		return (FAILURE);
	*amb_init = true;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 2)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[0], &light.intensity) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (light.intensity < 0.0 || light.intensity > 1.0)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[1], &light.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	printf("A ratio: %f\n", light.intensity);
	printf("A color: %f, %f, %f\n", light.color.x, light.color.y, light.color.z);
	(void)scene;
	return (ft_split_free(split), SUCCESS);
}

int	parse_camera(char *data, t_scene *scene, bool *cam_init)
{
	char	**split;
	int		i;

	i = 0;
	if (*cam_init == true)
		return (FAILURE);
	*cam_init = true;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 3)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &scene->cam.pos) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &scene->cam.look_at) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[2], &scene->cam.size) == FAILURE)
		return (ft_split_free(split), FAILURE);
	printf("C pos: %f, %f, %f\n", scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
	printf("C dir: %f, %f, %f\n", scene->cam.look_at.x, scene->cam.look_at.y, scene->cam.look_at.z);
	printf("C fov: %f\n", scene->cam.size);
	return (ft_split_free(split), SUCCESS);
}

int	parse_light(char *data, t_scene *scene)
{
	char	**split;
	int		i;
	t_light	light;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 3)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &light.pos) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &light.intensity) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[2], &light.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	printf("l pod: %f, %f, %f\n", light.pos.x, light.pos.y, light.pos.z);
	printf("l intensity: %f\n", light.intensity);
	printf("l color: %f, %f, %f\n", light.color.x, light.color.y, light.color.z);
	(void)scene;
	return (ft_split_free(split), SUCCESS);
}

int	parse_sphere(char *data, t_scene *scene)
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
	printf("sp center: %f, %f, %f\n", sphere.center.x, sphere.center.y, sphere.center.z);
	printf("sp radius: %f\n", sphere.radius);
	printf("sp color: %f, %f, %f\n", sphere.color.x, sphere.color.y, sphere.color.z);
	(void)scene;
	return (ft_split_free(split), SUCCESS);
}

int	parse_plane(char *data, t_scene *scene)
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
	if (i != 3)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &plane.center) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &plane.normal) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[2], &plane.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	printf("pl center: %f, %f, %f\n", plane.center.x, plane.center.y, plane.center.z);
	printf("pl normal: %f, %f, %f\n", plane.normal.x, plane.normal.y, plane.normal.z);
	printf("pl color: %f, %f, %f\n", plane.color.x, plane.color.y, plane.color.z);
	(void)scene;
	return (ft_split_free(split), SUCCESS);
}

int	parse_cylinder(char *data, t_scene *scene)
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
	if (parse_vec(split[1], &cylinder.normal) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[2], &cylinder.radius) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[3], &cylinder.height) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[4], &cylinder.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	printf("cy center: %f, %f, %f\n", cylinder.center.x, cylinder.center.y, cylinder.center.z);
	printf("cy normal: %f, %f, %f\n", cylinder.normal.x, cylinder.normal.y, cylinder.normal.z);
	printf("cy radius: %f\n", cylinder.radius);
	printf("cy height: %f\n", cylinder.height);
	printf("cy color: %f, %f, %f\n", cylinder.color.x, cylinder.color.y, cylinder.color.z);
	(void)scene;
	return (ft_split_free(split), SUCCESS);
}