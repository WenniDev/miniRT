/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:47:51 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 14:29:57 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "miniRT.h"
#include "mlx_app.h"
#include "parsing.h"
#include "object.h"

//static const t_obj_parse	g_parser[7] = {
//{"A", {parse_double, parse_color, NULL}},
//{"C", {parse_vec, parse_vec, parse_double, NULL}},
//{"l", {parse_vec, parse_double, parse_color, NULL}},
//{"sp", {parse_vec, parse_double, parse_color, NULL}},
//{"pl", {parse_vec, parse_vec, parse_color, NULL}},
//{"cy", {parse_vec, parse_vec, parse_double, parse_double, parse_color, NULL}}
//};
//
//static const t_obj_create 	g_obj_create[4] = {
////{"A", create_ambient},
////{"C", create_camera},
////{"l", create_light},
//{"sp", sphere_create},
//{"pl", plane_create},
//{"cy", cylinder_create},
//{"cn", cone_create}
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

int parse_texture(char *data, void *value)
{
	printf("texture: %s\n", data);
	return (SUCCESS);
}

//t_obj_parse get_function(char *obj)
//{
//	int i;
//
//	i = 0;
//	while (ft_strcmp(g_parser[i].data, obj) != 0)
//		i++;
//	return (g_parser[i]);
//}
//
//int get_function_nb(t_obj_parse steps)
//{
//	int	i;
//
//	i = 0;
//	while (steps.parse[i])
//		i++;
//	return (i);
//}
//
//void	*get_object(char *type)
//{
//	int	i;
//
//	i = 0;
//	while (ft_strcmp(g_obj_create[i].type, type) != 0)
//		i++;
//	return (g_obj_create[i].create());
//}
//
//int parse_object(char *data, t_scene *scene)
//{
//	char		**split;
//	int			i;
//	t_obj_parse	steps;
//
//	i = 0;
//	split = ft_split(data, " \t\r\n\v\f");
//	if (!split)
//		return (FAILURE);
//	while (split[i])
//		i++;
//	steps = get_function(split[0]);
//	if (i != get_function_nb(steps) + 1)
//		return (FAILURE);
//	i = 0;
//	while (split[++i])
//		get_object(split[0]));
//		//		if (steps.parse[i - 1](split[i], (sizeof(steps.parse[i - 1]))&scene[i]) == FAILURE)
//		//			return (FAILURE);
//	(void)scene;
//	printf("%s parsed\n", split[0]);
//	return (SUCCESS);
//}

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
	if (i != 4)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &plane.center) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &plane.normal) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[2], &plane.size) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[3], &plane.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_texture(split[4], &plane.texture) == FAILURE)
		return (ft_split_free(split), FAILURE);

	t_obj_lst *new = plane_create();
//	t_material floor_material = simple_mat_const(vec_create(1.0, 1.0, 1.0), 0.5, 0.0);
//	t_texture checker1 = create_checker_texture();

//	checker1.tfm = set_transform(vec_create(0.0, 0.0, 0.0), 0.0, vec_create(16.0, 16.0, 0.0));
	gtfm_set_transform(plane.center, plane.normal,
					   plane.size, &new->gtfm);
	new->color = plane.color;
//	assign_material(new, floor_material);
//	assign_texture(&new->material, checker1);
	add_obj(&scene->obj_lst, new);
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
	(void)scene;
	return (ft_split_free(split), SUCCESS);
}