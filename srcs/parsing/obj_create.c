//
// Created by Joachim Padovani on 11/07/2023.
//

#include "parsing.h"
#include "miniRT.h"

int	obj_add_plane(t_plane *plane, t_scene *scene)
{
	t_obj_lst	*new;

	new = plane_create();
	if (!new)
		return (FAILURE);
	new->gtfm = gtfm_set(plane->center, plane->direc, plane->size);
	new->color = plane->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}

int	obj_add_sphere(t_sphere *sphere, t_scene *scene)
{
	t_obj_lst	*new;

	new = sphere_create();
	if (!new)
		return (FAILURE);
	new->gtfm = gtfm_set(sphere->center, vec_create(0, 0, 0), vec_create(sphere->radius, sphere->radius, sphere->radius));
	new->color = sphere->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}

int	obj_add_cylinder(t_cylinder *cylinder, t_scene *scene)
{
	t_obj_lst	*new;

	new = cylinder_create();
	if (!new)
		return (FAILURE);
	new->gtfm = gtfm_set(cylinder->center, cylinder->direc, vec_create(cylinder->radius, cylinder->radius, cylinder->height));
	new->color = cylinder->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}

int	obj_add_cone(t_cone *cone, t_scene *scene)
{
	t_obj_lst *new;

	new = cone_create();
	if (!new)
		return (FAILURE);
	new->gtfm = gtfm_set(cone->center, cone->direc, vec_create(cone->radius, cone->radius, cone->height));
	new->color = cone->color;
	add_obj(&scene->obj_lst, new);
	return (SUCCESS);
}
