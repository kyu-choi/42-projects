# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#              #
#    Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## @file Makefile
## @brief Build rules for miniRT and miniRT_bonus binaries.
## @details Keeps mandatory and bonus sources fully isolated.
## @details Selects MiniLibX per OS (Darwin/Linux) and supports MLX_DIR.
##
## Build flow (dependency order):
##   1) $(LIBFT_LIB) - builds libft.a via libft/Makefile
##   2) $(MLX_LIB) - builds MiniLibX per UNAME_S
##   3) $(OBJ_DIR_MAND)/%.o - compiles each mandatory .c -> .o
##   4) $(NAME) - links OBJS_MAND + LIBFT + MLX -> miniRT
##
## Target dependency chain (all):
##   all -> $(NAME) -> [$(LIBFT_LIB), $(MLX_LIB), $(OBJS_MAND)]
##
## Clean targets:
##   clean   - removes obj/, libft objs, MLX objs
##   fclean  - clean + $(NAME) $(BONUS_NAME) + libft.a
##   re      - fclean then all
##
## Override: make MLX_DIR=<path> to use custom MiniLibX

NAME			= miniRT
BONUS_NAME		= miniRT_bonus
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP
RM				= rm -f

SRC_DIR_MAND		= src/mandatory
SRC_DIR_BONUS		= src/bonus
OBJ_DIR_MAND		= obj/mandatory
OBJ_DIR_BONUS		= obj/bonus
INCLUDE_DIR_MAND	= includes/mandatory
INCLUDE_DIR_BONUS	= includes/bonus
LIBFT_DIR		= libft
LIBFT_LIB		= $(LIBFT_DIR)/libft.a

UNAME_S			:= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  ifneq (,$(wildcard minilibx-linux/Makefile))
    DEFAULT_MLX_DIR = minilibx-linux
  else ifneq (,$(wildcard minilibx/Makefile))
    DEFAULT_MLX_DIR = minilibx
  else
    $(error No usable Linux MiniLibX found. Use make MLX_DIR=<path>)
  endif
else ifeq ($(UNAME_S),Darwin)
  ifneq (,$(wildcard minilibx_opengl_20191021/Makefile))
    DEFAULT_MLX_DIR = minilibx_opengl_20191021
  else ifneq (,$(wildcard minilibx_macos/Makefile))
    DEFAULT_MLX_DIR = minilibx_macos
  else ifneq (,$(wildcard minilibx/Makefile))
    DEFAULT_MLX_DIR = minilibx
  else ifneq (,$(wildcard minilibx_mms_20200219/Makefile))
    DEFAULT_MLX_DIR = minilibx_mms_20200219
  else
    $(error No usable MiniLibX found. Install MLX in miniRT/)
  endif
else
  $(error Unsupported OS: $(UNAME_S))
endif

MLX_DIR			?= $(DEFAULT_MLX_DIR)
ifeq ($(UNAME_S),Darwin)
ifneq (,$(findstring minilibx_mms_20200219,$(MLX_DIR)))
ifneq (,$(wildcard minilibx_opengl_20191021/Makefile))
$(warning mms failed on this Swift; fallback to opengl_20191021)
override MLX_DIR := minilibx_opengl_20191021
endif
endif
endif
ifeq ($(UNAME_S),Linux)
  MLX_LIB_NAME = libmlx.a
  MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S),Darwin)
ifneq (,$(findstring minilibx_mms_20200219,$(MLX_DIR)))
  MLX_LIB_NAME = libmlx.dylib
  MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework Metal -framework MetalKit \
				-framework AppKit -lz -Wl,-rpath,$(abspath $(MLX_DIR))
else
  MLX_LIB_NAME = libmlx.a
  MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
endif
endif
MLX_LIB			= $(MLX_DIR)/$(MLX_LIB_NAME)

SRCS_MAND_COMMON = main.c \
				  init/init.c \
				  init/hooks.c \
				  init/control_camera.c \
				  init/control_scene.c \
				  mlx/pixel.c \
				  mlx/render.c \
				  mlx/debug_axis.c \
				  math/vec3_a.c \
				  math/vec3_b.c \
				  math/color.c \
				  math/camera.c \
				  math/rotate.c \
				  parse/read_file.c \
				  parse/parse.c \
				  parse/parse_line.c \
				  parse/scan.c \
				  parse/parse_num.c \
				  parse/parse_vec.c \
				  parse/parse_env.c \
				  parse/parse_obj.c \
				  scene/object.c \
				  ray/intersect_scene.c \
				  ray/intersect_sphere.c \
				  ray/intersect_plane.c \
				  ray/intersect_cylinder_side.c \
				  ray/intersect_cylinder.c \
				  ray/shadow.c \
				  ray/shade.c \
				  ray/trace.c \
				  utils/error.c

SRCS_BONUS_COMMON = main_bonus.c \
				   init/init_bonus.c \
				   init/hooks_bonus.c \
				   init/control_camera_bonus.c \
				   init/control_scene_bonus.c \
				   mlx/pixel_bonus.c \
				   mlx/render_bonus.c \
				   mlx/debug_axis_bonus.c \
				   math/vec3_a_bonus.c \
				   math/vec3_b_bonus.c \
				   math/color_bonus.c \
				   math/camera_bonus.c \
				   math/rotate_bonus.c \
				   parse/read_file_bonus.c \
				   parse/parse_bonus.c \
				   parse/parse_line_bonus.c \
				   parse/scan_bonus.c \
				   parse/parse_num_bonus.c \
				   parse/parse_vec_bonus.c \
				   parse/parse_env_bonus.c \
				   parse/parse_obj_bonus.c \
				   parse/parse_cone_bonus.c \
				   parse/parse_hyperboloid_bonus.c \
				   parse/parse_paraboloid_bonus.c \
				   parse/parse_obj_opts_bonus.c \
				   scene/object_bonus.c \
				   scene/light_list_bonus.c \
				   ray/intersect_scene_bonus.c \
				   ray/intersect_sphere_bonus.c \
				   ray/intersect_plane_bonus.c \
				   ray/intersect_cylinder_side_bonus.c \
				   ray/intersect_cylinder_bonus.c \
				   ray/intersect_cone_bonus.c \
				   ray/intersect_hyperboloid_bonus.c \
				   ray/intersect_paraboloid_bonus.c \
				   ray/shadow_bonus.c \
				   ray/pattern_bonus.c \
				   ray/material_bonus.c \
				   ray/shade_bonus.c \
				   ray/trace_bonus.c \
				   utils/error_bonus.c

ifeq ($(UNAME_S),Linux)
  SRCS_MAND_OS = init/cleanup_linux.c init/resize_linux.c
  SRCS_BONUS_OS = init/cleanup_linux_bonus.c init/resize_linux_bonus.c
else
  SRCS_MAND_OS = init/cleanup_macos.c init/resize_macos.c
  SRCS_BONUS_OS = init/cleanup_macos_bonus.c init/resize_macos_bonus.c
endif

SRCS_MAND = $(SRCS_MAND_COMMON) $(SRCS_MAND_OS)
SRCS_BONUS = $(SRCS_BONUS_COMMON) $(SRCS_BONUS_OS)

OBJS_MAND = $(addprefix $(OBJ_DIR_MAND)/, $(SRCS_MAND:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR_BONUS)/, $(SRCS_BONUS:.c=.o))
DEPS_MAND = $(OBJS_MAND:.o=.d)
DEPS_BONUS = $(OBJS_BONUS:.o=.d)

## @target all
## @brief Default target. Depends on $(NAME).
all: $(NAME)

## @target $(NAME)
## @brief Links OBJS_MAND + libft + MLX -> miniRT. Depends on libs + objs.
$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS_MAND)
	$(CC) $(CFLAGS) $(OBJS_MAND) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

## @target bonus
## @brief Builds bonus binary miniRT_bonus.
bonus: $(BONUS_NAME)

## @target $(BONUS_NAME)
## @brief Links bonus object set with libft and MiniLibX.
$(BONUS_NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(BONUS_NAME)

## @target $(OBJ_DIR_MAND)/%.o
## @brief Pattern rule: compiles mandatory .c with -I includes. Dep on %.d.
$(OBJ_DIR_MAND)/%.o: $(SRC_DIR_MAND)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR_MAND) -I$(LIBFT_DIR) -I$(MLX_DIR) \
		-c $< -o $@

## @target $(OBJ_DIR_BONUS)/%.o
## @brief Compiles bonus source files with bonus headers.
$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR_BONUS) -I$(LIBFT_DIR) -I$(MLX_DIR) \
		-c $< -o $@

## @target $(LIBFT_LIB)
## @brief Builds libft.a. No dep on other miniRT targets.
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

## @target $(MLX_LIB)
## @brief Builds MiniLibX (libmlx.a or .dylib). -j1 for parallel safety.
$(MLX_LIB):
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		$(MAKE) -j1 -C $(MLX_DIR); \
	else \
		echo "Error: MiniLibX not found in $(MLX_DIR)"; \
		exit 1; \
	fi

## @target clean
## @brief Removes obj/, then libft clean, then MLX clean. Keeps binaries.
clean:
	$(RM) -r obj
	@$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		$(MAKE) -j1 -C $(MLX_DIR) clean 2>/dev/null || true; \
	fi

## @target fclean
## @brief Depends on clean. Removes $(NAME), $(BONUS_NAME), libft.a.
fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean 2>/dev/null || true

## @target re
## @brief Full rebuild: fclean then all.
re: fclean all

-include $(DEPS_MAND)
-include $(DEPS_BONUS)

.PHONY: all bonus clean fclean re
