CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = fdf

SRCS_DIR = ./srcs/
SRCS = $(SRCS_DIR)main.c\
	   $(SRCS_DIR)parser.c\
	   $(SRCS_DIR)renderer.c\
	   $(SRCS_DIR)terminator.c\
	   $(SRCS_DIR)painter.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

LIBFT = libft/libft.a
MLX = mlx/libmlx.a

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft libft.a

$(MLX):
	$(MAKE) -C mlx libmlx.a

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C libft
	$(MAKE) clean -C mlx

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) clean -C mlx

re: fclean all

.PHONY: all clean fclean re
