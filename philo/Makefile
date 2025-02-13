###############    variables    ###############

CFLAGS = -Wall -Wextra -Werror -g 
#  -fsanitize=thread
# LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline -lncurses


SRC_DIR = ./srcs
OBJS_DIR = ./objs
OUTPUT_DIR ?= .
NAME ?= philo

###############    Files    ###############

SRC_GENERAL =	main \
				utils \
				routines \
				philo \
				utils_routines

SRC	= $(addprefix $(SRC_DIR)/, $(addsuffix .c,	$(SRC_GENERAL) \
))

OBJS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC))

###############    Comilation    ###############
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/$(NAME) $(OBJS) -I./includes 
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
