/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_app.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:07:33 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 13:45:51 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_app.h"
#include "miniRT.h"
#include "parsing.h"

void	app_loop(t_app *app);
void	app_event(t_app *app);

int	app_init(t_app *app)
{
	app->dsp_id = mlx_init();
	if (app->dsp_id == NULL)
	{
		return (FAILURE);
	}
	app->win_id = mlx_new_window(app->dsp_id, SIZE_X, SIZE_Y, "test");
	if (app->win_id == NULL)
	{
		return (FAILURE);
	}
	if (img_init(&app->img, app->dsp_id, SIZE_X, SIZE_Y) == FAILURE)
	{
		app_exit(app);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	test_texture(t_app *app, t_img *img)
{
	t_texture	img_txt;
	img_txt = img_txt_create();
	load_image(app, &img_txt, "./imgs/earth.xpm");
	img_txt.tfm = set_transform(vec_create(0.0, 0.0, 0.0), 0.0,
								vec_create(1.0, 1.0, 1.0));
	for (int x = 0; x < img->size_x; ++x)
	{
		for (int y = 0; y < img->size_y; ++y)
		{
			double	u = ((double) x / (((double) img->size_x) / 2.0)) - 1.0;
			double	v = ((double) y / (((double) img->size_y) / 2.0)) - 1.0;
			t_vec	color = img_txt.colorfct(img_txt, u, v);
			img_store_color(img, x, y, color);
		}
	}
}

int	app_execute(t_app *app)
{
	if (app_parse(app) == FAILURE)
	{
		return (FAILURE);
	}
	if (app_init(app) == FAILURE)
	{
		return (FAILURE);
	}
	//test_texture(app, &app->img);
	if (scene_render(app, &app->scene, &app->img) == FAILURE)
	{
		app_exit(app);
		return (FAILURE);
	}
	img_display(app->win_id, &app->img, 0, 0);
	app_event(app);
	app_loop(app);
	return (SUCCESS);
}

void	app_event(t_app *app)
{
	mlx_hook(app->win_id, 17, 0L, mlx_loop_end, app);
	mlx_hook(app->win_id, 2, 1l << 0, app_key_action, app);
}

void	app_loop(t_app *app)
{
	mlx_loop(app->dsp_id);
	app_exit(app);
}

int	app_exit(t_app *app)
{
	cleanup(app);
	img_destroy(&app->img);
	mlx_destroy_window(app->dsp_id, app->win_id);
	mlx_destroy_display(app->dsp_id);
	free(app->dsp_id);
	return (SUCCESS);
}

//DEBUG FCT
#include <stdio.h>
void	print_vector(t_vec vec)
{
	printf("x = %f\n", vec.x);
	printf("y = %f\n", vec.y);
	printf("z = %f\n", vec.z);
}
