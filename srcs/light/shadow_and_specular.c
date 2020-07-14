/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_and_specular.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:19:30 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/14 23:41:53 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light	light_clon(const t_list	*light)
{
	t_light l;

	l.x = ((t_light*)light->content)->x;
	l.y = ((t_light*)light->content)->y;
	l.z = ((t_light*)light->content)->z;
	l.intens = ((t_light*)light->content)->intens;
	return(l);
}

int	shadow_ray_tracing_pl(t_3_vec q, t_plane *o, t_t *t)
{
	t_vector l0;
	t_vector l;
	t_vector	p0l0;
	t_vector	p0;
	double		t1;
	double 		f;

	l = vec_diff(q.p, q.n);
	l0 = q.n;
	p0 = new_vec(o->x, o->y, o->z);
	f = vec_dot(o->n, l);
	if (f > 0.000001)
	{
		p0l0 = vec_diff(l0, p0);
		t1 = vec_dot(p0l0, o->n);
		if (t1 < t->t_max && t1 > t->t_min)
			return (1);
	}
	return (0);
}

int	shadow_ray_tracing(t_3_vec q, t_orb *o, t_t *t)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;

	d = vec_diff(q.p, q.n);
	oc = vec_diff(q.n, new_vec(o->x, o->y, o->z));
	disk = pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
			(vec_dot(oc, oc) - pow(o->r, 2)));
	if (disk <= 0)
		return (0);
	t1 = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	t2 = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	t1 = min(t1, t2, t);
	if (t1 < t->t_max && t1 > t->t_min)
		return (1);
	return (0);
}

int	shadow_render_cy(t_data *p, t_3_vec r, t_t *t)
{
	t_list *f;
	t_orb o;
	t_plane pl;

	f = p->figur;
	while (f != NULL)
	{
		if (((t_orb*)f->content)->type == SPHERE)
		{
			o = orb_clon(f);
			if (shadow_ray_tracing(r, &o, t))
				return (1);
		}
		if (((t_plane*)f->content)->type == PLANE)
		{
			pl = plane_clon(f);
			if (shadow_ray_tracing_pl(r, &pl, t))
				return (1);
		}
		f = f->next;
	}
	return (0);
}

double	spec(t_vector l, t_3_vec tre, double s, double i)
{
	t_vector	r;
	double		r_dot_v;

	if (s >= 0)
	{
		r = (vec_diff(vec_mult_cst(vec_mult_cst(tre.n, 2), vec_dot(tre.n, l)), l));
		r_dot_v = vec_dot(r, tre.v);
		if (r_dot_v > 0)
			return(i * pow(r_dot_v / (vec_length(r) * vec_length(tre.v)), s));
		else
			return(0.0);
	}
	else
		return(0.0);
}