#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "control.h"

int main() {
    struct Control *control = create_control();

    void (*menu_item[])(struct Control *) = {NULL, add_vertex, display, add_edge, remove_edge, remove_vertex,weight_search,belmond_ford,find_connections};
    const char *menu[] = {"0. EXIT", "1. ADD VERTEX", "2. DISPLAY", "3. ADD EDGE", "4. REMOVE EDGE",
                          "5. REMOVE VERTEX","6. WEIGHT SEARCH","7. BELMON FORD","8. FIND CONNECTIONS"};
    int a;
    while (1) {
        for (int i = 0; i < 9; ++i) {
            printf("%s\n", menu[i]);
        }
        scanf("%d%*c", &a);
        if (a <= 0 || a > 8)
            break;
        menu_item[a](control);
    }

    delete_control(control);
    return 0;
}
