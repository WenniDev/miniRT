/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:40:28 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 08:01:03 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ray.h"
# include "vector.h"
# include <stdbool.h>

typedef struct s_sreen
{
	t_vec	u;
	t_vec	v;
	t_vec	c;
}t_screen;

typedef struct s_cam
{
	t_vec		pos;
	t_vec		look_at;
	t_vec		up;
	t_vec		align;
	double		dist;
	double		size;
	double		ratio;
	t_screen	scr;
	bool		is_init;
}t_cam;

void	cam_init(t_cam *cam);
void	cam_geometry(t_cam *cam);
t_ray	cam_generate_ray(t_cam *cam, float x, float y);

#endif //CAMERA_H
