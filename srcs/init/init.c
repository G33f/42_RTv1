/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:54:36 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/11 16:22:13 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_orb	*orb_clon(const t_list *o)
{
	t_orb *orb;

	orb = (t_orb*)malloc(sizeof(t_orb));
	orb->x = ((t_orb*)o->content)->x;
	orb->y = ((t_orb*)o->content)->y;
	orb->z = ((t_orb*)o->content)->z;
	orb->r = ((t_orb*)o->content)->r;
	orb->specular = ((t_orb*)o->content)->specular;
	orb->color = ((t_orb*)o->content)->color;
	return(orb);
}

/*int camera_init(t_data *p)
{
	p->camera.canv_h = 2500;
	p->camera.canv_w = 2500;
	p->camera.canv_d = 2500;
	p->camera.x = 0;
	p->camera.y = 0;
	p->camera.z = 0;
	return(0);
}*/

int	init(t_data *p)
{
	//camera_init(p);
	init_mlx(p);
	return(0);
}