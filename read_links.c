/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 13:37:02 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/15 13:37:03 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_pass_commentary(t_file *file, const unsigned flags)
{
	int	a;

	a = 0;
	while (file->index + a < file->size && file->txt[file->index + a] == '#' &&
		!(file->index + a + 8 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##start\n", 8)) &&
		!(file->index + a + 6 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##end\n", 6)))
		while (file->index + ++a < file->size &&
			file->txt[file->index + a - 1] != '\n')
			;
	if (file->index + a + 8 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##start\n", 8))
	{
		write(1, file->txt + file->index, a + 8);
		return (flags & FLAG_ERROR ? ft_error(START_BAD_FOLLOW) : 0);
	}
	if (file->index + a + 6 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##end\n", 6))
	{
		write(1, file->txt + file->index, a + 6);
		return (flags & FLAG_ERROR ? ft_error(END_BAD_FOLLOW) : 0);
	}
	write(1, file->txt + file->index, a);
	return (!!(file->index += a));
}

static int	ft_fill_link(t_file *file, t_lst **t1, t_lst **t2)
{
	int	a;

	a = 0;
	while (file->index + a < file->size && file->txt[file->index + a] != '\n'
		&& file->txt[file->index + a] != ' ' &&
		file->txt[file->index + a] != '-')
		++a;
	if (file->index + a == file->size || file->txt[file->index + a] == '\n' ||
		file->txt[file->index + a] == ' ')
		return (0);
	while (*t1 && (a != (*t1)->room->sizename ||
		!ft_strnequ((*t1)->room->name, file->txt + file->index, a)))
		*t1 = (*t1)->next;
	file->index += a + 1;
	a = 0;
	while (file->txt[file->index + a] != '\n')
		if (file->index + a == file->size || file->txt[file->index + a] == ' '
			|| file->txt[file->index + a++] == '-')
			return (0);
	while (*t2 && (a != (*t2)->room->sizename ||
		!ft_strnequ((*t2)->room->name, file->txt + file->index, a)))
		*t2 = (*t2)->next;
	return (!!(file->index += a + 1));
}

static int	ft_check_and_print_link(t_lst **tlst, t_lst *t1, t_lst *t2,
	const unsigned flags)
{
	if (!t1 || !t2)
		return (flags & FLAG_ERROR ? ft_error(IMPOSSIBLE_LINK) : 0);
	if (t1 == t2)
		return (flags & FLAG_ERROR ? ft_error(ROOM_TO_ROOM) : 0);
	*tlst = t1->room->links;
	while (*tlst)
	{
		if ((*tlst)->room == t2->room)
			return (flags & FLAG_ERROR ? ft_error(EXISTING_LINK) : 0);
		*tlst = (*tlst)->next;
	}
	write(1, t1->room->name, t1->room->sizename);
	write(1, "-", 1);
	write(1, t2->room->name, t2->room->sizename);
	write(1, "\n", 1);
	return (1);
}

int			ft_read_links(t_file *file, t_lst **rooms, const unsigned flags)
{
	t_lst	*tlst;
	t_lst	*t1;
	t_lst	*t2;

	t1 = *rooms;
	t2 = *rooms;
	while (ft_pass_commentary(file, flags))
	{
		if (!ft_fill_link(file, &t1, &t2))
			return (1);
		if (!ft_check_and_print_link(&tlst, t1, t2, flags))
			return (0);
		tlst = (t_lst *)malloc(sizeof(t_lst));
		tlst->room = t2->room;
		tlst->next = t1->room->links;
		t1->room->links = tlst;
		tlst = (t_lst *)malloc(sizeof(t_lst));
		tlst->room = t1->room;
		tlst->next = t2->room->links;
		t2->room->links = tlst;
		t1 = *rooms;
		t2 = *rooms;
	}
	return (0);
}
