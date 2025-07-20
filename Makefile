CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = fdf

SRCS_DIR = ./srcs/
SRCS = $(SRCS_DIR)main.c \
	   $(SRCS_DIR)parser.c \
	   $(SRCS_DIR)renderer.c \
	   $(SRCS_DIR)terminator.c \
	   $(SRCS_DIR)painter.c \
	   $(SRCS_DIR)parser_utils.c \
	   $(SRCS_DIR)fill_map.c \
	   $(SRCS_DIR)painter_utils.c \
	   $(SRCS_DIR)renderer_utils.c \
	   $(SRCS_DIR)projector.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

LIBFT = libft/libft.a
MLX = mlx/libmlx.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
else
	MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm -lz -lGL
endif

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft libft.a

$(MLX):
	$(MAKE) -C mlx

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
