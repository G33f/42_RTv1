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

t_orb	*new_orb(t_orb new)
{
	t_orb	*orb;

	orb = (t_orb*)malloc(sizeof(t_orb));
	orb->x = new.x;
	orb->y = new.y;
	orb->z = new.z;
	orb->r = new.r;
	orb->specular = new.specular;
	orb->color = new.color;
	orb->next = NULL;
	return (orb);
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
	t_orb	o1;
	t_orb	o2;
	t_orb	o3;
	t_orb	o4;

	p->figur = NULL;
	o1 = orb_init(0, 1, 3, 1, 0xFF0000, 500);
	ft_lstadd(&p->figur, ft_lstnew(new_orb(o1), sizeof(t_orb)));
	o2 = orb_init(2, 0, 4, 1, 0x0000FF, 500);
	ft_lstadd(&p->figur, ft_lstnew(new_orb(o2), sizeof(t_orb)));
	o3 = orb_init(-2, 0, 4, 1, 0x00FF00, 10);
	ft_lstadd(&p->figur, ft_lstnew(new_orb(o3), sizeof(t_orb)));
	o4 = orb_init(0, 5001, 0, 5000, 0xFFFF00, 1000);
	ft_lstadd(&p->figur, ft_lstnew(new_orb(o4), sizeof(t_orb)));
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
