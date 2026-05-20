#ifndef UI_NCURSES_H
#define UI_NCURSES_H

#include <stdbool.h>

/*
 * Это первый маленький шаг в сторону ncurses.
 *
 * main.c не должен знать, как ncurses рисует текст или читает стрелки.
 * main.c должен только спросить: "какой пункт меню выбрал пользователь?"
 */
int UiSelectMenuOption(bool hasGradesData, bool autosave, int gradeCount);

#endif
