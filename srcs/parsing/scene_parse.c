//
// Created by Joachim Padovani on 11/07/2023.
//

#include "parsing.h"
#include "miniRT.h"

int	parse_ambient(char *data, t_app *app, bool *amb_init)
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
	(void)app;
	return (ft_split_free(split), SUCCESS);
}

int	parse_camera(char *data, t_app *app, bool *cam_init)
{
	char	**split;
	int		i;
	t_cam	cam;

	i = 0;
	if (*cam_init == true)
		return (FAILURE);
	*cam_init = true;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 4)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[0], &cam.pos) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[1], &cam.look_at) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[2], &cam.up) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[3], &cam.size) == FAILURE)
		return (ft_split_free(split), FAILURE);
	scene_set_camera(&cam, &app->scene);
	return (ft_split_free(split), SUCCESS);
}

int	parse_light(char *data, t_app *app)
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
	(void)app;
	return (ft_split_free(split), SUCCESS);
}
