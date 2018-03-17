/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:04:49 by mvarga            #+#    #+#             */
/*   Updated: 2017/06/03 17:53:48 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			ft_key_dwn_up(unsigned int key, int *x, int *y, t_term *term)
{
	ft_draw_item(x, y, term, NULL);
	if (key == KEY_DWN)
	{
		*y += 1;
		if (term->lst.cur->next != NULL)
			term->lst.cur = term->lst.cur->next;
		else
		{
			term->lst.cur = term->lst.head;
			*y = 0;
			*x = 0;
		}
		ft_draw_item(x, y, term, term->lst.cur);
		return ;
	}
	*y -= 1;
	if (term->lst.cur->prev != NULL)
		term->lst.cur = term->lst.cur->prev;
	else
	{
		term->lst.cur = term->lst.end;
		*x = (term->word_cnt / (term->lin - 1)) * (term->max_width + 4);
		*y = term->word_cnt % (term->lin - 1) - 1;
	}
	ft_draw_item(x, y, term, term->lst.cur);
}

static void		ft_key_rgh(int *x, int *y, t_term *term)
{
	int		cnt;
	int		tmpy;

	tmpy = *y + 1;
	cnt = term->lin - 1;
	if (cnt > term->word_cnt)
		ft_key_dwn_up(KEY_DWN, x, y, term);
	else
	{
		while (cnt--)
		{
			if (term->lst.cur->next != NULL)
				ft_key_dwn_up(KEY_DWN, x, y, term);
			else
			{
				ft_key_dwn_up(KEY_DWN, x, y, term);
				if (tmpy == (term->lin - 1))
					return ;
				while (tmpy--)
					ft_key_dwn_up(KEY_DWN, x, y, term);
				break ;
			}
		}
	}
}

static void		ft_key_lft(int *x, int *y, t_term *term)
{
	int		cnt;
	int		tmpy;

	if ((cnt = term->lin - 2) > term->word_cnt || term->lin == 1)
		ft_key_dwn_up(KEY_UP, x, y, term);
	else if (term->lst.cur->prev == NULL)
	{
		ft_key_dwn_up(KEY_UP, x, y, term);
		if (!(term->word_cnt % (term->lin - 1)))
			return ;
		while (*y)
			ft_key_dwn_up(KEY_UP, x, y, term);
		ft_key_dwn_up(KEY_UP, x, y, term);
		return ;
	}
	if (cnt > term->word_cnt || term->lin == 1)
		return ;
	if (*x == 0)
		ft_key_dwn_up(KEY_UP, x, y, term);
	tmpy = *y;
	while (*y)
		ft_key_dwn_up(KEY_UP, x, y, term);
	ft_key_dwn_up(KEY_UP, x, y, term);
	while (tmpy != *y)
		ft_key_dwn_up(KEY_UP, x, y, term);
}

static void		ft_key_sps(int *x, int *y, t_term *term)
{
	if (term->lst.cur->item.flag)
	{
		term->lst.cur->item.flag = 0;
		ft_goto_xy(x, y, term);
		ft_putendl_fd(term->lst.cur->item.name, term->fd);
	}
	else
	{
		term->lst.cur->item.flag = 1;
		ft_goto_xy(x, y, term);
		tputs(tgetstr("so", NULL), 1, ft_put);
		ft_putendl_fd(term->lst.cur->item.name, term->fd);
		tputs(tgetstr("se", NULL), 1, ft_put);
	}
	ft_key_dwn_up(KEY_DWN, x, y, term);
}

void			ft_navig_keys(int *x, int *y, unsigned long key, t_term *term)
{
	while (read(term->fd, &key, sizeof(unsigned long)) != 0)
	{
		ft_windsize(x, y, term);
		if (key == KEY_ESC)
		{
			ft_close_visual_mode(term);
			ft_delete_list(term);
		}
		if (term->word_cnt > ((term->lin - 1) * ((term->col) / \
												(term->max_width + 4))))
			;
		else if (key == KEY_ENTR)
			ft_print_return(term);
		else if (key == KEY_DWN || key == KEY_UP)
			ft_key_dwn_up(key, x, y, term);
		else if (key == KEY_RGHT)
			ft_key_rgh(x, y, term);
		else if (key == KEY_LFT)
			ft_key_lft(x, y, term);
		else if (key == KEY_SP)
			ft_key_sps(x, y, term);
		else if (key == KEY_BACKSP || key == KEY_DEL)
			ft_key_del(x, y, term);
		key = 0;
	}
}
