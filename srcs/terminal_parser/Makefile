SOURCE =	test.c \
			convert_tokens_to_board.c \
			get_tokenized_array.c \
			redirections/are_any_syntax_errors_in_redirections.c \
			redirections/dup_redirection.c \
			redirections/extract_redirections.c \
			redirections/init_brace.c \
			redirections/remove_board_and_tokens.c \
			redirections/remove_redirections.c \
			remove_quotes.c \
			replace_white_spaces.c

.PHONY: all
all :
	make parser

parser :
	gcc -o parser -lreadline $(SOURCE)

.PHONY: clean
clean :
	rm -f parser

.PHONY: fclean
fclean :
	rm -f parser

.PHONY: re
re :
	make fclean
	make all
