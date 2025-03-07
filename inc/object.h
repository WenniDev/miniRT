/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:23:12 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 13:33:49 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "gtfm.h"
# include "libft.h"
# include "matrix.h"
# include "texture.h"
# include "normal_map.h"
# include <stdbool.h>

# define SPHERE		0
# define PLANE		1
# define CYLINDER	2
# define CONE		3

typedef struct s_poi	t_poi;
typedef struct s_obj	t_obj;
typedef struct s_light	t_light;
typedef struct s_scene	t_scene;

/*********************OBJECT TYPES********************/

//Struct to hold 	objects data

typedef struct s_f_parse
{
	void	*value;
	int		(*parse)(char *data, void *value);
}t_f_parse;

typedef struct s_p_object
{
	t_vec	center;
	t_vec	direc;
	double	height;
	double	width;
	double	radius;
	t_vec	color;
}t_p_object;

/*******************MATERIALS***********************/

typedef struct s_material
{
	t_vec			color;
	double			reflec;
	double			shiny;
	double			trans;
	double			ior;
	int				max_ref_ray;
	int				ref_ray_count;
	t_texture		texture;
	bool			has_texture;
	t_vec			amb_color;
	double			amb_int;
	t_vec			(*colorfct)(t_scene, t_ray, t_poi);
	t_normal_map	nmap;
	bool			has_nmap;
}t_material;

/*******************OBJECT**************************/

//Chained list of objects
typedef struct s_obj
{
	t_vec			color;
	t_material		mat;
	bool			has_mat;
	bool			(*intfct)(t_ray, t_poi *poi, t_obj *obj);
	t_gtfm			gtfm;
	struct s_obj	*next;
}t_obj;

//Struct to hold the intersection point data
typedef struct s_poi
{
	t_vec		point;
	double		u;
	double		v;
	t_vec		normal;
	t_vec		color;
	double		intensity;
	t_obj		*obj;
}t_poi;

//Struct to hold the intersection function of each objects
typedef struct s_intfct
{
	bool	(*fct)(t_ray, t_poi *poi, t_obj *obj);
}t_intfct;

/********************FUNCTION DECLARATION***************/

t_obj	*add_obj(t_obj **obj_lst, t_obj *new);
t_obj	*get_last_obj(t_obj *obj_lst);

void	assign_texture(t_material *material, t_texture texture);

bool	sphere_intersect(t_ray cam_ray, t_poi *poi, t_obj *cur_obj);
bool	plane_intersect(t_ray cam_ray, t_poi *poi, t_obj *cur_obj);
bool	cylinder_intersect(t_ray cast_ray, t_poi *poi, t_obj *obj_cur);
bool	cone_intersect(t_ray cast_ray, t_poi *poi, t_obj *obj_cur);

t_obj	*sphere_create(void);
t_obj	*plane_create(void);
t_obj	*cylinder_create(void);
t_obj	*cone_create(void);

#endif
