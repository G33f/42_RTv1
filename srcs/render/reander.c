/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reander.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:06:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/13 16:28:55 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	min(double a, double b)
{
	if (a < b && a > 0)
		return (a);
	else if (b > 0)
		return (b);
	return (0.0);
}

int	ray_tracing(t_data *p, t_vector r, t_orb *o, double *t)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;

	d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z),
			new_vec(o->x, o->y, o->z));
	disk = pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
			(vec_dot(oc, oc) - pow(o->r, 2)));
	if (disk <= 0)
		return (0);
	t1 = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	t2 = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	t1 = min(t1, t2);
	if (t1 < *t && t1 > 0)
	{
		*t = t1;
		return (get_color(t1, p, d, o));
	}
	return (0);
}

void	render_cy(t_data *p, t_vector r, int j)
{
	t_list	*f;
	t_orb	*o;
	int		color;
	int		buf;
	double	t;

	f = p->figur;
	color = 0;
	t = 2147483647;
	while(f != NULL)
	{
		if (((t_orb*)f->content)->type == SPHERE)
		{
			o = orb_clon(f);
			buf = ray_tracing(p, new_vec(r.x, r.y, p->camera.canv_d), o, &t);
			if (buf > 0)
				color = buf;
			free(o);
		}
		//else
		//ft_putstr("not a sphere -_-\n");
		f = f->next;
	}
	p->canv.img_data[(int)r.z * p->camera.canv_w + j] = color;
}

int render(t_data *p)
{
	int i;
	int j;
	int x;
	int	y;

	y = p->camera.x - p->camera.canv_h / 2;
	i = 0;
	while(y < p->camera.y + p->camera.canv_h / 2)
	{
		j = 0;
		x = p->camera.x - p->camera.canv_w / 2;
		while(x < p->camera.x + p->camera.canv_w / 2)
		{
			render_cy(p, new_vec(x, y, i), j);
			x++;
			j++;
		}
		y++;
		i++;
	}
	return(0);
}
