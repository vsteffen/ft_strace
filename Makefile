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

CFLAGS = -Wall -Wextra -g

ifeq ($(no-asm),y)
	NO-ASM:= no-asm
endif

LIB	=	$(ROOT)/lib
LIBSRCS	=	$(ROOT)/libsrcs

ROOT  	=	$(shell /bin/pwd)
OPATH 	=	$(ROOT)/objs
CPATH 	=	$(ROOT)/srcs
HPATH 	=	-I $(ROOT)/includes

SRC =	ft_strace.c \
		check_args.c \
		print_syscall_arg.c \
		syscall_handlers.c

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

.PHONY: all clean fclean re
.SILENT: $(NAME) $(OPATH) $(OPATH)/%.o clean fclean re

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