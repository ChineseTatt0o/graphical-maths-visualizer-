#include "fibonacci.h"
#include "raylib.h"
#include <stdbool.h>

#define SCALE 10
#define COUNT 10

Color colors[] = {
    (Color){255, 0, 0, 255},
    (Color){0, 255, 0, 255},
    (Color){0, 0, 255, 255},
    (Color){255, 255, 0, 255},
    (Color){255, 0, 255, 255},
    (Color){0, 255, 255, 255},
    (Color){128, 0, 128, 255},
    (Color){255, 165, 0, 255},
    (Color){128, 128, 128, 255},
    (Color){0, 128, 0, 255}
};

int numbers[COUNT];

enum Fold
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void init_fibonacci(void)
{
    numbers[0] = 1;
    numbers[1] = 1;

    for (int i = 2; i < COUNT; i++)
    {
        numbers[i] = numbers[i - 1] + numbers[i - 2];
    }
}

void draw_fibonacci(int start_x, int start_y)
{
    enum Fold current_fold = RIGHT;
    int current_x = start_x;
    int current_y = start_y;

    int min_y = current_y;
    int min_x = current_x;

    for (int i = 0; i < COUNT; i++)
    {
        int size = numbers[i] * SCALE;

        Color color = colors[i % (sizeof(colors) / sizeof(colors[0]))];

        DrawRectangle(current_x, current_y, size, size, WHITE);
        DrawRectangle(current_x + 1, current_y + 1,
                      size - 2, size - 2, color);

        Vector2 center = (Vector2){current_x + size, current_y + size};

        switch (current_fold)
        {
            case RIGHT:
                center = (Vector2){current_x + size, current_y + size};
                DrawCircleSectorLines(center, size, 180, 270, 30, WHITE);
                break;

            case DOWN:
                center = (Vector2){current_x, current_y + size};
                DrawCircleSectorLines(center, size, 270, 360, 30, WHITE);
                break;

            case LEFT:
                center = (Vector2){current_x, current_y};
                DrawCircleSectorLines(center, size, 0, 90, 30, WHITE);
                break;

            case UP:
                center = (Vector2){current_x + size, current_y};
                DrawCircleSectorLines(center, size, 90, 180, 30, WHITE);
                break;
        }

        int next_size = -7;

        if (i < COUNT - 1)
        {
            next_size = numbers[i + 1] * SCALE;
        }

        switch (current_fold)
        {
            case RIGHT:
                current_x += size;
                current_fold = DOWN;
                break;

            case DOWN:
                current_x = min_x;
                current_y += size;
                current_fold = LEFT;
                break;

            case LEFT:
                current_x -= next_size;
                min_x = current_x;
                current_y = min_y;
                current_fold = UP;
                break;

            case UP:
                current_y -= next_size;
                min_y = current_y;
                current_fold = RIGHT;
                break;
        }
    }
}


