NAME = minishell
Header = minishell.h

FILE = minishell.c   parser.c
CC = gcc
file = ./libft/libft.a
CFLAGS =  -Wall -Wextra -Werror   -fsanitize=address


HEAD = -lreadline -L/goinfre/asekkak/homebrew/opt/readline/lib 
INCLUDE= -I/goinfre/asekkak/homebrew/opt/readline/include


$(RM) = rm -rf

OBG = $(FILE:.c=.o)
 
all: $(NAME) 

$(file):
	make -C libft
 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@  
 

$(NAME): $(OBG) $(file)
	$(CC) $(CFLAGS) $(OBG) $(HEAD) $(file) -o $(NAME)

clean: 
	$(RM) $(OBG) ./libft/*.o

fclean: clean 
	$(RM) $(NAME)  ./libft/*.a

re: fclean all

 

.PHONY: bonus all re fclean clean  libft