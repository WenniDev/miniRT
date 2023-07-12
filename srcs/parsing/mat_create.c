//
// Created by Joachim Padovani on 12/07/2023.
//

#include "parsing.h"
#include "miniRT.h"

void mat_simp_add(t_material *mat, t_scene *scene)
{
	t_material	new;
	t_vec		color;

	color = vec_mult(mat->color, 1.0/255.0);
	new = simple_mat_const(color, mat->reflec, mat->shiny);
	assign_material(get_last_obj(scene->obj_lst), new);
}

void	mat_ref_add(t_material *mat, t_scene *scene)
{
	t_material	new;
	t_vec		color;

	color = vec_mult(mat->color, 1.0/255.0);
	new = refractive_mat_const(color, mat->reflec, mat->shiny, mat->translucency);
	assign_material(get_last_obj(scene->obj_lst), new);
}

int mat_txt_add(char *path, t_app *app)
{
	t_texture new;

	new = img_txt_create();
	if (load_image(app, &new, path) == FAILURE)
		return (FAILURE);
	new.tfm = set_transform(vec_create(0.0, 0.0, 0.0), 0.0,
											vec_create(1.0, 1.0, 1.0));
	if (get_last_obj(app->scene.obj_lst)->has_material == false)
		return (FAILURE);
	assign_texture(&get_last_obj(app->scene.obj_lst)->material, new);
	return (SUCCESS);
}
