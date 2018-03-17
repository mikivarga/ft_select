/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 12:45:30 by mvarga            #+#    #+#             */
/*   Updated: 2017/06/03 17:58:12 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				ft_windsize(int *x, int *y, t_term *term)
{
	t_win		ws;

	ioctl(term->fd, TIOCGWINSZ, &ws);
	if (term->col != ws.ws_col || term->lin != ws.ws_row)
	{
		term->col = ws.ws_col;
		term->lin = ws.ws_row;
		ft_clear_screen();
		if (term->word_cnt > ((term->lin - 1) * ((term->col) / \
												(term->max_width + 4))))
			ft_putendl_fd("window is to small, sorry))", term->fd);
		else
			ft_draw_list(x, y, term, term->lst.cur);
	}
}

void				ft_goto_xy(int *x, int *y, t_term *term)
{
	if (*y > (term->lin - 2))
	{
		*y = 0;
		*x += (term->max_width + 4);
	}
	else if (*y < 0)
	{
		*x -= (term->max_width + 4);
		*y = term->lin - 2;
	}
	tputs(tgoto(tgetstr("cm", NULL), *x, *y), 1, ft_put);
}

void				ft_draw_item(int *x, int *y, t_term *term, t_lst *cur)
{
	ft_goto_xy(x, y, term);
	if (term->lst.cur->item.flag && term->lst.cur == cur)
	{
		tputs(tgetstr("us", NULL), 1, ft_put);
		tputs(tgetstr("so", NULL), 1, ft_put);
		ft_putendl_fd(term->lst.cur->item.name, term->fd);
		tputs(tgetstr("ue", NULL), 1, ft_put);
		tputs(tgetstr("se", NULL), 1, ft_put);
	}
	else if (term->lst.cur == cur)
	{
		tputs(tgetstr("us", NULL), 1, ft_put);
		ft_putendl_fd(term->lst.cur->item.name, term->fd);
		tputs(tgetstr("ue", NULL), 1, ft_put);
	}
	else
	{
		if (term->lst.cur->item.flag)
			tputs(tgetstr("so", NULL), 1, ft_put);
		ft_putendl_fd(term->lst.cur->item.name, term->fd);
		if (term->lst.cur->item.flag)
			tputs(tgetstr("se", NULL), 1, ft_put);
	}
}

void				ft_draw_list(int *x, int *y, t_term *term, t_lst *cur)
{
	static int	flag = FALSE;
	int			xx;
	int			yy;

	xx = 0;
	yy = 0;
	term->lst.cur = term->lst.head;
	ft_clear_screen();
	while (term->lst.cur)
	{
		ft_draw_item(&xx, &yy, term, cur);
		if (term->lst.cur == cur)
		{
			*x = xx;
			*y = yy;
		}
		term->lst.cur = term->lst.cur->next;
		yy++;
	}
	if (!flag++)
		term->lst.cur = term->lst.head;
	else
		term->lst.cur = cur;
	ft_draw_item(x, y, term, term->lst.cur);
}

void				ft_draw(t_term *term)
{
	static int		y = 0;
	static int		x = 0;
	unsigned long	key;

	key = 0;
	if (term->word_cnt > ((term->lin - 1) * ((term->col) / \
											(term->max_width + 4))))
	{
		ft_clear_screen();
		ft_putendl_fd("window is to small, sorry))", term->fd);
	}
	else
		ft_draw_list(&x, &y, term, term->lst.cur);
	ft_navig_keys(&x, &y, key, term);
}
