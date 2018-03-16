/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:43:41 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/23 19:43:42 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_first_start_and_end(t_lst **rooms)
{
	t_lst	*tlst;
	t_lst	*ttlst;

	tlst = *rooms;
	while (tlst && tlst->room->place != START_AND_END)
		tlst = tlst->next;
	if (tlst && tlst->room->place == START_AND_END && *rooms != tlst)
	{
		ttlst = *rooms;
		while (ttlst->next != tlst)
			ttlst = ttlst->next;
		ttlst->next = ttlst->next->next;
		tlst->next = *rooms;
		*rooms = tlst;
		return (1);
	}
	return (0);
}

void	ft_first_start(t_lst **rooms)
{
	t_lst	*tlst;
	t_lst	*ttlst;

	tlst = *rooms;
	while (tlst && tlst->room->place != START)
		tlst = tlst->next;
	if (tlst && tlst->room->place == START && *rooms != tlst)
	{
		ttlst = *rooms;
		while (ttlst->next != tlst)
			ttlst = ttlst->next;
		ttlst->next = ttlst->next->next;
		tlst->next = *rooms;
		*rooms = tlst;
	}
}

void	ft_first_end(t_lst **rooms)
{
	t_lst	*tlst;
	t_lst	*ttlst;

	tlst = *rooms;
	while (tlst && tlst->room->place != END)
		tlst = tlst->next;
	if (tlst && tlst->room->place == END && *rooms != tlst)
	{
		ttlst = *rooms;
		while (ttlst->next != tlst)
			ttlst = ttlst->next;
		ttlst->next = ttlst->next->next;
		tlst->next = (*rooms)->next;
		(*rooms)->next = tlst;
	}
}
