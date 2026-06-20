/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:51:03 by hhuang2           #+#    #+#             */
/*   Updated: 2026/03/04 17:51:10 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# define LOWER_CASE "0123456789abcdef"
# define UPPER_CASE "0123456789ABCDEF"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int			ft_isalpha(int ch);
int			ft_isdigit(int ch);
int			ft_isalnum(int ch);
int			ft_isascii(int ch);
int			ft_isprint(int ch);

size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t count);
void		*ft_memmove(void *s1, const void *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *s1, const char *s2, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t num, size_t size);
char		*ft_strdup(const char *s1);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int			ft_printf(const char *fmt, ...);
int			ft_get_format(char spec, va_list ap);
int			ft_print_char(char c);
int			ft_print_str(char *str);
int			ft_print_unsigned(unsigned int n);
int			ft_print_nbr(int n);
int			ft_print_hex(unsigned long long n, char *sym, char spec);

char		*get_next_line(int fd);

typedef struct s_list_gnl
{
	char				*str_read;
	struct s_list_gnl	*next;
}						t_list_gnl;

int			extract_content(t_list_gnl **list, int fd);
void		add_to_list(t_list_gnl **list, char *buf);
char		*get_the_line(t_list_gnl *list);
void		clean_up_node(t_list_gnl **list);

char		*ft_strchr_gnl(const char *s, int c);
int			get_line_len(t_list_gnl *list);
void		str_dup(t_list_gnl *list, char *str);
t_list_gnl	*find_last_node(t_list_gnl *list);
void		deallocate(t_list_gnl **list);

#endif
