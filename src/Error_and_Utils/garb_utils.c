/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:51:17 by asalic            #+#    #+#             */
/*   Updated: 2023/10/17 16:57:00 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		malloc_failure();
	garbage_add(ptr);
	return (ptr);
}

// Doit etre call en debut de programme
t_garbage	*start_garbage(void)
{
	t_garbage	*garbage;

	garbage = get_garbage();
	garbage->head = NULL;
	garbage->tail = NULL;
	garbage->len_of_lst = 0;
	return (garbage);
}

void	malloc_failure(void)
{
	perror("MALLOC FAILURE\n");
	ft_exit(NULL, NULL);
}
