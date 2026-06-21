/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:38:30 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/22 00:32:09 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
    g_signal = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

static void	setup_heredoc_signals(void)
{
	struct sigaction	sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_sigint;
	sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void read_loop(char *sep, int *fd)
{
    char    *line;

    while (1)
    {
        line = readline("> ");
        if (g_signal == SIGINT)
        {
            free(line);
            break ;
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
        ft_putendl_fd(line, fd[1]);
        free(line);
    }
}

void heredoc_process(int *fd, char *sep)
{
    g_signal = 0;
    setup_heredoc_signals();
    close(fd[0]);
    read_loop(sep, fd);
    close(fd[1]);
    if (g_signal == SIGINT)
        exit(130);
    exit(0);
}

int  heredoc_child(char *sep)
{
    int     fd[2];
    pid_t   pid;
    int     status;
    
    if (pipe(fd) < 0)
        return (perror("pipe"), -1);
    g_signal = 0;
    setup_parent_wait_signals();
    pid = fork();
    if (pid < 0)
        return (close(fd[0]), close(fd[1]), perror("fork"), -1);
    if (pid == 0)
        heredoc_process(fd, sep);
    close(fd[1]);
    waitpid(pid, &status, 0);
    setup_interactive_signals();
    if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
    {
        g_signal = SIGINT;
        close(fd[0]);
        return (-1);
    }
    return (fd[0]);
}
