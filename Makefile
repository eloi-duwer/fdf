NAME = fdf

SRC = fdf.c \
	  get_infos.c \
	  draw_it.c \
	  destroy.c

LIBFT = libft/libft.a

all : $(NAME)

$(NAME) :
	cd ./libft && make
	gcc -o fdf $(SRC) $(LIBFT) -L/usr/local/lib -I/usr/local/include \
-lmlx -framework OpenGL -framework appkit -Wall -Wextra -Werror

clean :
	cd ./libft && make clean

fclean : clean
	rm -rf fdf

re : fclean all

