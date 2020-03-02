/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:42:14 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/02 15:42:17 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef XMALLOC_H
#define XMALLOC_H

# define MALLOC xmalloc
# define FREE xfree
# define FLUSH xflush
# define EXIT xexit
# include <stdlib.h>

void	xflush(void);
void    *xmalloc(size_t bytes);
void    xfree(void  *adr);

#endif