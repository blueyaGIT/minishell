/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:30:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/19 13:45:46 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCOLLECTOR_H
# define GCOLLECTOR_H

# include "minishell.h"

typedef struct s_gcmem
{
	void			*address;
	struct s_gcmem	*next;
}					t_gcmem;

void				*gc_malloc(size_t size);
void				gc_free(void *address);
// t_gcmem				**gc_get(void);
// void				gc_set(t_gcmem *new_head);
// void				gc_add(void *address);
// void				gc_freeall(void);
// void				*gc_safe(void *address);

#endif
