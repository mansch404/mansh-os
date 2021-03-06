#include "print.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char
{
    uint8_t character;
    uint8_t color;
};

struct Char *buffer = (struct Char *)0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row)
{
    struct Char empty = (struct Char){
        character : ' ',
        color : color,
    };

    for (size_t col = 0; col < NUM_COLS; col++)
    {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear()
{
    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        clear_row(i);
    }
}

void print_newline()
{
    col = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++)
    {
        for (size_t col = 0; col < NUM_COLS; col++)
        {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_char(char character)
{
    if (character == '\n')
    {
        print_newline();
        return;
    }

    if (col > NUM_COLS)
    {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char){
        character : (uint8_t)character,
        color : color,
    };

    col++;
}

void print_str(char *str)
{
    for (size_t i = 0; 1; i++)
    {
        char character = (uint8_t)str[i];

        if (character == '\0')
        {
            return;
        }

        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background)
{
    color = foreground + (background << 4);
}

void render_square(uint8_t fromX, uint8_t toX, uint8_t fromY, uint8_t toY)
{
    uint8_t n = 0;
    for (size_t y = 0; y < NUM_ROWS; y++)
    {
        for (size_t x = 0; x < NUM_COLS; x++)
        {
            if (x >= fromX && x <= toX && y >= fromY && y <= toY)
            {
                struct Char renderpx = (struct Char){
                    character : ' ',
                    color : 255,
                };
                buffer[x + NUM_COLS * y] = renderpx;
                n++;
            }
        }
    }
}

void render_text(char* text)
{
    for (size_t y = 0; y < NUM_ROWS; y++)
    {
        for (size_t x = 0; x < NUM_COLS; x++)
        {
            if (x <= sizeof(text) & y == 0) {
                struct Char renderpx = (struct Char){
                    character : (char)text[x],
                    color : 15,
                };
                buffer[x + NUM_COLS * y] = renderpx;
            }
        }
    }
}

void inf_render()
{
    while (1)
    {
        render_text("hello :)");
    }
}
