/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:32:30 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/14 22:47:27 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	light_point(t_data *p, t_3_vec tre, t_light *light, double s)
{
	double		intens;
	t_vector	l;
	double		n_dot_l;
	t_t			t;
	int			check;

	p->camera.x = p->camera.x;
	t.t_min = 0.0000001;
	t.t_max = 1.0;
	intens = light->intens;
	l = new_vec(light->x, light->y, light->z);
	l = vec_diff(l, tre.p);
	check = shadow_render_cy(p, new_vec_3(l ,tre.p, new_vec(0 ,0 , 1)), &t);
	n_dot_l = vec_dot(tre.n, l);
	if (n_dot_l > 0 && check != 1)
		return((intens * n_dot_l / (vec_length(tre.n) * vec_length(l)) + spec(l, tre, s, intens)));
	else
		return(0.0);
}

double	light_direction(t_data *p, t_3_vec tre, double s)
{
	double		intens;
	double		n_dot_l;
	t_t			t;

	p->camera.x = p->camera.x;
	t.t_min = 0.00000001;
	t.t_max = 2147483647.0;
	intens = 0.0;
	n_dot_l = vec_dot(tre.n, p->l.l_d);
	if (n_dot_l > 0 && !shadow_render_cy(p, new_vec_3(p->l.l_d ,tre.p, new_vec(0 ,0 , 1)), &t))
		return((intens * n_dot_l / (vec_length(tre.n) * vec_length(p->l.l_d)) + spec(p->l.l_d, tre, s, intens)));
	else
		return(0.0);
}

double	light_intens(t_data *p ,t_3_vec tre, double s)
{
	double	i;
	t_list	*t;
	t_light	l;

	t = p->light;
	i = p->l.ambient;
	i += light_direction(p, tre, s);
	while(t != NULL)
	{
		l = light_clon(t);
		i += light_point(p, tre, &l, s);
		t = t->next;
	}
	return (i);
}

int get_color_pl(double t, t_data *q, t_vector d, t_plane *o)
{
	t_3_vec		tre;
	double		i;

	tre.p = vec_sum(new_vec(q->camera.x, q->camera.x, q->camera.x),
			vec_mult_cst(d, t));
	tre.n = vec_diff(tre.p, new_vec(o->x, o->y, o->z));
	tre.n = vec_divis_cst(tre.n, vec_length(tre.n));
	tre.v = rev_vec(d);
	i = light_intens(q, tre, 500);
	return(color(o->color, i));
}

int get_color(double t, t_data *q, t_vector d, t_orb *o)
{
	t_3_vec		tre;
	double		i;

	tre.p = vec_sum(new_vec(q->camera.x, q->camera.x, q->camera.x),
			vec_mult_cst(d, t));
	tre.n = vec_diff(tre.p, new_vec(o->x, o->y, o->z));
	tre.n = vec_divis_cst(tre.n, vec_length(tre.n));
	tre.v = rev_vec(d);
	i = light_intens(q, tre, o->specular);
	return(color(o->color, i));
}