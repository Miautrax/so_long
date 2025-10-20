# so_long Makefile

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

# Paths
SRCDIR  = src
LIBFTDIR= libft
MLXDIR  = MLX42
INCDIRS = -I$(SRCDIR) -I$(LIBFTDIR) -I$(MLXDIR)/include

# Sources
SRCS = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parse_map.c \
	$(SRCDIR)/validate_map.c \
	$(SRCDIR)/scan_tiles.c \
	$(SRCDIR)/validate_path.c \
	$(SRCDIR)/validate_path_utils.c \
	$(SRCDIR)/init_mlx.c \
	$(SRCDIR)/textures.c \
	$(SRCDIR)/textures_scale.c \
	$(SRCDIR)/render.c \
	$(SRCDIR)/controls.c \
	$(SRCDIR)/controls_player.c \
	$(SRCDIR)/controls_collect.c \
	$(SRCDIR)/free.c

OBJS = $(SRCS:.c=.o)

# Output
NAME = so_long

# Libs
LIBFT = $(LIBFTDIR)/libft.a
MLX   = $(MLXDIR)/build/libmlx42.a
# GLFW detection (pkg-config preferred)
PKGCFG := $(shell command -v pkg-config 2>/dev/null)
GLFW  := $(if $(PKGCFG),$(shell pkg-config --libs glfw3 2>/dev/null),)
ifeq ($(strip $(GLFW)),)
GLFW = -lglfw
endif
LDLIBS= $(LIBFT) $(MLX) $(GLFW) -ldl -lX11 -lXrandr -lXi -lpthread -lm
LDFLAGS = -L$(MLXDIR)/build -L$(LIBFTDIR)

# Tools detection
CMAKE := $(shell command -v cmake 2>/dev/null)

# Default target
all: $(NAME)

# Build MLX42 if not present
$(MLX):
ifndef CMAKE
	@echo "Error: cmake no encontrado. Instala cmake (y libglfw3-dev) para compilar MLX42." && exit 127
else
	@cmake -S $(MLXDIR) -B $(MLXDIR)/build -DMLX_BUILD_DOCS=OFF -DMLX_BUILD_EXAMPLES=OFF >/dev/null
	@cmake --build $(MLXDIR)/build -j >/dev/null
endif

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

# Compile objects
%.o: %.c
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

# Link
$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

# Run with a map
run: $(NAME)
	./$(NAME) maps/map_ok.ber

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(RM) $(NAME)
	@rm -rf $(MLXDIR)/build

re: fclean all

.PHONY: all clean fclean re run
