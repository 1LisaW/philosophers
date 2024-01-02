NAME	= philosophers

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -rf

SRC_DIR	=	philo

BUILD_DIR	=	build

FILES	=	parse_args philosophers

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
		$(CC) $(OBJS_WITH_DIR) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all	clean fclean re