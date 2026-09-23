//Math visualizer project

// first exemple, Fibonacci sequence

#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#define WIDTH 900
#define HEIGHT 600
#define SCALE 10

#define COUNT 10

Color colors[] = {
    (Color){255, 0, 0, 255},      // Red
    (Color){0, 255, 0, 255},      // Green
    (Color){0, 0, 255, 255},      // Blue
    (Color){255, 255, 0, 255},    // Yellow
    (Color){255, 0, 255, 255},    // Magenta
    (Color){0, 255, 255, 255},    // Cyan
    (Color){128, 0, 128, 255},    // Purple
    (Color){255, 165, 0, 255},    // Orange
    (Color){128, 128, 128, 255},   // Gray
    (Color){0, 128, 0, 255}       // Dark Green
};


int numbers[COUNT];

enum Fold
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
Vector2 pos;
bool fixed = false;
int current_x, current_y;

void init_fibonacci()
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
    
    int size = numbers[i]*SCALE;

        Color color = colors[i % (sizeof(colors) / sizeof(colors[0]))];
    DrawRectangle(current_x, current_y, size, size, WHITE);
    DrawRectangle(current_x+1, current_y+1, size-2, size-2, color);
    
    Vector2 center = (Vector2){current_x + size, current_y + size};
    
    
    //draw the spiral segment
    Vector2 crnter;
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
        next_size = numbers[i + 1]*SCALE;
        }
      // Update current position and fold direction
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

int numbers[COUNT];
int main(int argc, char *argv[])
{
   InitWindow(WIDTH, HEIGHT, "Fibonacci");
   init_fibonacci();
   SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
    if (!fixed)
    {
        pos = GetMousePosition();
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        fixed = !fixed;
    }
        
        draw_fibonacci(pos.x - 100, pos.y - 100);
        EndDrawing();
    }
    return 0;
}