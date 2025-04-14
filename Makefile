NAME := cube3d
CFLAGS :=  -Wall -Werror -Wextra -g3 -fsanitize=address 
CC := cc
LIBRARY_DIRS := -L./libft/compiled -L./MLX42/build -Iinclude
LIBRARIES   := -lgnl -lmlx42 -lglfw -lprintf -lft -lm
FRAMEWORKS  := -framework Cocoa -framework OpenGL -framework IOKit

EXEC_D = ./src/exec
CONTROL_D = ./src/exec/movement
INIT_D = ./src/exec/init
UTILS_D = ./src/utils
PARSING_D = ./src/parsing
PUTILS_D = ./src/parsing/utils
TEX_D = ./src/exec/texture
GAME_D = ./src/exec/game
RAY_D = ./src/exec/raycasting

SRC=			$(wildcard *.c) \
				  $(wildcard $(EXEC_D)/*.c) \
				  $(wildcard $(GAME_D)/*.c) \
				  $(wildcard $(RAY_D)/*.c) \
				  $(wildcard $(TEX_D)/*.c) \
				  $(wildcard $(CONTROL_D)/*.c) \
				  $(wildcard $(INIT_D)/*.c) \
				  $(wildcard $(PARSING_D)/*.c) \
				  $(wildcard $(PUTILS_D)/*.c) \
				  $(wildcard $(UTILS_D)/*.c)

OBJ = $(SRC:.c=.o)


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f
RESET		:= \033[0m

all:		clone_libft clone_mlx libmlx libft ${NAME}

libft:
	echo "Start LibFT"
	@$(MAKE) all -C ./libft
	echo "End LibFT"

REPO_URL_LIB := https://github.com/Saliinger/libft.git
CLONE_DIR_LIB := libft

REPO_URL_CODAM := https://github.com/codam-coding-college/MLX42.git
CLONE_DIR_CODAM := MLX42

# Clone target
clone_libft:
	@if [ ! -d "$(CLONE_DIR_LIB)" ]; then \
		echo "Cloning repository..."; \
		git clone $(REPO_URL_LIB) $(CLONE_DIR_LIB); \
	else \
		echo "Repository already cloned."; \
	fi

clone_mlx:
	@if [ ! -d "$(CLONE_DIR_CODAM)" ]; then \
		echo "Cloning repository..."; \
		git clone $(REPO_URL_CODAM) $(CLONE_DIR_CODAM); \
	else \
		echo "Repository already cloned."; \
	fi

libmlx:
			@cd MLX42 && cmake . -B build && make -C build -j4

${NAME}:	${OBJ}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${CFLAGS} ${OBJ} ${LIBRARY_DIRS} ${LIBRARIES} -o ${NAME}
			@echo "$(GREEN)$(NAME) created $(RESET)"

mac:		libft ${OBJ}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${CFLAGS} ${FRAMEWORKS} ${OBJ} ${LIBRARY_DIRS} ${LIBRARIES} -o ${NAME}
			@echo "$(GREEN)$(NAME) created $(RESET)"

clean:
			@$(MAKE) -C ./libft clean
			@ ${RM} $(OBJ)
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs"

fclean:		clean
			@$(MAKE) -C ./libft fclean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary"

re:			fclean all

.PHONY:		all clean fclean re clone_libft libft

# need to add the clone + Compilation of the mlx

