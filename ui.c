#include "ui.h"
#include <ncurses.h>


struct MenuItem {
    int value;
    const char* Text;
    
};
const int MenuSize = 13;

const struct  MenuItem Menuitems[] = {
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

void StartNcurses(void) {
    initscr(); // initscr включает nсurses экран
    cbreak();
    noecho();
    keypad(stdscr, TRUE); // keypad позволяет принимать стрелочки
    curs_set(0);
    
    

}
void StopNcurses(void) {
    
    endwin();// endwin возвращает терминалу обычный режим
    
}
void DrawMenu(bool HasGradeData,bool AutoSave,int GradeCount,int selected) {
    
    clear();
    box(stdscr, 0, 0);
    mvprintw(1, 3, "Grade Manager");
    mvprintw(2, 3, "Use Up/Down arrows and Enter. Press q to exit.");
    mvprintw(4, 3, "Grade loaded: %s | count: %d | AutoSave: %s \n",
             HasGradeData ? "yes" : "no",
             GradeCount,
             AutoSave ? "on" : "off");
    
    for (int i = 0; i < MenuSize; i++) {
        int row = 6+i;
        if (i == selected) {
            attron(A_REVERSE);
        }
        mvprintw(row, 5, "%d-%s",Menuitems[i].value,Menuitems[i].Text);
        
        if (i == selected) {
            attroff(A_REVERSE);
        }
 }
    

    
    refresh();
    
}
int MoveSelection(int Selected,int key) {
    if (key == KEY_UP) {
        Selected --;
        if (Selected < 0) {
            Selected = MenuSize -1;
        }
    }
    else if(key == KEY_DOWN) {
        Selected++;
        if (Selected >= MenuSize) {
            Selected = 0;
        }
    }
    return Selected;
    
    
    
    
}

static int FindMenuItemByValue(int value)
{
    for (int i = 0; i < MenuSize; i++) {
        if (Menuitems[i].value == value) {
            return i;
        }
    }

    return -1;
}

int UISelectMenuOption(bool HasGradeData,bool AutoSave,int GradeCount) {
    int Selected = 0;
    int Result = 0;
    
    StartNcurses();
    
    
    
    while (1) {
        DrawMenu(HasGradeData, AutoSave,GradeCount,Selected);
        int key = getch();
        if (key == KEY_UP || key == KEY_DOWN) {
            Selected = MoveSelection(Selected, key);
            
        }
        else if  (key == '\n' || key == KEY_ENTER) {
            Result = Menuitems[Selected].value;
            break;
            
        }
        else if (key == 'q' || key == 'Q') {
            Result = 0;
            break;
        }
        else if (key >= '0' && key <= '9') {
            int menuIndex = FindMenuItemByValue(key - '0');
            if (menuIndex != -1) {
                Result = Menuitems[menuIndex].value;
                break;
            }
        }
    }
    
    
    
    
    StopNcurses();
    
    return Result;
}

void UIShowGrades(int *grades, int GradeCount, bool HasGradeData)
{
    StartNcurses();

    clear();
    box(stdscr, 0, 0);

    mvprintw(1, 3, "Student Grades");

    if (!HasGradeData) {
        mvprintw(3, 3, "No grades available.");
    } else if (GradeCount == 0) {
        mvprintw(3, 3, "There are no students.");
    } else {
        mvprintw(3, 3, "Grades loaded: %d", GradeCount);

        int visibleRows = LINES - 8;
        if (visibleRows < 1) {
            visibleRows = 1;
        }

        int gradesToShow = GradeCount;
        if (gradesToShow > visibleRows) {
            gradesToShow = visibleRows;
        }

        for (int i = 0; i < gradesToShow; i++) {
            mvprintw(5 + i, 5, "Student %d: %d", i + 1, grades[i]);
        }

        if (gradesToShow < GradeCount) {
            mvprintw(LINES - 3, 3, "Showing first %d of %d grades.", gradesToShow, GradeCount);
        }
    }

    mvprintw(LINES - 2, 3, "Press any key to return to the menu.");
    refresh();
    getch();

    StopNcurses();
}
