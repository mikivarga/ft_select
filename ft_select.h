/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:57:45 by mvarga            #+#    #+#             */
/*   Updated: 2017/06/03 18:27:09 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <signal.h>

# define TRUE 1
# define FALSE 0

# define KEY_UP 0x415B1B
# define KEY_DWN 0x425B1B
# define KEY_RGHT 0x435B1B
# define KEY_LFT 0x445B1B
# define KEY_DEL 0x7E335B1B
# define KEY_ENTR 0xA
# define KEY_ESC 0x1B
# define KEY_SP 0x20
# define KEY_BACKSP 0x7F

# define BUF 2048

typedef struct winsize	t_win;

typedef struct			s_item
{
	char				name[BUF];
	int					flag;
}						t_item;

typedef struct			s_lst
{
	t_item				item;
	struct s_lst		*next;
	struct s_lst		*prev;
}						t_lst;

typedef struct			s_lstarg
{
	t_lst				*head;
	t_lst				*cur;
	t_lst				*end;
	int					cnt;
}						t_lstarg;

typedef struct			s_term
{
	int					fd;
	int					col;
	int					lin;
	t_lstarg			lst;
	int					word_cnt;
	int					max_width;
	struct termios		old;
	struct termios		new;
}						t_term;

void					ft_save_list(t_term *term, char **argv);
void					ft_delete_list(t_term *term);
void					ft_term_init(t_term *term);
void					ft_open_visual_mode(t_term *term);
void					ft_close_visual_mode(t_term *term);
int						ft_put(int c);
void					ft_clear_screen(void);
void					ft_draw(t_term *term);
void					ft_draw_list(int *x, int *y, t_term *term, t_lst *cur);
void					ft_goto_xy(int *x, int *y, t_term *term);
void					ft_draw_item(int *x, int *y, t_term *term, t_lst *cur);
void					ft_navig_keys\
						(int *x, int *y, unsigned long key, t_term *term);
void					ft_key_dwn_up\
						(unsigned int key, int *x, int *y, t_term *term);
void					ft_key_del(int *x, int *y, t_term *term);
void					ft_windsize(int *x, int *y, t_term *term);
void					ft_print_return(t_term *term);
#endif
