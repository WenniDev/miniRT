//
// Created by Joachim Padovani on 11/07/2023.
//

#include "parsing.h"
#include "miniRT.h"

void	scene_set_camera(t_cam *cam, t_scene *scene)
{
	cam_init(&scene->cam);
	scene->cam.pos = cam->pos;
	scene->cam.look_at = cam->look_at;
	scene->cam.size = cam->size;
	scene->cam.up = cam->up;
	scene->cam.ratio = 16.0 / 9.0;
	cam_geometry(&scene->cam);
}

int	scene_add_light(t_light *light, t_scene *scene);