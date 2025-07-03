CC=cc

CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g

NAME=fdf

SRCS_DIR=./srcs/

SRCS=$(SRCS_DIR)main.c\
	 $(SRCS_DIR)parser.c\
	 $(SRCS_DIR)renderer.c\
	 $(SRCS_DIR)terminator.c\
	 $(SRCS_DIR)painter.c

OBJS=$(SRCS:.c=.o)

RM=rm -f

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c -g $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft/
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a mlx/libmlx.a -Lmlx -lmlx -framework OpenGL -framework AppKit -g -o $(NAME)

clean:
	$(RM) $(OBJS)
	@make clean -C ./libft/

fclean: 
	$(RM) $(OBJS)
	$(RM) $(NAME)
	@make fclean -C ./libft/

re: fclean all

.PHONY: all clean fclean re $(NAME)

