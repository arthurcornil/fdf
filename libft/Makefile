# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 21:49:47 by arcornil          #+#    #+#              #
#    Updated: 2025/04/18 17:01:32 by arcornil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc 

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRCS=ft_atoi.c\
	 ft_bzero.c\
	 ft_calloc.c\
	 ft_isalnum.c\
	 ft_isalpha.c\
	 ft_isascii.c\
	 ft_isdigit.c\
	 ft_isprint.c\
	 ft_memchr.c\
	 ft_memcmp.c\
	 ft_memcpy.c\
	 ft_memset.c\
	 ft_memmove.c\
	 ft_split.c\
	 ft_strdup.c\
	 ft_strlcat.c\
	 ft_strlcpy.c\
	 ft_strlen.c\
	 ft_strncmp.c\
	 ft_strnstr.c\
	 ft_strchr.c\
	 ft_strtrim.c\
	 ft_strrchr.c\
	 ft_substr.c\
	 ft_tolower.c\
	 ft_toupper.c\
	 ft_putchar_fd.c\
	 ft_putstr_fd.c\
	 ft_putendl_fd.c\
	 ft_putnbr_fd.c\
	 ft_strjoin.c\
	 ft_itoa.c\
	 ft_strmapi.c\
	 ft_striteri.c\
	 ft_malloc.c\
	 ft_realloc.c\
	 ft_free.c\
	 get_next_line.c\
	 get_next_line_utils.c

OBJS=${SRCS:.c=.o}

NAME=libft.a

BONUS=ft_lstnew_bonus.c\
	  ft_lstadd_front_bonus.c\
	  ft_lstsize_bonus.c\
	  ft_lstlast_bonus.c\
	  ft_lstadd_back_bonus.c\
	  ft_lstdelone_bonus.c\
	  ft_lstclear_bonus.c\
	  ft_lstiter_bonus.c\
	  ft_lstmap_bonus.c

B_OBJS= ${BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} $?

bonus: ${B_OBJS}
	ar rcs ${NAME} $?

clean:
	${RM} ${OBJS} ${B_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: fclean clean re bonus all
