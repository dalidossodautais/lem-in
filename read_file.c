/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 19:34:39 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/16 19:34:40 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_read_file(t_file *file, const unsigned int flags)
{
	int		size_read;
	char	t[BUFF_SIZE];
	char	*tmp;

	while ((size_read = read(0, t, BUFF_SIZE)) > 0)
	{
		if (!(tmp = (char *)malloc((file->size + size_read) * sizeof(char))))
			return (flags & FLAG_ERROR ? ft_error(FAIL_ALLOC) : 0);
		file->index = -1;
		while (++file->index < file->size)
			tmp[file->index] = file->txt[file->index];
		free(file->txt);
		file->txt = tmp;
		file->index = -1;
		while (++file->index < size_read)
			file->txt[file->size++] = t[file->index];
	}
	file->index = 0;
	if (size_read < 0)
		return (flags & FLAG_ERROR ? ft_error(FAIL_READ) : 0);
	if (!file->txt)
		return (flags & FLAG_ERROR ? ft_error(EMPTY_FILE) : 0);
	return (1);
}
