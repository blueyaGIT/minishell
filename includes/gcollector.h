/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:30:12 by dalbano           #+#    #+#             */
/*   Updated: 2025/03/22 17:35:14 by dalbano          ###   ########.fr       */
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
t_gcmem				**get_head(void);
void				set_newhead(t_gcmem *new_head);
void				gc_freeall(void);
void				gc_add(void *address);
void				*gc_safe(void *address);

// UTILS
void				*gc_calloc(size_t count, size_t size);
char				*gc_itoa(int n);
char				**gc_split(char const *s, char c);
char				*gc_strdup(char *src);
char				*gc_strjoin(char const *s1, char const *s2);
char				*gc_substr(char const *s, unsigned int start, size_t len);
char				**gc_arr_cpy(char **arr);
void				gc_free_arr(char **arr);
	
#endif /* GCOLLECTOR_H */
