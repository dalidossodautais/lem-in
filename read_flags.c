/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 14:24:08 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/15 14:24:12 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_read_some_flags(unsigned *flags, const short c)
{
	if (c == 'e')
		*flags += *flags | FLAG_ERROR;
	else if (*flags & FLAG_ERROR)
		ft_error(FLAG_UNKNOWN);
}

int			ft_read_flags(unsigned *flags, const int ac, const char **av)
{
	short	a;
	short	b;

	a = 0;
	while (++a < ac)
	{
		b = 0;
		while (av[a][b])
		{
			if (av[a][b] == '-')
			{
				if (!av[a][b + 1] || av[a][b + 1] == ' ' ||
					av[a][b + 1] == '\t' || av[a][b + 1] == '\n')
					return (*flags & FLAG_ERROR ? ft_error(FLAG_BAD_INIT) : 0);
				while (av[a][++b] && av[a][b] != ' ' && av[a][b] != '\t' &&
					av[a][b] != '\n')
					ft_read_some_flags(flags, av[a][b]);
			}
			else if (av[a][b] == ' ' || av[a][b] == '\t' || av[a][b] == '\n')
				++b;
			else
				return (*flags & FLAG_ERROR ? ft_error(FLAG_BAD_INIT) : 0);
		}
	}
	return (1);
}
