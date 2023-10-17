/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:34:56 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:53:10 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_garbage_lst	*new_element(void *pointer_to)
{
	t_garbage_lst	*new;

	new = malloc(sizeof(t_garbage_lst));
	if (!new)
		malloc_failure();
	if (!pointer_to)
		new->pointer = NULL;
	else
		new->pointer = pointer_to;
	new->next = NULL;
	return (new);
}

// Doit etre call quand nouvelle allocation
void	garbage_add(void *pointer)
{
	t_garbage		*garbage;
	t_garbage_lst	*new;

	garbage = get_garbage();
	new = new_element(pointer);
	if (garbage->head == NULL)
	{
		garbage->head = new;
		garbage->tail = new;
	}
	else
	{
		garbage->tail->next = new;
		garbage->tail = garbage->tail->next;
	}
	garbage->len_of_lst++;
}

// Doit etre call dans les secu ft_malloc
void	free_garbage(void)
{
	t_garbage		*garbage;
	t_garbage_lst	*save;
	int				i;

	i = -1;
	garbage = get_garbage();
	save = garbage->head;
	while (++i < garbage->len_of_lst)
	{
		if (save->pointer)
		{
			free(save->pointer);
			save->pointer = NULL;
		}
		garbage->head = save->next;
		free(save);
		save = garbage->head;
	}
}

// Doit etre call quand nouveau tableau 2D
void	add_d_t_garbage(void **double_array, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		garbage_add((void *)double_array[i]);
	garbage_add((void *)double_array);
}

t_garbage	*get_garbage(void)
{
	static t_garbage	instance;

	return (&instance);
}
