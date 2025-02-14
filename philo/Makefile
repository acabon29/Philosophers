
###############    Colors    ###############

RESET := \033[0m
BLUE := \033[34m
PURPLE := \033[35m
YELLOW := \033[33m

###############    variables    ###############

#  -fsanitize=thread can use in compilation for check data race
CFLAGS = -Wall -Wextra -Werror -g

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
	@printf "$(BLUE)Compiling $(NAME)... [$(CFLAGS)]\n$(RESET)"
	@$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/$(NAME) $(OBJS) -I./includes 

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<


###############    Helper    ###############

# shows help
help:
	@perl -e ' $$p=0; while(<>){ $$p=1 if/^# .*/; print $$_=~s/(.+):( |$$).*/\x1b[0;1;2m\$$ make $$1\x1b[0m\n/r=~s/^# /\x1b[1m# \x1b[0;2m/r if $$p; $$p=0 if /:( |$$)/; } ' Makefile | $${PAGER:-less} -R


###############    Cleaning    ###############

clean:
	@rm -f $(OBJS)
	@printf "$(YELLOW)Cleaning objects in $(NAME) successfull !\n$(RESET)"

fclean:
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@printf "$(YELLOW)Cleaning $(NAME) successfull !\n$(RESET)"

###############    Re    ###############

re: fclean all
