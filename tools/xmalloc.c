/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:42:00 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 23:09:46 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xmalloc.h"

void				*xmalloc(size_t bytes)
{
	t_link	*tmp;

	tmp = g_x;
	if (!(g_rtn = malloc(bytes)))
		return (NULL);
	if (!g_x)
	{
		if (!(g_x = malloc(sizeof(t_link))))
			return (xexit(1));
		g_x->addr = (size_t)g_rtn;
		g_x->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = malloc(sizeof(t_link))))
			return (xexit(1));
		tmp = tmp->next;
		tmp->addr = (size_t)g_rtn;
		tmp->next = NULL;
	}
	return (ftft());
}

int					xbrowse(void *adr)
{
	t_link	*tmp;
	t_link	*back;

	tmp = g_x;
	while (tmp && tmp->addr != (size_t)adr && (back = tmp))
		tmp = tmp->next;
	if (tmp && ((back->next = tmp->next) != (void*)42))
	{
		free((void *)tmp->addr);
		free(tmp);
		return (0);
	}
	return (1);
}

void				xfree(void *adr)
{
	t_link	*tmp;

	if (g_x && (tmp = g_x))
	{
		if (tmp->addr == (size_t)adr)
		{
			free((void *)tmp->addr);
			g_x = tmp->next;
			free(tmp);
		}
		else
		{
			if (xbrowse(adr))
			{
				ft_putstr("Non user allocated pointer was being freed!\n");
				free(adr);
				return ;
			}
		}
	}
	else
	{
		ft_putstr("Non user allocated pointer was being freed!\n");
		free(adr);
	}
}

void				xflush(void)
{
	t_link	*tmp;

	tmp = g_x;
	free(g_rtn);
	while (tmp)
	{
		free((void *)tmp->addr);
		g_x = tmp->next;
		free(tmp);
		tmp = g_x;
	}
}

void				leakcheck(void)
{
	t_link *tmp;
	size_t c;

	c = 0;
	tmp = g_x;
	while (tmp)
	{
		c++;
		tmp = tmp->next;
	}
}
