CC	=	gcc

HEADER	=	includes

LIBFT	=	libft/libft.a

CCFLAGS	= -Wall -Wextra -Werror -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3 -I$(HEADER)

MLFLAGS	= -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME	= cube_3D

RESET	= \033[0m
BLACK	= \033[0;30m
RED	= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE 	= \033[0;37m

BOLDBLACK	= \033[1m\033[30m
BOLDRED		= \033[1m\033[31m
BOLDGREEN	= \033[1m\033[32m
BOLDYELLOW	= \033[1m\033[33m
BOLDBLUE	= \033[1m\033[34m
BOLDMAGENTA	= \033[1m\033[35m
BOLDCYAN	= \033[1m\033[36m
BOLDWHITE	= \033[1m\033[37m

SRCDIR	= src/

SRC	=  $(addprefix $(SRCDIR), $(SRC_LIST))

SRC_LIST =	main.c \
		minimap.c \
		minimap2.c \
		parsing.c \
		parsing2.c \
		parsing3.c \
		terminate.c \
		interact.c \
		game_loop.c \
		game_loop_utils.c \
		utils.c \
		syntax.c \
		intersect.c \
		init.c \
		render.c \
		raycast.c \
		cursor.c \

OBJ 	= $(SRC:%.c=%.o)

BOBJS	= $(BONUS:%.c=%.o)

LIBMLX = mlx/libmlx.a

#end of variable definitions

all: $(NAME) 

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
	 @$(CC) $(CCFLAGS) $(MLFLAGS) $(OBJ) $(LIBFT) -o $@
	 @printf "\n[COMPILED]\n"

$(LIBFT):
	@make -C libft

$(LIBMLX):
	@make -C mlx

%.o: %.c
	@printf "$(GREEN).$(RESET)"
	@$(CC) $(CCFLAGS) -Imlx -c $< -o $@ 

clean: 
	@rm -f $(OBJ)
	@printf "$(RED)[CLEAN]\n$(RESET)"

fclean: clean
	@#make -C libft clean
	@#make -C mlx clean
	@rm -f $(NAME)
	@printf "[FCLEAN]\n"

re: fclean all

test:
	echo "test $(RED)test"

.PHONY: test clean fclean all re
