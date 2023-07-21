/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:10 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/21 13:59:31 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "miniRT.h"

int	parse_ambient(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char		**split;
	t_light		light;
	static bool	amb_init = false;

	if (amb_init == true)
		return (FAILURE);
	amb_init = true;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	if (check_nb_value(split, 2) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[0], &light.intensity) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (light.intensity < 0.0 || light.intensity > 1.0)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[1], &light.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	scene_add_ambiant(&light, &app->scene);
	((void)set_parse_step, (void)add_obj);
	return (ft_split_free(split), SUCCESS);
}

int	parse_camera(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char		**split;
	t_cam		cam;
	static bool	cam_init = false;

	if (cam_init == true)
		return (FAILURE);
	cam_init = true;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	if (check_nb_value(split, 4) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &cam.pos) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &cam.look_at) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[2], &cam.up) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[3], &cam.size) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (cam.size < 0.0 || cam.size > 180.0)
		return (ft_split_free(split), FAILURE);
	set_camera(&cam, &app->scene);
	((void)set_parse_step, (void)add_obj);
	return (ft_split_free(split), SUCCESS);
}

int	parse_light(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char	**split;
	t_light	light;

	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	if (check_nb_value(split, 3) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &light.pos) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &light.intensity) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (light.intensity < 0.0 || light.intensity > 1.0)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[2], &light.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	scene_add_light(&light, &app->scene);
	((void)set_parse_step, (void)add_obj);
	return (ft_split_free(split), SUCCESS);
}
