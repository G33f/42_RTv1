/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figur_and_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:06:48 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/10 19:06:51 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light	light_init(double x, double y, double z, double intens)
{
	t_light	light;

	light.x = x;
	light.y = y;
	light.z = z;
	light.intens = intens;
	return (light);
}

t_orb	orb_init(int x, int y, int z, int r, int color, double spec)
{
	t_orb orb;

	orb.x = x;
	orb.y = y;
	orb.z = z;
	orb.r = r;
	orb.color = color;
	orb.specular = spec;
	return(orb);
}
