#ifndef VBC_H
#define VBC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

extern char *g_ptr;

int		add_up(void);
int		make_multi(void);
int		use_terms(void);
void	error_exit(char c);

#endif