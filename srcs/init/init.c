/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:54:36 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 15:54:41 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int camera_init(t_data *p)
{
	p->camera.canv_h = 2500;
	p->camera.canv_w = 2500;
	p->camera.canv_d = 2500;
	p->camera.x = 0;
	p->camera.y = 0;
	p->camera.z = 0;
	return(0);
}

int	init(t_data *p)
{
	camera_init(p);
	init_mlx(p);
	return(0);
}