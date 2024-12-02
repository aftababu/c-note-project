#include <stdio.h>
#include <conio.h> // For getch() on Windows
#include <stdlib.h> // For system("cls")
#define UP 72
#define DOWN 80
#define ENTER 13

void displayMenu(const char *options[], int size, int selected) {
    system("cls"); // Clear screen
    for (int i = 0; i < size; i++) {
        if (i == selected)
            printf("\033[1;32m-> %s\033[0m\n", options[i]); // Green color
        else
            printf("   %s\n", options[i]);
    }
}

int main() {
    const char *mainMenu[] = {"1. Option 1", "2. Option 2", "3. Option 3", "Exit"};
    const char *submenu1[] = {"1.1 Suboption 1", "1.2 Suboption 2", "1.3 Suboption 3", "Back"};
    int mainSize = sizeof(mainMenu) / sizeof(mainMenu[0]);
    int submenuSize = sizeof(submenu1) / sizeof(submenu1[0]);

    int selected = 0, inSubmenu = 0;
    while (1) {
        if (!inSubmenu) {
            displayMenu(mainMenu, mainSize, selected);
        } else {
            displayMenu(submenu1, submenuSize, selected);
        }

        char key = getch();
        if (key == -32) { // Arrow keys start with -32 in some systems
            key = getch();
            if (key == UP && selected > 0)
                selected--;
            else if (key == DOWN && ((inSubmenu && selected < submenuSize - 1) || (!inSubmenu && selected < mainSize - 1)))
                selected++;
        } else if (key == ENTER) {
            if (!inSubmenu) {
                if (selected == 0) {
                    // Enter submenu
                    inSubmenu = 1;
                    selected = 0;
                } else if (selected == mainSize - 1) {
                    // Exit
                    break;
                }
            } else {
                if (selected == submenuSize - 1) {
                    // Back to main menu
                    inSubmenu = 0;
                    selected = 0;
                }
            }
        }
    }

    printf("Exiting program.\n");
    return 0;
}
