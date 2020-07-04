/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 10:20:34 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/04 10:20:45 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		color(int color, double i)
{
	int		red;
	int		green;
	int		blue;

	red = (color >> 16) & 0xFF;
	red = (int)(red * i);
	green = (color >> 8) & 0xFF;
	green = (int)(green * i);
	blue = (color & 0xFF);
	blue = (int)(blue * i);
	return ((red << 16) | (green << 8) | blue);
}
