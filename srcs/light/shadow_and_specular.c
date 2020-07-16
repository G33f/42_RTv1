/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_and_specular.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:19:30 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/10 17:19:33 by wpoudre          ###   ########.fr       */
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

int	shadow_ray_tracing(t_3_vec q, t_obj *o, t_t *t)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;

	d = vec_diff(q.p, q.n);
	oc = vec_diff(q.n, o->c);
	disk = f_disk(d, oc, o);
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
	t_obj o;

	f = p->figur;
	while (f != NULL)
	{
		o = obj_clon(f);
		if (shadow_ray_tracing(r, &o, t))
			return (1);
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
