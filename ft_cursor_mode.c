/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:16:03 by mvarga            #+#    #+#             */
/*   Updated: 2017/06/03 17:43:10 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_signal_handler(int sig)
{
	if (sig == SIGTSTP)
	{
		tputs(tgetstr("cl", NULL), 1, ft_put);
		tputs(tgetstr("cm", NULL), 1, ft_put);
		tputs(tgetstr("te", NULL), 1, ft_put);
		tputs(tgetstr("ve", NULL), 1, ft_put);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
	}
	else if (sig == SIGCONT)
	{
		ft_term_init(NULL);
		signal(SIGCONT, ft_signal_handler);
	}
	else
	{
		tputs(tgetstr("cl", NULL), 1, ft_put);
		tputs(tgetstr("cm", NULL), 1, ft_put);
		tputs(tgetstr("te", NULL), 1, ft_put);
		tputs(tgetstr("ve", NULL), 1, ft_put);
		ft_delete_list(NULL);
	}
}

void			ft_clear_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_put);
}

void			ft_open_visual_mode(t_term *term)
{
	ioctl(term->fd, TIOCSETA, &(term->new));
	tputs(tgetstr("ti", NULL), 1, ft_put);
	tputs(tgetstr("vi", NULL), 1, ft_put);
	if (signal(SIGWINCH, NULL) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGTSTP, ft_signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGCONT, ft_signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGINT, ft_signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGINT, ft_signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void			ft_close_visual_mode(t_term *term)
{
	ioctl(term->fd, TIOCSETA, &(term->old));
	tputs(tgetstr("cl", NULL), 1, ft_put);
	tputs(tgetstr("te", NULL), 1, ft_put);
	tputs(tgetstr("ve", NULL), 1, ft_put);
}
