/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:42:14 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 02:15:54 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMALLOC_H
# define XMALLOC_H
# include "../cub3d.h"
# define MALLOC xmalloc
# define FREE xfree
# define FLUSH xflush
# define EXIT xexit

typedef	struct	s_link
{
	size_t				addr;
	struct s_link		*next;
}				t_link;
void			xflush(void);
void			*xmalloc(size_t bytes);
void			xfree(void *adr);
void			*xexit(int x);
void			ft_putstr(char *str);
void			*ftft();

static	t_link	*g_x;
void			*g_rtn;

#endif
