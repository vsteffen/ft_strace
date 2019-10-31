# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/06 20:52:05 by vsteffen          #+#    #+#              #
#    Updated: 2018/03/20 18:17:27 by vsteffen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT	= ft_strace
NAME	= ft_strace

CC 	=	/usr/bin/clang
RM 	=	/bin/rm
MAKE 	=	/usr/bin/make
MKDIR 	=	/bin/mkdir -p
AR 	=	/usr/bin/ar
RANLIB 	=	/usr/bin/ranlib
GIT	=	/usr/bin/git

OBJ = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

CFLAGS = -Wall -Wextra -g # -fsanitize=address

ifeq ($(no-asm),y)
	NO-ASM:= no-asm
endif

LIB	=	$(ROOT)/lib
LIBSRCS	=	$(ROOT)/libsrcs

ROOT  	=	$(shell /bin/pwd)
OPATH 	=	$(ROOT)/objs
CPATH 	=	$(ROOT)/srcs
HPATH 	=	-I $(ROOT)/includes
TESTPATH	=	$(ROOT)/test
TESTBINPATH	=	$(ROOT)/bin_test

SRC =	ft_strace.c \
		check_args.c \
		signals.c \
		print_syscall.c \
		syscall_handler_gen.c \
		syscall_handler_read_write.c

COMPILE	= no

OS	:= $(shell uname -s)

ifeq ($(OS),Darwin)
	NPROCS:=$(shell sysctl -n hw.ncpu)
else
	NPROCS:=$(shell grep -c ^processor /proc/cpuinfo)
endif


define PRINT_RED
	printf "\033[31m$(1)\033[0m"
endef

define PRINT_GREEN
	printf "\033[32m$(1)\033[0m"
endef

define PRINT_YELLOW
	printf "\033[33m$(1)\033[0m"
endef

define PRINT_STATUS
	printf '['
	$(if $(filter $(2),SUCCESS),$(call PRINT_GREEN,$(1)))
	$(if $(filter $(2),FAIL),$(call PRINT_RED,$(1)))
	$(if $(filter $(2),WARN),$(call PRINT_YELLOW,$(1)))
	$(if $(filter $(2),INFO),printf $(1))
	$(if $(filter $(3),-n),printf $(1),echo ']')
endef

.PHONY: all clean fclean re test test-clean
.SILENT: $(NAME) $(OPATH) $(OPATH)/%.o clean fclean re test test-clean

all: $(NAME)

$(NAME): $(OPATH) $(OBJ)
	$(if $(filter $(COMPILE),yes),echo ']')
	printf $(PROJECT)": Building $@ ... "
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(HPATH)
	$(call PRINT_STATUS,DONE,SUCCESS)

$(OPATH)/%.o: $(CPATH)/%.c
	$(if $(filter $(COMPILE),no),@printf $(PROJECT)': Files compiling [')
	$(eval COMPILE := yes)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HPATH)
	@$(call PRINT_GREEN,.)

$(OPATH):
	echo $(PROJECT)": Creation of objects directory"
	$(MKDIR) $@

clean:
	$(RM) -Rf $(OPATH)
	echo $(PROJECT)": Objects cleaned "
	printf $(PROJECT)": $@ rule "
	$(call PRINT_STATUS,DONE,SUCCESS)

fclean: clean
	$(RM) -f $(NAME)
	echo $(PROJECT)": executable clean"
	printf $(PROJECT)": $@ rule "
	$(call PRINT_STATUS,DONE,SUCCESS)

re: fclean
	$(MAKE) -C $(ROOT) -j$(NPROCS) -s

test: $(NAME)
	printf $(PROJECT)": Building tests ... "
	$(MKDIR) $(TESTBINPATH)
	$(CC) $(TESTPATH)/write.c -o $(TESTBINPATH)/32 -m32
	$(CC) $(TESTPATH)/write.c -o $(TESTBINPATH)/64
	$(CC) $(TESTPATH)/execve.c -o $(TESTBINPATH)/execve
	$(CC) $(TESTPATH)/special_syscall.c -o $(TESTBINPATH)/special_32 -m32
	$(CC) $(TESTPATH)/special_syscall.c -o $(TESTBINPATH)/special_64
	$(CC) $(TESTPATH)/corr1.c -o $(TESTBINPATH)/corr1
	$(CC) $(TESTPATH)/corr2.c -o $(TESTBINPATH)/corr2
	$(CC) $(TESTPATH)/corr3.c -o $(TESTBINPATH)/corr3
	$(CC) $(TESTPATH)/corr4.c -o $(TESTBINPATH)/corr4
	$(CC) $(TESTPATH)/corr5.c -o $(TESTBINPATH)/corr5 -pthread
	$(call PRINT_STATUS,DONE,SUCCESS)

test-clean:
	$(RM) -rf $(TESTBINPATH)
	printf $(PROJECT)": tests clean "
	$(call PRINT_STATUS,DONE,SUCCESS)