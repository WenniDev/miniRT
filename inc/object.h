/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:40:28 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/11 14:16:32 by jopadova         ###   ########.fr       */
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
# include <stdbool.h>

# define SPHERE		0
# define PLANE		1
# define CYLINDER	2
# define CONE		3

typedef struct s_poi		t_poi;
typedef struct s_obj_lst	t_obj_lst;
typedef struct s_light_lst	t_light_lst;

/*********************OBJECT TYPES********************/

typedef enum e_type
{
	Integer,
	Float,
	String,
	Vector
}e_type;

//Struct to hold th plane data
typedef struct s_plane
{
	t_vec	center;
	t_vec	normal;
	t_vec 	size;
	t_vec	color;
	char 	*texture;
}t_plane;

//Struct t hold the sphere data
typedef struct s_sphere
{
	t_vec	center;
	double	radius;
	t_vec	color;
	char 	*texture;
}t_sphere;

//Struct to hold the cylinder data
typedef struct s_cylinder
{
	t_vec	center;
	t_vec	normal;
	double	radius;
	double	height;
	t_vec	color;
	char 	*texture;
}t_cylinder;

//Union to the object type
typedef union u_obj_type
{
	t_sphere	sphere;
	t_plane		plane;
}t_obj_type;

/*******************MATERIALS***********************/

typedef struct s_material
{
	t_vec		color;
	double		reflec;
	double		shiny;
	double		translucency;
	double		ior;
	int			max_ref_ray;
	int			ref_ray_count;
	t_texture	texture;
	bool		has_texture;
	t_vec		ambiant_color;
	double		ambiant_intensity;
	t_vec		(*colorfct)(t_obj_lst *, t_light_lst *,
			t_poi, t_ray, struct s_material);
}t_material;

/*******************OBJECT**************************/

//Chained list of objects
typedef struct s_obj_lst
{
	t_vec				color;
	t_material			material;
	bool				has_material;
	bool				(*intfct)(t_ray, t_poi *poi, t_obj_lst *obj);
	t_gtfm				gtfm;
	struct s_obj_lst	*next;
}t_obj_lst;

//Struct to hold the intersection point data
typedef struct s_poi
{
	t_vec		point;
	double		u;
	double		v;
	t_vec		normal;
	t_vec		color;
	t_obj_lst	*obj;
}t_poi;

//Struct to hold the intersection function of each objects
typedef struct s_intfct
{
	bool	(*fct)(t_ray, t_poi *poi, t_obj_lst *obj);
}t_intfct;

/********************FUNCTION DECLARATION***************/

t_obj_lst	*add_obj(t_obj_lst **obj_lst, t_obj_lst *new);
t_obj_lst	*obj_lst_at(t_obj_lst *obj_lst, int index);

void		assign_texture(t_material *material, t_texture texture);

bool		sphere_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj);
bool		plane_intersect(t_ray cam_ray, t_poi *poi, t_obj_lst *cur_obj);
bool		cylinder_intersect(t_ray cast_ray, t_poi *poi, t_obj_lst *obj_cur);
bool		cone_intersect(t_ray cast_ray, t_poi *poi, t_obj_lst *obj_cur);

t_obj_lst	*sphere_create(void);
t_obj_lst	*plane_create(void);
t_obj_lst	*cylinder_create(void);
t_obj_lst	*cone_create(void);

#endif //OBJECT_H
