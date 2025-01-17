NAME = cube3d
FLAGS = -Wall -Werror -Wextra
CC = gcc
INCLUDE = 


SRC = main.c

OBJ = $(SRC%.c=.o)


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f
RESET		:= \033[0m

all:		clone_libft libft ${NAME}

libft:
	echo "Start LibFT"
	@$(MAKE) all -C ./libft
	echo "End LibFT"

REPO_URL_LIB := https://github.com/Saliinger/libft.git
CLONE_DIR_LIB := libft

# Clone target
clone_libft:
	@if [ ! -d "$(CLONE_DIR_LIB)" ]; then \
		echo "Cloning repository..."; \
		git clone $(REPO_URL_LIB) $(CLONE_DIR_LIB); \
	else \
		echo "Repository already cloned."; \
	fi

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} $(LIBS)
			@echo "$(GREEN)$(NAME) created $(RESET)"

clean:
			@$(MAKE) -C ./libft clean
			@ ${RM} $(OBJS)
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs"

fclean:		clean
			@$(MAKE) -C ./libft fclean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary"

re:			fclean all

.PHONY:		all clean fclean re clone_libft libft

