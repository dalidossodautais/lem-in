/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:21:06 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/05/04 16:21:08 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_rooms(t_lst *rooms)
{
	t_lst	*trooms;
	t_lst	*tlinks;

	while (rooms)
	{
		free(rooms->room->name);
		while (rooms->room->links)
		{
			tlinks = rooms->room->links->next;
			free(rooms->room->links);
			rooms->room->links = tlinks;
		}
		trooms = rooms->next;
		free(rooms->room);
		free(rooms);
		rooms = trooms;
	}
}

void	ft_putnbr(int n)
{
	char	c;

	if (n == INT_MIN)
	{
		write(1, STR_INT_MIN, 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

int		ft_strnequ(char *s1, char *s2, short size)
{
	while (size-- && s1[size] && s2[size] && s1[size] == s2[size])
		;
	return (size == -1);
}

int		ft_atoi(t_file *file, int *a, int *t)
{
	int	s;

	s = (file->index + *a < file->size &&
		file->txt[file->index + *a] == '-') ? -1 : 1;
	if (file->index + *a < file->size && (file->txt[file->index + *a] == '+' ||
		file->txt[file->index + *a] == '-'))
		++*a;
	if (file->txt[file->index + *a] < '0' || file->txt[file->index + *a] > '9')
		return (0);
	*t = 0;
	while (file->index + *a < file->size &&
		file->txt[file->index + *a] != ' ' &&
		file->txt[file->index + *a] != '\n')
	{
		if (file->txt[file->index + *a] < '0' ||
			file->txt[file->index + *a] > '9' ||
			*t * 10 + file->txt[file->index + *a] - '0' * s > INT_MAX ||
			*t * 10 + file->txt[file->index + *a] - '0' * s < INT_MIN)
			return (0);
		*t = *t * 10 + file->txt[file->index + *a] - '0';
		++*a;
	}
	*t *= s;
	return (1);
}
