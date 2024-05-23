##
## EPITECH PROJECT, 2023
## corewar
## File description:
## The main Makefile of our project
##

NAME		=	corewar

CC		=	gcc
DEBUG_MODE	=

BUILDDIR 	=	./build
SRCDIR		=	./src

SRCS		+=	main.c
SRCS		+=	instructions/add.c
SRCS		+=	instructions/aff.c
SRCS		+=	instructions/and.c
SRCS		+=	instructions/fork.c
SRCS		+=	instructions/ld.c
SRCS		+=	instructions/ldi.c
SRCS		+=	instructions/lfork.c
SRCS		+=	instructions/live.c
SRCS		+=	instructions/lld.c
SRCS		+=	instructions/lldi.c
SRCS		+=	instructions/or.c
SRCS		+=	instructions/st.c
SRCS		+=	instructions/sti.c
SRCS		+=	instructions/sub.c
SRCS		+=	instructions/xor.c
SRCS		+=	instructions/zjmp.c
SRCS		+=	arena.c
SRCS		+=	champion.c
SRCS		+=	coding_byte.c
SRCS		+=	corewar.c
SRCS		+=	header.c
SRCS		+=	instructions.c
SRCS		+=	op.c
SRCS		+=	parsing.c
SRCS		+=	read_file.c
SRCS		+=	state.c
SRCS		+=	update.c

OBJS     	=	$(addprefix $(BUILDDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS		=	-Werror -Wextra -I./include/
DEBUGFLAGS	=	-g3
OPTIMIZEFLAGS	=	-O3
VALGRINDFLAGS	=	--leak-check=full --show-leak-kinds=all --track-origins=yes
OUTPUT		=	valgrind.log

LDFLAGS 	=	-L./lib/ -lmymemory -lmylist -lmy

TEST_ARGS	=	-d 10 -n 1 champions/42.cor -n 10 champions/42.cor

.PHONY: all libs create-build debug valgrind clean fclean re \
		unit_tests tests_run doc

all: create-build libs $(BUILDDIR) $(NAME)
	@echo -e "\033[1;33m$(NAME) compiled.\033[0m"

libs:
	@make --no-print-directory -C ./lib/my/ $(DEBUG_MODE)
	@make --no-print-directory -C ./lib/mylist/ $(DEBUG_MODE)
	@make --no-print-directory -C ./lib/mymemory/ $(DEBUG_MODE)
	@echo -e "\033[1;33mLibs made.\033[0m"

create-build:
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(OPTIMIZEFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/instructions/%.c
	$(CC) $(CFLAGS) $(OPTIMIZEFLAGS) $(LDFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUGFLAGS)
debug: OPTIMIZEFLAGS =
debug: DEBUG_MODE = debug
debug: all

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(OPTIMIZEFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -rf $(BUILDDIR)
	@echo -e "\033[1;31mAll .o deleted.\033[0m"

fclean: clean
	@find -type f -name "*.a" -exec rm -f {} \;
	@rm -rf unit_tests*
	@rm -rf tests/unit_tests*
	@rm -rf vgcore*
	@rm -rf *.log
	@rm -rf $(NAME)
	@echo -e "\033[1;31mProject cleaned.\033[0m"

re:	fclean all

re_debug: fclean debug

valgrind: fclean debug
	@echo -e "\033[0;32mExecuting valgrind...\033[0m"
	@valgrind $(VALGRINDFLAGS) ./$(NAME) $(TEST_ARGS) 2> $(OUTPUT)

# Unit tests Makefile
unit_tests:
	@make unit_tests --no-print-directory -C./tests/

tests_run:
	@make tests_run --no-print-directory -C./tests/
	@gcovr \
	--exclude lib/my/my_printf/round_flag_a.c \
	--exclude lib/mylist/my_list_to_array.c \
	--exclude lib/mylist/my_show_list.c \

# Documentation
doc: tests_run
	@doxygen Doxyfile
	@gcovr \
    --exclude lib/my/my_printf/round_flag_a.c \
    --exclude lib/mylist/my_list_to_array.c \
    --exclude lib/mylist/my_show_list.c \
	--branch --html-details docs/tests/test.html
	@echo -e "\033[1;33mDocumentation generated.\033[0m"
	@google-chrome docs/html/index.html
	@google-chrome docs/tests/test.html
