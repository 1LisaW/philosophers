NAME	= philosophers

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -fsanitize=thread -g

RM		=	rm -rf

SRC_DIR	=	philo

BUILD_DIR	=	build

FILES	=	parse_args check_exit_condition ft_print_info\
			forks\
			shared_helpers\
			 threads helpers actions philosophers clean_data

SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))

OBJS = $(addsuffix .o, $(FILES))

OBJS_WITH_DIR	=	$(addprefix $(SRC_DIR)/$(BUILD_DIR)/, $(OBJS))

%.o : %.c
		$(CC) -c $(CFLAGS) $< -o $@


all:	$(NAME)

$(OBJS_WITH_DIR): $(SRCS)
		@mkdir -p $(SRC_DIR)/$(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(SRCS)
		mv $(OBJS) $(SRC_DIR)/$(BUILD_DIR)/

$(NAME):	$(OBJS_WITH_DIR)
		$(CC) $(CFLAGS) $(OBJS_WITH_DIR) -pthread -o $(NAME)

clean:
	$(RM) $(OBJS_WITH_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all	clean fclean re
