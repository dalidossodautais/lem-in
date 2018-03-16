# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/04 14:24:43 by ddosso-d          #+#    #+#              #
#    Updated: 2017/05/04 14:24:45 by ddosso-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS	=	-Wall -Wextra
#-Werror
NAME	=	lem_in
OBJS	=	main.o read_flags.o read_file.o read_nbr_ants.o read_rooms.o \
			read_links.o find_paths.o print_paths.o usefull.o error.o first.o

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $^ -o $@

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
