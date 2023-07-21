/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:10 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/21 14:20:07 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "miniRT.h"

int	add_plane(t_p_object *plane, t_scene *scene)
{
	t_obj	*new;
	t_vec		size;

	new = plane_create();
	if (!new)
		return (FAILURE);
	size = vec_create(plane->width, plane->height, 1);
	new->gtfm = gtfm_set(plane->center, plane->direc, size);
	new->color = plane->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}

int	add_sphere(t_p_object *sphere, t_scene *scene)
{
	t_obj	*new;

	new = sphere_create();
	if (!new)
		return (FAILURE);
	new->gtfm = gtfm_set(sphere->center, vec_create(0, 0, 0),
			vec_create(sphere->radius, sphere->radius, sphere->radius));
	new->color = sphere->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}

int	add_cylinder(t_p_object *cylinder, t_scene *scene)
{
	t_obj	*new;

	new = cylinder_create();
	if (!new)
		return (FAILURE);
	new->gtfm = gtfm_set(cylinder->center,
						 cylinder->direc,
						 vec_create(cylinder->radius,
							cylinder->radius,
							cylinder->height)
						);
	new->color = cylinder->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}

int	add_cone(t_p_object *cone, t_scene *scene)
{
	t_obj	*new;

	new = cone_create();
	if (!new)
		return (FAILURE);
	new->gtfm = gtfm_set(cone->center, cone->direc,
			vec_create(cone->radius, cone->radius, cone->height));
	new->color = cone->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}
