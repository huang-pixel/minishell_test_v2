/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:14:20 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/19 18:59:33 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Unset:
 * remove env variable
 * if key is invalid, unset ignore and echo $? print 0
 * 
 */

int	exec_unset(t_shell *shell, t_ast *node)
{
	t_arg	*arg;
	
	if (!shell || !node || !node->args)
		return (1);
	arg = node->args->next;
	while (arg)
	{
		if (is_valid_key(arg->value))
			delete_env_var(&shell->env, arg->value);
		arg = arg->next;
	}
	return (0);
}

/*
 *
 * Env implement:
 * check env->value, since real env prints only if the value exists
 * 
 */

int	exec_env(t_shell *shell)
{
	t_env	*tmp;

	if (!shell)
		return (1);
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
 *
 * Pwd implement:
 * Use getconf -a to see PATH_MAX
 * 
 */

int exec_pwd(void)
{
	char	cwd[4096];
	
	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/*
 *
 * Echo implement:
 * check "-n" and set newline status 0 or 1
 * write string, following by a space or no space
 * finally check newline status and add newline
 * 
 */

int exec_echo(t_ast *node)
{
	t_arg	*target;
	int		newline;

	if (!node || !node->args)
		return (1);
	newline = 1;
	target = node->args->next;
	while (target && has_n_option(target->value))
	{
		newline = 0;
		target = target->next;
	}
	while (target)
	{
		ft_putstr_fd(target->value, STDOUT_FILENO);
		if (target->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		target = target->next;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	exec_exit(t_ast *node, t_shell *shell)
{
    char        **argv;
    long long   n;
    int         num;

    if (!node || !node->args || !shell)
        exit(1);
    argv = args_list(node->args);
    if (shell->main && isatty(STDIN_FILENO))
        ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (!argv[1])
    {
        exit_free(argv, shell);
        exit(shell->last_status);
    }
    if (!is_numeric(argv[1]) || !ft_atol(argv[1], &n))
        exit_numeric_msg(argv, shell);
    if (argv[2])
    {
        exit_many_args(argv, shell);
        return (1);
    }
    num = (unsigned char)n;
    exit_free(argv, shell);
    exit(num);
}
