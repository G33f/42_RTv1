/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 18:21:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 18:21:11 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error_log(int cod)
{
	if (cod == 1)
		ft_putstr("Low memory((\n");
	else if (cod == 2)
		ft_putstr("Incorect SCEN");
	exit(0);
}

void	usage(int cod)
{
	if (cod == 1)
		ft_putstr("Use ./RTv1 [any_scen.rce]\n");
	else if (cod == 2)
		ft_putstr("Use corect ./RTv1 [any_scen.rce]\n");
	exit(0);
}

void	error(int cod)
{
	if (cod == -10)
		usage(1);
	else if (cod == -11)
		usage(2);
	else if (cod == -12)
		error_log(1);
	else if (cod == -13)
		error_log(2);
}
