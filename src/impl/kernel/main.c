#include "print.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_str("Welcome to manshOS!");
    print_char('\n');
    print_str("v-beta-0.1");
}