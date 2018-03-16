/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_nbr_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 14:24:48 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/15 14:24:50 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_read_nbr_ants(t_file *file, int *ants, const unsigned int flags)
{
	int	a;

	a = 0;
	if (!ft_atoi(file, &a, ants) || file->txt[file->index + a] != '\n')
		return (flags & FLAG_ERROR ? ft_error(NBR_ANTS_BAD_INIT) : 0);
	file->index += a + 1;
	if (*ants <= 0)
		return (flags & FLAG_ERROR ? ft_error(NBR_ANTS_NULL_NEG) : 0);
	ft_putnbr(*ants);
	write(1, "\n", 1);
	return (1);
}
