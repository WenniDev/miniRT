#include "gtfm.h"

#include <stdio.h>

void	init_gtfm(t_gtfm *gtfm)
{
	identity(&gtfm->tfm_mtx);
	identity(&gtfm->revtfm_mtx);
}

void	gtfm_set_transform(t_vec trans, t_vec rot, t_vec scale, t_gtfm *gtfm)
{
	//Define a matric for each component
	t_mtx4	trans_mtx;
	t_mtx4	rotx_mtx;
	t_mtx4	roty_mtx;
	t_mtx4 	rotz_mtx;
	t_mtx4	scale_mtx;

	//Set the matrix to identity
	identity(&trans_mtx);
	identity(&rotx_mtx);
	identity(&roty_mtx);
	identity(&rotz_mtx);
	identity(&scale_mtx);

	//Set values
	//Translation
	trans_mtx.val[0][3] = trans.x;
	trans_mtx.val[1][3] = trans.y;
	trans_mtx.val[2][3] = trans.z;

	rot = vec_mult(rot, M_PI / 180.0);
	//rotation
	rotx_mtx.val[1][1] = cos(rot.x);
	rotx_mtx.val[1][2] = -sin(rot.x);
	rotx_mtx.val[2][1] = sin(rot.x);
	rotx_mtx.val[2][2] = cos(rot.x);

	roty_mtx.val[0][0] = cos(rot.y);
	roty_mtx.val[0][2] = sin(rot.y);
	roty_mtx.val[2][0] = -sin(rot.y);
	roty_mtx.val[2][2] = cos(rot.y);

	rotz_mtx.val[0][0] = cos(rot.z);
	rotz_mtx.val[0][1] = -sin(rot.z);
	rotz_mtx.val[1][0] = sin(rot.z);
	rotz_mtx.val[1][1] = cos(rot.z);

	//Scaling
	scale_mtx.val[0][0] = scale.x;
	scale_mtx.val[1][1] = scale.y;
	scale_mtx.val[2][2] = scale.z;

	//Combine to the final foward matrix
	gtfm->tfm_mtx = mtx_mult(trans_mtx, scale_mtx);
	gtfm->tfm_mtx = mtx_mult(gtfm->tfm_mtx, rotx_mtx);
	gtfm->tfm_mtx = mtx_mult(gtfm->tfm_mtx, roty_mtx);
	gtfm->tfm_mtx = mtx_mult(gtfm->tfm_mtx, rotz_mtx);

	//Compute the revtfm
	gtfm->revtfm_mtx = gtfm->tfm_mtx;
	invert(&gtfm->revtfm_mtx);
}

t_vec	gtfm_vec_apply(t_gtfm gtfm, t_vec vec, int tfm)
{
	t_vec4	vec4;
	t_vec4	tmp_res;
	t_vec	res;

	vec4 = vec4_create(vec.x, vec.y, vec.z, 1.0);
	if (tfm == FWD)
	{
		tmp_res = mtx_vec_mult(vec4, gtfm.tfm_mtx);
	}
	else
	{
		tmp_res = mtx_vec_mult(vec4, gtfm.revtfm_mtx);
	}
	res = vec_create(tmp_res.x, tmp_res.y, tmp_res.z);
	return (res);
}

t_ray	gtfm_ray_apply(t_gtfm gtfm, t_ray ray, int tfm)
{
	t_ray	tfm_ray;

	tfm_ray.pa = gtfm_vec_apply(gtfm, ray.pa, tfm);
	tfm_ray.pb = gtfm_vec_apply(gtfm, ray.pb, tfm);
	tfm_ray.ab = vec_sub(tfm_ray.pb, tfm_ray.pa);
	return (tfm_ray);
}
