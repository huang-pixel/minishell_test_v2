NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
READLINE = -lreadline

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXPANDER_DIR = $(SRC_DIR)/expander
SIGNALS_DIR = $(SRC_DIR)/signals
DEBUG_DIR = $(SRC_DIR)/debug
EXEC_DIR = $(SRC_DIR)/executor
OBJ_DIR = obj

SRCS = \
	$(SRC_DIR)/main.c \
	$(PARSER_DIR)/ast_free.c \
	$(PARSER_DIR)/ast_utiles.c \
	$(PARSER_DIR)/parser.c \
	$(PARSER_DIR)/parser_command_utils.c \
	$(PARSER_DIR)/parser_free_utils.c \
	$(PARSER_DIR)/parser_logical.c \
	$(PARSER_DIR)/parser_pipeline.c \
	$(PARSER_DIR)/parser_primary.c \
	$(PARSER_DIR)/parser_syntax.c \
	$(PARSER_DIR)/parser_syntax_utils.c \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/lexer_quote.c \
	$(LEXER_DIR)/lexer_scan.c \
	$(LEXER_DIR)/lexer_word.c \
	$(LEXER_DIR)/token_free.c \
	$(EXPANDER_DIR)/expander.c \
	$(EXPANDER_DIR)/expander_args.c \
	$(EXPANDER_DIR)/expander_cleanup.c \
	$(EXPANDER_DIR)/expander_env.c \
	$(EXPANDER_DIR)/expander_redirs.c \
	$(EXPANDER_DIR)/expander_status.c \
	$(EXPANDER_DIR)/expander_strip.c \
	$(EXPANDER_DIR)/expander_utils.c \
	$(EXPANDER_DIR)/expander_wildcard.c \
	$(EXPANDER_DIR)/expander_wildcard_sort.c \
	$(SIGNALS_DIR)/signals.c \
	$(DEBUG_DIR)/debug_ast.c \
	$(DEBUG_DIR)/debug_ast_lists.c \
	$(DEBUG_DIR)/debug_ast_names.c \
	$(DEBUG_DIR)/debug_ast_utils.c \
	$(DEBUG_DIR)/token_debug.c \
	$(EXEC_DIR)/buildins_cd.c \
	$(EXEC_DIR)/buildins_export.c \
	$(EXEC_DIR)/buildins_utils.c \
	$(EXEC_DIR)/buildins.c \
	$(EXEC_DIR)/env_to_execve.c \
	$(EXEC_DIR)/exec_pipe_utils.c \
	$(EXEC_DIR)/exec_pipe.c \
	$(EXEC_DIR)/executor.c \
	$(EXEC_DIR)/exit_utils.c \
	$(EXEC_DIR)/export_utils.c \
	$(EXEC_DIR)/heredoc.c \
	$(EXEC_DIR)/init_env.c \
	$(EXEC_DIR)/path.c \
	$(EXEC_DIR)/pipe_close_free.c \
	$(EXEC_DIR)/process_utils.c \
	$(EXEC_DIR)/process.c \
	$(EXEC_DIR)/redirections.c \
	$(EXEC_DIR)/shell.c \
	$(EXEC_DIR)/utils.c \
	$(EXEC_DIR)/exec_and_or.c \
	$(EXEC_DIR)/exec_subshell.c 

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
