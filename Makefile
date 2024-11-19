NAME = philo

SRCS =	check.c free.c init.c monitor_finish.c monitor.c mutex.c utils.c utils2.c main.c

OBJS  = $(SRCS:.c=.o)

HEADER_FILE = push_swap.h

CC = cc
CFLAGS = -g
#CFLAGS = -g -fsanitize=thread
# CFLAGS = -Wall -Wextra -Werror -Wunreachable-code

all: $(NAME)

$(NAME):$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER_FILE)
		$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re: fclean all
# --tool=helgrind
.PHONY: all clean fclean re

# 5 900 295 100 10
