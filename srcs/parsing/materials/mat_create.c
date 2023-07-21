/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:10 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/21 15:36:13 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "miniRT.h"

int	mat_normal_add(char *path, t_app *app)
{
	t_normal_map	new;

	new = normal_map_create();
	if (nmap_load_image(app, &new, path) == FAILURE)
		return (FAILURE);
	new.tfm = set_transform(vec_create(0.0, 0.0, 0.0), 0.0,
			vec_create(1.0, 1.0, 1.0));
	assign_nmap(&get_last_obj(app->scene.obj_lst)->mat, new);
	return (SUCCESS);
}

void	mat_simp_add(t_material *mat, t_scene *scene)
{
	t_material	new;

	new = simple_mat_const(mat->color, mat->reflec, mat->shiny);
	assign_mat(get_last_obj(scene->obj_lst), new);
}

void	mat_ref_add(t_material *mat, t_scene *scene)
{
	t_material	new;

	new = refractive_mat_const(mat->color, mat->reflec, mat->shiny,
			mat->trans);
	assign_mat(get_last_obj(scene->obj_lst), new);
}

int	mat_txt_add(char *path, t_app *app)
{
	t_texture	new;

	new = img_txt_create();
	if (load_image(app, &new, path) == FAILURE)
		return (FAILURE);
	new.tfm = set_transform(vec_create(0.0, 0.0, 0.0), 0.0,
			vec_create(1.0, 1.0, 1.0));
	if (get_last_obj(app->scene.obj_lst)->has_mat == false)
		return (FAILURE);
	assign_texture(&get_last_obj(app->scene.obj_lst)->mat, new);
	return (SUCCESS);
}
