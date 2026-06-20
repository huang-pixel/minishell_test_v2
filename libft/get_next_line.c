/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 01:06:15 by hhuang2           #+#    #+#             */
/*   Updated: 2026/03/04 01:06:22 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *
 * Remove everything before and including '\n'
 *
 */

void	clean_up_node(t_list_gnl **list)
{
	int			i;
	char		*newline;
	t_list_gnl	*last;
	t_list_gnl	*new_node;

	if (!list)
		return ;
	last = find_last_node(*list);
	newline = ft_strchr(last->str_read, '\n');
	if (!newline || !*(newline + 1))
		return (deallocate(list));
	new_node = malloc(sizeof(t_list_gnl));
	if (!new_node)
		return (deallocate(list));
	new_node->str_read = malloc(BUFFER_SIZE + 1);
	if (!new_node->str_read)
		return (free(new_node), deallocate(list));
	i = 0;
	while (*(++newline))
		new_node->str_read[i++] = *newline;
	new_node->str_read[i] = '\0';
	new_node->next = NULL;
	deallocate(list);
	*list = new_node;
}

/*
 *
 * Get read content and '\n'
 *
 */

char	*get_the_line(t_list_gnl *list)
{
	int		count_len;
	char	*get_per_line;

	if (list == NULL)
		return (NULL);
	count_len = get_line_len(list);
	get_per_line = malloc(count_len + 1);
	if (get_per_line == NULL)
		return (NULL);
	str_dup(list, get_per_line);
	return (get_per_line);
}

/*
 *
 * Add the content extracted to the linked list
 *
 */

void	add_to_list(t_list_gnl **list, char *buf)
{
	t_list_gnl	*new_list;
	t_list_gnl	*last;

	new_list = malloc(sizeof(t_list_gnl));
	if (new_list == NULL)
	{
		free(buf);
		return ;
	}
	new_list->next = NULL;
	new_list->str_read = buf;
	if (*list == NULL)
	{
		*list = new_list;
		return ;
	}
	last = find_last_node(*list);
	last->next = new_list;
}

/*
 *
 * Set a flag during the reading
 * Return: -1, 0 and 1
 * For read error, EOF, success cases
 *
 */

int	extract_content(t_list_gnl **list, int fd)
{
	char			*buf;
	int				byte_read;
	t_list_gnl		*last;

	while (1)
	{
		last = find_last_node(*list);
		if (last && ft_strchr(last->str_read, '\n'))
			return (1);
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (-1);
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read <= 0)
		{
			free(buf);
			return (byte_read);
		}
		buf[byte_read] = '\0';
		add_to_list(list, buf);
	}
}

/*
*
* Prototype return:
* if any characters were read -> line
* if EOF, no data, without newline OR read error -> NULL
*
*/

char	*get_next_line(int fd)
{
	int						read_flag;
	static t_list_gnl		*list = NULL;
	char					*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_flag = extract_content(&list, fd);
	if (read_flag == -1)
		return (deallocate(&list), NULL);
	if (list == NULL)
		return (NULL);
	line = get_the_line(list);
	clean_up_node(&list);
	if (!line)
	{
		deallocate(&list);
		list = NULL;
		free(line);
		line = NULL;
	}
	return (line);
}

/*#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <stdio.h>*/

/*int main(int argc, char *argv[])
{
    int     fd;
    char    *line;

    if (argc == 1)
        return (1);
    fd = open(argv[1], O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}*/

/*int main(void)
{
    int     fd[3];
    char    *line_fd0;
    char    *line_fd1;
    char    *line_fd2;

    fd[0] = open("only_nl.txt", O_RDONLY);
    fd[1] = open("variable_nls.txt", O_RDONLY);
    fd[2] = open("1char.txt", O_RDONLY);

    while ((line_fd0 = get_next_line(fd[0])))
    {
        printf("fd0: %s\n", line_fd0);
        free(line_fd0);
    }
    close(fd[0]);

    while ((line_fd1 = get_next_line(fd[1])))
    {
        printf("fd1: %s\n", line_fd1);
        free(line_fd1);
    }
    close(fd[1]);

    while ((line_fd2 = get_next_line(fd[2])))
    {
        printf("fd2: %s\n", line_fd2);
        free(line_fd2);
    }
    close(fd[2]);
    return (0);
}*/
