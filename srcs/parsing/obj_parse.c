/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:47:51 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 15:20:48 by jopadova         ###   ########.fr       */
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
	if (i != 5)
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
	printf("%s\n", plane.texture);
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