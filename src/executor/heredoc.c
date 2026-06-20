/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:38:30 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/07 00:42:47 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}*/

/*static void	setup_heredoc_signals(void)
{
	struct sigaction	sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_sigint;
	sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}*/

static void read_loop(char *sep, int fd)
{
    char    *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(sep, 2);
	        ft_putstr_fd("')\n", 2);
            break ;
        }
        if (!ft_strncmp(line, sep, ft_strlen(sep) + 1))
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
}

/*
 *
 * 
 */

static int  heredoc_child(char *sep)
{
    int     fd[2];
    pid_t   pid;
    int     status;
    
    if (pipe(fd) < 0)
        return (perror("pipe"), -1); // return -1 for invalid fd
    pid = fork();
    if (pid < 0)
        return (close(fd[0]), close(fd[1]), perror("fork"), -1);
    if (pid == 0)
    {
        close(fd[0]);
        read_loop(sep, fd[1]);
        close(fd[1]);
        exit(0); // child should exit
    }
    close(fd[1]);
    waitpid(pid, &status, 0);
    return (fd[0]);
}

/*
 *
 * Loop t_redir, since a single cmd can several redirections
 * If heredoc found, save fd[0] in t_redir->fd
 */

static int   check_cmd_hd(t_ast *node)
{
    t_redir *tmp;

    tmp = node->redirs;
    while (tmp)
    {
        if (tmp->type == REDIR_HEREDOC)
        {
            tmp->fd = heredoc_child(tmp->file);
            if (tmp->fd < 0)
                return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

/*
 *
 * A recursive way to search heredoc
 * Check left and right side and return value
 * When it goes to PIPE, AND, OR and SUBSHELL call
 * Need to check the value return for each side
 * 
 */

int prepare_heredoc(t_ast *node)
{
    if (!node)
        return (0);
    if (node->type == NODE_CMD)
        return (check_cmd_hd(node));
    if (prepare_heredoc(node->left))
        return (1);
    if (prepare_heredoc(node->right))
        return (1);
    return (0);
}

/*int read_heredoc(char *sep)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
    
    g_signal = 0;
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			close(fd[0]);
			close(fd[1]);
			return (130);
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(sep, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (!ft_strncmp(line, sep, ft_strlen(sep) + 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	setup_interactive_signals();
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}*/

/*static void	heredoc_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);
}*/

/*int heredoc_child(char *sep)
{
    pid_t   pid;
    int     fd[2];
    int     status;

    if (pipe(fd) < 0)
    {
        perror("pipe");
        return (1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return (1);
    }
    if (pid == 0)
    {
        close(fd[0]); // child does not need read side
        setup_heredoc_signals();
        read_heredoc(sep, fd[1]); // keep write only
        close(fd[1]);
        exit(0);
    }
    close(fd[1]); // parent does not write, keep read
    setup_parent_wait_signals();
    waitpid(pid, &status, 0);
    setup_interactive_signals();
    if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
    {
        close(fd[0]);
        return (130);
    }
    if (WIFSIGNALED(status))
    {
        close(fd[0]);
        return (128 + WTERMSIG(status));
    }
    dup2(fd[0], STDIN_FILENO); // stdin now reads from heredoc pipe
    close(fd[0]);
    return (0);
}*/

/*
 *
 * Read heredoc line 
 * 
 */

/*int read_heredoc(char *sep)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) < 0)
        return (perror("pipe"), 1);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(sep, 2);
	        ft_putstr_fd("')\n", 2);
            break ;
        }
        if (!ft_strncmp(line, sep, ft_strlen(sep) + 1))
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd[1]);
        ft_putstr_fd("\n", fd[1]);
        free(line);
    }
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    return (0);
}*/

/*int read_heredoc(char *sep, int fd_w)
{
    char    *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(sep, 2);
	        ft_putstr_fd("')\n", 2);
            break ;
        }
        if(!ft_strncmp(line, sep, ft_strlen(sep) + 1))
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd_w);
        ft_putstr_fd("\n", fd_w);
        free(line);
    }
    return (0);
}*/
