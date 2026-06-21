/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:26 by kexu              #+#    #+#             */
/*   Updated: 2026/06/21 01:52:41 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static int	run_lexer(char *line, t_token **tokens, int debug_ast)
{
	*tokens = lexer(line);
	if (!*tokens)
	{
		set_last_status(2);
		return (0);
	}
	if (debug_ast)
	{
		printf("TOKENS\n");
		print_tokens(*tokens);
	}
	return (1);
}

static int	run_parser(t_token *tokens, char **envp, t_ast **tree,
	int debug_ast)
{
	*tree = parser(tokens);
	if (!*tree)
	{
		set_last_status(2);
		return (0);
	}
	if (debug_ast)
	{
		printf("RAW AST\n");
		print_ast(*tree, 0);
	}
	expand_ast(*tree, envp);
	if (debug_ast)
	{
		printf("EXPANDED AST\n");
		print_ast(*tree, 0);
	}
	return (1);
}*/

/*static void	process_line(char *line, char **envp, t_env **env, int debug_ast)
{
	int		status;
	t_token	*tokens;
	t_ast	*tree;

	tokens = NULL;
	tree = NULL;
	if (line && *line)
	{
		add_history(line);
		if (run_lexer(line, &tokens, debug_ast))
			if (run_parser(tokens, envp, &tree, debug_ast))
			{
				if (prepare_heredoc(tree) == 0)
				{
					status = execute_ast(tree, env, 0);
					set_last_status(status);
				}
				else
					set_last_status(130);
			}
	}
	free_ast(tree);
	free_tokens(tokens);
	free(line);
}*/

static void	reset_line(t_shell *shell)
{
	if (shell->node)
	{
		free_ast(shell->node);
		shell->node = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}

static void	process_line(t_shell *shell, int debug_ast)
{
	int		status;
	char	**envp;

	envp = generate_tab(shell->env);
	expand_ast(shell->node, envp);
	if (debug_ast)
	{
		printf("EXPANDED AST\n");
		print_ast(shell->node, 0);
	}
	free_words(envp);
	if (prepare_heredoc(shell->node))
	{
		set_shell_status(shell, 130);
		return ;
	}
	status = execute_ast(shell->node, shell, 0);
	set_shell_status(shell, status);
}

static int	prepare_line(char *line, t_shell *shell, int debug_ast)
{	
	add_history(line);
	shell->tokens = lexer(line);
	if (!shell->tokens)
	{
		set_shell_status(shell, 2);
		return (0);
	}
	if (debug_ast)
	{
		printf("TOKENS\n");
		print_tokens(shell->tokens);
	}
	shell->node = parser(shell->tokens);
	if (!shell->node)
	{
		set_shell_status(shell, 2);
		return (0);
	}
	if (debug_ast)
	{
		printf("RAW AST\n");
		print_ast(shell->node, 0);
	}
	return (1);
}

/*
 *
 * Main shell loop:
 * readline returns NULL (Ctrl-D), minishell exits
 * empty line only shows a new prompt and continue
 * no-empty line will be parsed, expanded, and executed
 * after each execution, free tokens and AST and line string
 * 
 */

static void	shell_loop(char **envp, int debug_ast)
{
	char	*line;
	t_shell	shell;
	int		status;

	if (init_shell(&shell, envp))
		return ;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			status = shell.last_status;
			write(1, "\rexit\n", 6);
			cleanup_shell(&shell);
			rl_clear_history();
			exit(status);
		}
		if (*line)
		{
			if (prepare_line(line, &shell, debug_ast))
				process_line(&shell, debug_ast);	
		}
		reset_line(&shell);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	debug_ast;

	debug_ast = 0;
	if (argc == 2 && !ft_strncmp(argv[1], "--debug-ast", 11)
		&& ft_strlen(argv[1]) == 11)
		debug_ast = 1;
	configure_terminal();
	setup_interactive_signals();
	shell_loop(envp, debug_ast);
	return (0);
}
