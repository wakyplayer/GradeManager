# Ncurses Basics For GradeManager

This note is for learning just enough `ncurses` to build a simple terminal UI for this project.

The goal is not to make a beautiful app. The goal is to replace a long `printf` menu with a cleaner text screen where the user can press keys, move around, and see results.

## What Is Ncurses?

`ncurses` is a C library for drawing inside the terminal.

Normal C terminal programs usually work like this:

```c
printf("Menu\n");
scanf("%d", &choice);
```

That is simple, but the screen keeps scrolling down.

With `ncurses`, the program can:

- clear the screen
- print text at a chosen row and column
- read one key at a time
- draw boxes and simple menus
- update only parts of the screen

It is still a terminal program. It is not a window app with buttons and mouse controls.

## Why It Fits This Project

A full graphical UI in C would need a bigger framework. That would add too much new complexity too early.

For this grade manager, a text UI is a realistic next step:

- the program can still be written in C
- the grade logic can stay in `grades.c`
- the UI can be improved without rewriting the whole project
- the student learns a useful way to build simple terminal tools

Important: the UI should not duplicate grade logic.

For example, the UI should call existing functions:

```c
FindMax(grades, n);
FindAverage(grades, n);
CountPassed(grades, n);
CountFailed(grades, n);
SetGrade(grades, n, index, grade);
AddGrade(&grades, &n, grade);
DeleteLastGrade(&grades, &n);
```

The UI is only the face of the program. `grades.c` is still the brain.

## Before Starting

Do not start the ncurses UI before the core bugs are fixed.

A good order is:

1. Make sure grade functions work correctly.
2. Make sure adding, editing, deleting, saving, and loading work correctly.
3. Only then create a cleaner terminal UI.

This matters because a UI can hide bugs. If the logic is wrong, the prettier screen will still give wrong answers.

## How To Include Ncurses

At the top of a C file:

```c
#include <ncurses.h>
```

When compiling, link with `ncurses`:

```bash
gcc main.c grades.c -lncurses -o grade_manager
```

If you create a separate UI file:

```bash
gcc main.c grades.c ui_ncurses.c -lncurses -o grade_manager
```

## The Smallest Ncurses Program

```c
#include <ncurses.h>

int main(void)
{
    initscr();              // start ncurses mode
    printw("Hello ncurses");
    refresh();              // show changes on the screen
    getch();                // wait for one key
    endwin();               // return terminal to normal

    return 0;
}
```

The most important rule:

If you call `initscr()`, you must later call `endwin()`.

If the program exits without `endwin()`, the terminal can look broken until you reset it.

## The Main Ncurses Functions

### `initscr`

Starts ncurses.

```c
initscr();
```

Call this once at the start of the UI.

### `endwin`

Stops ncurses and returns the terminal to normal.

```c
endwin();
```

Call this before the program exits.

### `printw`

Like `printf`, but for the ncurses screen.

```c
printw("Grade: %d", grade);
```

### `mvprintw`

Moves to a row and column, then prints text.

```c
mvprintw(2, 4, "Grade Manager");
```

This means:

- row `2`
- column `4`
- print `"Grade Manager"`

Rows and columns start from `0`.

### `clear`

Clears the screen.

```c
clear();
```

Use this before drawing a new screen.

### `refresh`

Shows the changes.

```c
refresh();
```

In ncurses, drawing functions prepare the screen, but the user may not see the changes until `refresh()`.

### `getch`

Reads one key.

```c
int key = getch();
```

Example:

```c
int key = getch();

if (key == 'q') {
    // quit
}
```

## Useful Setup

Most ncurses programs start with setup like this:

```c
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);
```

What this means:

- `cbreak()` makes key input arrive immediately
- `noecho()` stops typed keys from appearing automatically
- `keypad(stdscr, TRUE)` lets the program read arrow keys

At the end:

```c
endwin();
```

## Drawing Text At Positions

The terminal screen is like a grid.

Top left is:

```text
row 0, column 0
```

Example:

```c
clear();
mvprintw(0, 0, "Grade Manager");
mvprintw(2, 0, "1 - Print grades");
mvprintw(3, 0, "2 - Show max");
mvprintw(4, 0, "0 - Exit");
refresh();
```

This draws a simple menu in the same place every time.

## Drawing Simple Shapes

### One Character

```c
mvaddch(5, 10, '*');
```

This draws `*` at row `5`, column `10`.

### Horizontal Line

```c
mvhline(1, 0, '-', 30);
```

This draws 30 `-` characters on row `1`.

### Vertical Line

```c
mvvline(2, 0, '|', 10);
```

This draws 10 `|` characters starting at row `2`, column `0`.

### Box Around The Screen

```c
box(stdscr, 0, 0);
```

`stdscr` means the main screen.

Full example:

```c
clear();
box(stdscr, 0, 0);
mvprintw(1, 2, "Grade Manager");
refresh();
```

## A Simple Menu Loop

This is the basic idea for the project:

```c
#include <stdbool.h>
#include <ncurses.h>
#include "grades.h"

static void DrawMenu(void)
{
    clear();
    box(stdscr, 0, 0);

    mvprintw(1, 2, "Grade Manager");
    mvprintw(3, 2, "1 - Print grades");
    mvprintw(4, 2, "2 - Show max");
    mvprintw(5, 2, "3 - Show average");
    mvprintw(6, 2, "4 - Show passed students");
    mvprintw(7, 2, "5 - Show failed students");
    mvprintw(8, 2, "0 - Exit");

    mvprintw(10, 2, "Press a key:");
    refresh();
}

int main(void)
{
    int grades[] = {80, 70, 95};
    int n = 3;
    bool running = true;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (running) {
        DrawMenu();

        int key = getch();

        clear();
        box(stdscr, 0, 0);

        switch (key) {
        case '1':
            mvprintw(2, 2, "Grades:");
            for (int i = 0; i < n; i++) {
                mvprintw(3 + i, 2, "%d", grades[i]);
            }
            break;

        case '2':
            mvprintw(2, 2, "Max grade: %d", FindMax(grades, n));
            break;

        case '3':
            mvprintw(2, 2, "Average: %.2f", FindAverage(grades, n));
            break;

        case '4':
            mvprintw(2, 2, "Passed students: %d", CountPassed(grades, n));
            break;

        case '5':
            mvprintw(2, 2, "Failed students: %d", CountFailed(grades, n));
            break;

        case '0':
            running = false;
            break;

        default:
            mvprintw(2, 2, "Unknown option");
            break;
        }

        if (running) {
            mvprintw(12, 2, "Press any key to return to menu");
            refresh();
            getch();
        }
    }

    endwin();
    return 0;
}
```

This is not the final project code. It is a learning example.

The important idea is that the menu calls `FindMax`, `FindAverage`, `CountPassed`, and `CountFailed`. It does not calculate those things again inside the UI.

## Reading Numbers In Ncurses

For simple key choices, `getch()` is enough.

For real number input, one simple way is:

```c
echo();
nocbreak();

char text[20];
mvprintw(5, 2, "Enter grade: ");
getnstr(text, sizeof(text) - 1);

cbreak();
noecho();
```

Then convert the text to a number:

```c
int grade = atoi(text);
```

But `atoi` is not very strict. Later, it is better to use `strtol` so the program can reject bad input like `abc`.

For this student project, keep input simple first:

1. Ask for text.
2. Convert to number.
3. Check that the number is from `0` to `100`.
4. If it is wrong, show an error message.

## Showing A Message

A small helper function can make the UI cleaner:

```c
static void ShowMessage(const char *message)
{
    clear();
    box(stdscr, 0, 0);
    mvprintw(2, 2, "%s", message);
    mvprintw(4, 2, "Press any key to continue");
    refresh();
    getch();
}
```

Then use it like this:

```c
ShowMessage("No grades available");
```

This is better than repeating the same drawing code many times.

## A Better Project Structure

Keep the files separated by job:

```text
grades.h          declarations for grade logic
grades.c          grade logic
main.c            starts the program
ui_ncurses.c      ncurses menu and screens
```

The UI file can include:

```c
#include "grades.h"
#include <ncurses.h>
```

The UI should ask the grade logic questions:

```c
int max = FindMax(grades, n);
double average = FindAverage(grades, n);
```

The UI should not copy the loops from `grades.c`.

Bad idea:

```c
// Do not duplicate this in the UI.
int max = grades[0];
for (int i = 0; i < n; i++) {
    if (grades[i] > max) {
        max = grades[i];
    }
}
```

Good idea:

```c
int max = FindMax(grades, n);
```

## Simple Screen Plan For GradeManager

Start with a very small UI:

```text
+--------------------------------+
| Grade Manager                  |
|                                |
| 1 - Print grades               |
| 2 - Show max                   |
| 3 - Show average               |
| 4 - Show passed students       |
| 5 - Show failed students       |
| 0 - Exit                       |
|                                |
| Press a key:                   |
+--------------------------------+
```

After that works, add more options:

- save grades to file
- load grades from file
- read grades from keyboard
- edit one grade
- add one grade
- delete last grade
- toggle auto save

Do not build everything at once.

## Common Mistakes

### Forgetting `refresh`

If nothing appears, check if you called:

```c
refresh();
```

### Forgetting `endwin`

If the terminal looks strange after the program exits, the program maybe did not call:

```c
endwin();
```

### Mixing `printf` With Ncurses

After `initscr()`, avoid normal `printf` for the UI.

Use:

```c
printw();
mvprintw();
```

instead.

### Duplicating Logic

Do not rewrite grade calculations in the UI.

The UI should call `grades.c` functions.

### Making The First UI Too Big

First make only:

- draw menu
- read key
- show one result
- return to menu
- exit cleanly

Then add the rest.

## Tiny Class Exercise

Before changing the full project, create a small test file and try this:

1. Start ncurses.
2. Draw a box.
3. Print `"Grade Manager"` at the top.
4. Show three menu items.
5. Read one key.
6. Show a message based on that key.
7. Exit with `endwin()`.

After that works, connect the menu to the real grade functions.

## Final Rule

Keep this separation clear:

```text
grades.c      knows how grades work
ncurses UI    knows how to show things on the screen
```

If the UI needs a result, it should ask `grades.c`.

That is how the project stays easier to understand and easier to change later.
