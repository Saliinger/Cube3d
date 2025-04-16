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

SRC = \
	main.c \
	$(EXEC_D)/exec.c \
	$(GAME_D)/game_loop.c \
	$(GAME_D)/start_game.c \
	$(INIT_D)/init.c \
	$(INIT_D)/init_mlx.c \
	$(INIT_D)/init_player.c \
	$(INIT_D)/init_ray.c \
	$(CONTROL_D)/is_wall.c \
	$(CONTROL_D)/move.c \
	$(RAY_D)/inter_check.c \
	$(RAY_D)/normalize_angle.c \
	$(RAY_D)/raycasting.c \
	$(RAY_D)/unit_circle.c \
	$(RAY_D)/wall_hit.c \
	$(TEX_D)/draw_floor_ceilling.c \
	$(TEX_D)/draw_wall.c \
	$(TEX_D)/get_texture.c \
	$(TEX_D)/render.c \
	$(PARSING_D)/alloc_map_size.c \
	$(PARSING_D)/get_position_player.c \
	$(PARSING_D)/init_data.c \
	$(PARSING_D)/init_keys.c \
	$(PARSING_D)/insert_key.c \
	$(PARSING_D)/parsed_color.c \
	$(PARSING_D)/parser.c \
	$(PARSING_D)/parsing.c \
	$(PARSING_D)/process_line.c \
	$(PUTILS_D)/free_data.c \
	$(PUTILS_D)/free_split.c \
	$(PUTILS_D)/ft_isspace.c \
	$(PUTILS_D)/ft_split_count.c \
	$(PUTILS_D)/ft_str_is_numeric.c \
	$(PUTILS_D)/is_empty_line.c \
	$(PUTILS_D)/trim.c \
	$(PARSING_D)/valid_extension.c \
	$(PARSING_D)/valid_map.c \
	$(PARSING_D)/verif_data.c \
	$(PARSING_D)/wall_map.c \
	$(UTILS_D)/ft_error.c \
	$(UTILS_D)/ft_exit.c \
	$(UTILS_D)/ft_free.c \
	$(UTILS_D)/map_size.c \
	$(UTILS_D)/rgb_to_hex.c

OBJ = $(SRC:.c=.o)


CLR_RMV     := \033[0m
RED         := \033[1;31m
GREEN       := \033[1;32m
YELLOW      := \033[1;33m
BLUE        := \033[1;34m
CYAN        := \033[1;36m
RM          := rm -f
RESET       := \033[0m

all:        clone_libft clone_mlx libmlx libft ${NAME}

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

${NAME}:    ${OBJ}
		@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
		${CC} ${CFLAGS} ${OBJ} ${LIBRARY_DIRS} ${LIBRARIES} -o ${NAME}
		@echo "$(GREEN)$(NAME) created $(RESET)"

mac:        libft ${OBJ}
		@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
		${CC} ${CFLAGS} ${FRAMEWORKS} ${OBJ} ${LIBRARY_DIRS} ${LIBRARIES} -o ${NAME}
		@echo "$(GREEN)$(NAME) created $(RESET)"

clean:
	@$(MAKE) -C ./libft clean
	@ ${RM} $(OBJ)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs"

fclean:     clean
	@$(MAKE) -C ./libft fclean
	@ ${RM} ${NAME}
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary"

re:         fclean all

.PHONY:     all clean fclean re clone_libft libft
