#include "ui_ncurses.h"

#include <ncurses.h>

/*
 * Одна строка меню состоит из двух частей:
 * - value: число, которое main.c уже понимает в switch
 * - label: текст, который показывается на экране
 *
 * Так ncurses UI остается маленьким.
 * Мы пока не переписываем логику программы.
 * Мы только заменяем старое printf-меню на ncurses-меню.
 */
typedef struct {
    int value;
    const char *label;
} MenuItem;

/*
 * Порядок здесь - это порядок на экране.
 * Значения должны совпадать с case-числами в main.c.
 */
static const MenuItem MENU_ITEMS[] = {
    {1, "Print grades"},
    {2, "Show max"},
    {3, "Show average"},
    {4, "Show passed students"},
    {5, "Show failed students"},
    {6, "Save students to file"},
    {7, "Read students from file"},
    {8, "Read students from keyboard"},
    {9, "Edit grade"},
    {10, "Add grade"},
    {11, "Delete grade"},
    {12, "Toggle auto save"},
    {0, "Exit"},
};

static const int MENU_ITEM_COUNT = sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]);

static void StartNcurses(void)
{
    /*
     * initscr включает ncurses-режим.
     * После этого лучше рисовать через ncurses-функции, а не через printf.
     */
    initscr();

    /*
     * cbreak позволяет getch() получать клавишу сразу.
     * Без этого пользователю иногда нужно нажимать Enter после каждой клавиши.
     */
    cbreak();

    /*
     * noecho запрещает терминалу печатать каждую нажатую клавишу.
     * Выбранную строку меню UI рисует сам.
     */
    noecho();

    /*
     * keypad позволяет getch() понимать специальные клавиши:
     * KEY_UP, KEY_DOWN и другие.
     */
    keypad(stdscr, TRUE);

    /*
     * Для меню не нужен мигающий курсор.
     * Не все терминалы умеют его прятать, поэтому результат curs_set игнорируем.
     */
    curs_set(0);
}

static void StopNcurses(void)
{
    /*
     * endwin возвращает терминал в обычный режим.
     * Это важно, потому что остальная часть программы пока использует printf/fgets.
     */
    endwin();
}

static void DrawMenu(bool hasGradesData, bool autosave, int gradeCount, int selected)
{
    /*
     * clear очищает ncurses-экран.
     * Пользователь увидит новый экран только после refresh().
     */
    clear();

    /*
     * box рисует простую рамку вокруг всего окна терминала.
     * stdscr - это основной экран ncurses.
     */
    box(stdscr, 0, 0);

    mvprintw(1, 3, "Grade Manager");
    mvprintw(2, 3, "Use Up/Down arrows and Enter. Press q to exit.");

    /*
     * Небольшая строка статуса делает экран полезнее,
     * но не меняет логику оценок в grades.c.
     */
    mvprintw(
        4,
        3,
        "Grades loaded: %s | Count: %d | Autosave: %s",
        hasGradesData ? "yes" : "no",
        gradeCount,
        autosave ? "on" : "off"
    );

    for (int i = 0; i < MENU_ITEM_COUNT; i++) {
        int row = 6 + i;

        /*
         * A_REVERSE - простой стиль подсветки.
         * Включаем его только для выбранной строки.
         */
        if (i == selected) {
            attron(A_REVERSE);
        }

        mvprintw(row, 5, "%2d - %s", MENU_ITEMS[i].value, MENU_ITEMS[i].label);

        if (i == selected) {
            attroff(A_REVERSE);
        }
    }

    mvprintw(6 + MENU_ITEM_COUNT + 2, 3, "This is only the first ncurses step: menu selection.");

    /*
     * refresh отправляет все изменения на настоящий экран терминала.
     */
    refresh();
}

static int MoveSelection(int selected, int key)
{
    if (key == KEY_UP) {
        selected--;
        if (selected < 0) {
            selected = MENU_ITEM_COUNT - 1;
        }
    } else if (key == KEY_DOWN) {
        selected++;
        if (selected >= MENU_ITEM_COUNT) {
            selected = 0;
        }
    }

    return selected;
}

int UiSelectMenuOption(bool hasGradesData, bool autosave, int gradeCount)
{
    int selected = 0;
    int result = 0;

    StartNcurses();

    while (1) {
        DrawMenu(hasGradesData, autosave, gradeCount, selected);

        int key = getch();

        if (key == KEY_UP || key == KEY_DOWN) {
            selected = MoveSelection(selected, key);
        } else if (key == '\n' || key == KEY_ENTER) {
            result = MENU_ITEMS[selected].value;
            break;
        } else if (key == 'q' || key == 'Q') {
            result = 0;
            break;
        }
    }

    StopNcurses();

    return result;
}
