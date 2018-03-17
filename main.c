/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:58:35 by mvarga            #+#    #+#             */
/*   Updated: 2017/06/03 17:56:56 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				ft_put(int c)
{
	int fd;

	fd = open("/dev/tty", O_WRONLY);
	write(fd, &c, 1);
	close(fd);
	return (TRUE);
}

void			ft_term_init(t_term *term)
{
	static t_term	*t;

	if (term)
		t = term;
	else
		term = t;
	if ((tgetent(NULL, getenv("TERM"))) > 0)
	{
		term->fd = open("/dev/tty", O_RDWR | O_NDELAY);
		ioctl(term->fd, TIOCGETA, &(term->old));
		term->new = term->old;
		term->col = tgetnum("co");
		term->lin = tgetnum("li");
		term->new.c_lflag &= ~(ICANON | ECHO);
		term->new.c_cc[VMIN] = 1;
		term->new.c_cc[VTIME] = 0;
		ft_open_visual_mode(term);
		ft_draw(term);
		return ;
	}
	ft_putendl("No TERM detected!");
	ft_delete_list(term);
}

void			ft_print_return(t_term *term)
{
	int cnt;

	ft_close_visual_mode(term);
	cnt = 0;
	term->lst.cur = term->lst.head;
	while (term->lst.cur)
	{
		if (term->lst.cur->item.flag)
		{
			if (cnt++)
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(term->lst.cur->item.name, 1);
		}
		term->lst.cur = term->lst.cur->next;
	}
	ft_putchar_fd('\n', 1);
	ft_delete_list(term);
}

static void		ft_max_width(t_term *term, char **argv)
{
	int		max_len;
	int		tmp;

	max_len = 0;
	while (*argv)
	{
		tmp = ft_strlen(*argv++);
		if (max_len < tmp)
			max_len = tmp;
	}
	term->max_width = max_len;
}

int				main(int argc, char **argv)
{
	t_term				term;

	if (argc != 1)
	{
		term.word_cnt = --argc;
		ft_max_width(&term, ++argv);
		ft_save_list(&term, argv);
		ft_delete_list(&term);
		ft_term_init(&term);
	}
	ft_putstr("Usage : ./ft_select <arg 1> ... <arg n>\n");
	return (0);
}
