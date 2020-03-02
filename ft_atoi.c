/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:42:27 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/02 15:42:29 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_atoi(const char *ptr)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ptr[i] && ptr[i] >= '0' && ptr[i] <= '9')
	{
		res = res * 10 + (ptr[i] - '0');
		i++;
	}
	return (res * sign);
}

long long	ft_atoi2(const char *ptr)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ptr[i] && ptr[i] >= '0' && ptr[i] <= '9')
	{
		res = res * 10 + (ptr[i] - '0');
		i++;
	}
	return (res * sign);
}
