/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:34:23 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/19 13:34:28 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "miniRT.h"

void	init_plane(t_f_parse *parse, t_p_object *obj)
{
	parse[0].value = &obj->center;
	parse[0].parse = parse_vec;
	parse[1].value = &obj->direc;
	parse[1].parse = parse_vec;
	parse[2].value = &obj->height;
	parse[2].parse = parse_double;
	parse[3].value = &obj->width;
	parse[3].parse = parse_double;
	parse[4].value = &obj->color;
	parse[4].parse = parse_color;
	parse[5].value = NULL;
	parse[5].parse = NULL;
}

void	init_sphere(t_f_parse *parse, t_p_object *obj)
{
	parse[0].value = &obj->center;
	parse[0].parse = parse_vec;
	parse[1].value = &obj->radius;
	parse[1].parse = parse_double;
	parse[2].value = &obj->color;
	parse[2].parse = parse_color;
	parse[3].value = NULL;
	parse[3].parse = NULL;
}

void	init_cylinder(t_f_parse *parse, t_p_object *obj)
{
	parse[0].value = &obj->center;
	parse[0].parse = parse_vec;
	parse[1].value = &obj->direc;
	parse[1].parse = parse_vec;
	parse[2].value = &obj->radius;
	parse[2].parse = parse_double;
	parse[3].value = &obj->height;
	parse[3].parse = parse_double;
	parse[4].value = &obj->color;
	parse[4].parse = parse_color;
	parse[5].value = NULL;
	parse[5].parse = NULL;
}

void	init_cone(t_f_parse *parse, t_p_object *obj)
{
	parse[0].value = &obj->center;
	parse[0].parse = parse_vec;
	parse[1].value = &obj->direc;
	parse[1].parse = parse_vec;
	parse[2].value = &obj->radius;
	parse[2].parse = parse_double;
	parse[3].value = &obj->height;
	parse[3].parse = parse_double;
	parse[4].value = &obj->color;
	parse[4].parse = parse_color;
	parse[5].value = NULL;
	parse[5].parse = NULL;
}
