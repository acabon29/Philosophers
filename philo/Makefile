###############    variables    ###############

CFLAGS = -Wall -Wextra -Werror -g -I./includes 
# LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline -lncurses


SRC_DIR = ./srcs
OBJS_DIR = ./objs
OUTPUT_DIR ?= .
NAME ?= philo

###############    Files    ###############

SRC_GENERAL =	main 


SRC	= $(addprefix $(SRC_DIR)/, $(addsuffix .c,	$(SRC_GENERAL) \
))

OBJS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC))

###############    Comilation    ###############
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)-o $(OUTPUT_DIR)/$(NAME) $(OBJS)
#  $(LDFLAGS) 

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<


###############    Cleaning    ###############
clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

###############    Re    ###############
re: fclean all
