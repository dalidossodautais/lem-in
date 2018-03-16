/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 17:36:37 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/15 17:36:38 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_fill_or_not(t_lst *rooms, int a)
{
	while (rooms)
	{
		if (rooms->room->place == a)
			return (1);
		rooms = rooms->next;
	}
	return (0);
}

static void	ft_find_paths_next(t_lst *rooms)
{
	int		a;
	t_lst	*tlst;
	t_lst	*tlinks;

	a = 1;
	while (ft_fill_or_not(rooms->next->next, a))
	{
		tlst = rooms->next->next;
		while (tlst)
		{
			if (tlst->room->place == a)
			{
				tlinks = tlst->room->links;
				while (tlinks)
				{
					if (!tlinks->room->place)
						tlinks->room->place = a + 1;
					tlinks = tlinks->next;
				}
			}
			tlst = tlst->next;
		}
		++a;
	}
}

int			ft_find_paths(t_lst **rooms, const unsigned flags)
{
	t_lst	*tlinks;

	if (!ft_first_start_and_end(rooms))
	{
		ft_first_start(rooms);
		ft_first_end(rooms);
	}
	if ((*rooms)->room->place == START_AND_END)
		return (1);
	tlinks = (*rooms)->next->room->links;
	while (tlinks)
	{
		if (!tlinks->room->place)
			tlinks->room->place = 1;
		tlinks = tlinks->next;
	}
	ft_find_paths_next(*rooms);
	tlinks = (*rooms)->next->room->links;
	while (tlinks)
	{
		if (tlinks->room->place)
			return (1);
		tlinks = tlinks->next;
	}
	return (flags & FLAG_ERROR ? ft_error(ABSENT_PATH) : 0);
}
