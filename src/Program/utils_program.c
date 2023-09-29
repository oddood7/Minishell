/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:03:33 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/29 23:05:33 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*rv_static(int *rv)
{
	static int *rv_ptr;

	if (rv)
		rv_ptr = rv;
	return (rv_ptr);
}

