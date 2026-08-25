#
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
#

NAME = raytracer

BUILD_DIR = build

CMAKE = cmake


all: $(NAME)

$(NAME):
	$(CMAKE) -S . -B $(BUILD_DIR)
	$(CMAKE) --build $(BUILD_DIR)

clean:
	@if [ -d $(BUILD_DIR) ]; then \
		$(CMAKE) --build $(BUILD_DIR) --target clean; \
	fi
	@rm -f CMakeCache.txt cmake_install.cmake
	@rm -rf CMakeFiles

fclean: clean
	rm -rf $(BUILD_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
