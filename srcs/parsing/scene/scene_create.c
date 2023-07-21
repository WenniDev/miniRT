/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:10 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/21 14:40:17 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "miniRT.h"
#include "light.h"

void	set_camera(t_cam *cam, t_scene *scene)
{
	cam_init(&scene->cam);
	scene->cam.pos = cam->pos;
	scene->cam.look_at = cam->look_at;
	scene->cam.size = cam->size;
	scene->cam.up = cam->up;
	scene->cam.ratio = 16.0 / 9.0;
	cam_geometry(&scene->cam);
}

int	scene_add_light(t_light *light, t_scene *scene)
{
	t_light	*new;

	new = new_light();
	if (!new)
		return (FAILURE);
	new->pos = light->pos;
	new->color = light->color;
	new->intensity = light->intensity;
	add_light(&scene->light_lst, new);
	return (SUCCESS);

}

void	scene_add_ambiant(t_light *light, t_scene *scene)
{
	scene->amb_color = light->color;
	scene->amb_int = light->intensity;
}