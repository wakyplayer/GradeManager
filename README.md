# GradeManager

GradeManager is a small C console program for managing student grades. It can
read grades, print them, show basic statistics, edit the grade list, and save or
load grades from a text file.

## Branches

- `main` - the latest working console version of the project.
- `ncurses` - ongoing work for an improved terminal UI using `ncurses`. This
  branch is experimental and may or may not be finished.

## Build

```bash
gcc main.c grades.c -o grade_manager
```

Run it with:

```bash
./grade_manager
```
