/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:12:30 by mvarga            #+#    #+#             */
/*   Updated: 2017/06/03 18:12:58 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			ft_add_item(char *str, t_lstarg *plst)
{
	t_lst	*pnew;

	pnew = (t_lst *)malloc(sizeof(t_lst));
	if (pnew == NULL)
		exit(EXIT_FAILURE);
	pnew->item.flag = 0;
	ft_strcpy(pnew->item.name, str);
	pnew->next = NULL;
	if (plst->cnt == 0)
	{
		plst->head = pnew;
		plst->head->prev = NULL;
	}
	else
	{
		plst->end->next = pnew;
		pnew->prev = plst->end;
	}
	plst->end = pnew;
	plst->cnt++;
}

void				ft_save_list(t_term *term, char **argv)
{
	term->lst.cur = NULL;
	term->lst.end = NULL;
	term->lst.head = NULL;
	term->lst.cnt = 0;
	while (*argv)
		ft_add_item(*argv++, &(term->lst));
	term->lst.cur = term->lst.head;
}

void				ft_delete_list(t_term *term)
{
	static int		flag = 0;
	static t_term	*t;
	t_lst			*psave;

	if (term)
		t = term;
	else
		term = t;
	if (flag++)
	{
		while (term->lst.head != NULL)
		{
			psave = term->lst.head->next;
			free(term->lst.head);
			term->lst.head = psave;
		}
		term->lst.cur = NULL;
		term->lst.end = NULL;
		term->lst.head = NULL;
		term->lst.cnt = 0;
		exit(EXIT_SUCCESS);
	}
}

static int			ft_del_last(t_term *term)
{
	if (term->word_cnt == 1)
	{
		if (term->lst.head != NULL)
		{
			free(term->lst.head);
			term->lst.cur = NULL;
			term->lst.end = NULL;
			term->lst.head = NULL;
			ft_clear_screen();
		}
		else
		{
			ft_close_visual_mode(term);
			exit(EXIT_SUCCESS);
		}
		return (TRUE);
	}
	return (FALSE);
}

void				ft_key_del(int *x, int *y, t_term *term)
{
	t_lst		*elm;

	if (ft_del_last(term))
		return ;
	elm = term->lst.cur;
	if (elm->prev)
		elm->prev->next = elm->next;
	if (elm->next)
		elm->next->prev = elm->prev;
	if (!elm->prev)
		term->lst.head = elm->next;
	if (!elm->next)
		term->lst.end = elm->prev;
	if (!term->lst.cur->next)
		ft_key_dwn_up(KEY_UP, x, y, term);
	else
	{
		ft_key_dwn_up(KEY_UP, x, y, term);
		ft_key_dwn_up(KEY_DWN, x, y, term);
	}
	free(elm);
	term->lst.cnt = --term->word_cnt;
	ft_draw(term);
}
