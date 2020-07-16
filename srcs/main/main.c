/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:16:15 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 15:16:19 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*new_obj(t_obj new)
{
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->c = new.c;
	obj->v = new.v;
	obj->a = new.a;
	obj->r = new.r;
	obj->specular = new.specular;
	obj->color = new.color;
	obj->type = new.type;
	return (obj);
}

t_light	*new_light(t_light l)
{
	t_light	*light;

	light = (t_light*)malloc(sizeof(t_light));
	light->x = l.x;
	light->y = l.y;
	light->z = l.z;
	light->intens = l.intens;
	return (light);
}

void	lights_init(t_data *p)
{
	t_light	l1;
	t_light	l2;

	p->light = NULL;
	l1 = light_init(5, -1, 0, 0.7);
	ft_lstadd(&p->light, ft_lstnew(new_light(l1), sizeof(t_light)));
	l2 = light_init(-5, -1, 0, 0.7);
	ft_lstadd(&p->light, ft_lstnew(new_light(l2), sizeof(t_light)));
}

void	figur_init(t_data *p)
{
	t_obj	o1;
	t_obj	o2;
	t_obj	o3;
	t_obj	o4;
	t_obj	o5;

	p->figur = NULL;
	o5 = obj_init(new_vec(0, -2, 5), new_vec(0, 2, 0), 0.3, 0, 0, 0xF00000, CONE);
	ft_lstadd(&p->figur, ft_lstnew(new_obj(o5), sizeof(t_obj)));
	o1 = obj_init(new_vec(0, 1, 3), new_vec(0, 0, 0), 0, 1, 500, 0xFF0000, SPHERE);
	ft_lstadd(&p->figur, ft_lstnew(new_obj(o1), sizeof(t_obj)));
	o2 = obj_init(new_vec(2, 0, 4), new_vec(0, 0, 0), 0, 1, 500, 0x0000FF, SPHERE);
	ft_lstadd(&p->figur, ft_lstnew(new_obj(o2), sizeof(t_obj)));
	o3 = obj_init(new_vec(-2, 0, 4), new_vec(0, 0, 0), 0, 1, 10, 0x00FF00, SPHERE);
	ft_lstadd(&p->figur, ft_lstnew(new_obj(o3), sizeof(t_obj)));
	o4 = obj_init(new_vec(0, 5001, 0), new_vec(0, 0, 0), 0, 5000, 1000, 0xFFFF00, SPHERE);
	ft_lstadd(&p->figur, ft_lstnew(new_obj(o4), sizeof(t_obj)));
}

void 	print_vec(t_vector v)
{
	printf("x = %f\ny = %f\nz = %f\n", v.x, v.y, v.z);
}

void	test(t_data *p)
{
	figur_init(p);
	lights_init(p);
	render(p);
	drow(p);
}

int main()
{
	t_data	p;

	init(&p);
	test(&p);
	mlx_put_image_to_window(p.mlx.mlx, p.mlx.win, p.img.img, 0, 0);
	mlx_loop(p.mlx.mlx);
	return(0);
}
