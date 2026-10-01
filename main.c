//Math visualizer project

// first exemple, Fibonacci sequence

#include "raylib.h"
#include "tinyexpr.h"
#include "fibonacci.h"
#include "graph.h"
#include "function.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 900
#define HEIGHT 600

//! fibonacci sequence
// int main(void)
// {
//     InitWindow(WIDTH, HEIGHT, "Fibonacci");
    

//     init_fibonacci();

//     SetTargetFPS(60);

//     bool fixed = false;
//     Vector2 pos = {0};

//     while (!WindowShouldClose())
//     {
//         BeginDrawing();

//         ClearBackground(BLACK);

//         if (!fixed)
//         {
//             pos = GetMousePosition();
//         }

//         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//         {
//             fixed = !fixed;
//         }

//         draw_fibonacci(pos.x - 100, pos.y - 100);

//         EndDrawing();
//     }

//     CloseWindow();

//     return 0;
// }


//! graph
// int main(void)
// {
//     InitWindow(WIDTH, HEIGHT, "graph");
    

//     init_graph();

//     SetTargetFPS(60);


//     while (!WindowShouldClose())
//     {
//         BeginDrawing();

//         ClearBackground(BLACK);

//         draw_graph(0, 0);

//         EndDrawing();
//     }

//     CloseWindow();

//     return 0;
// }

//! function
#define MAX_FORMULA_LENGTH 128

int main(void)
{
    InitWindow(
        WIDTH,
        HEIGHT,
        "Raylib Function Visualizer"
    );

    SetTargetFPS(60);

    MathFunction function;
    FunctionInit(&function);

    char inputText[MAX_FORMULA_LENGTH] = "sin(x)";
    int inputLength = (int)strlen(inputText);

    bool editing = true;
    bool lastFormulaWasValid = true;

    FunctionSet(&function, inputText);

    while (!WindowShouldClose())
    {
        // Type characters into the formula input.
        if (editing)
        {
            int character = GetCharPressed();

            while (character > 0)
            {
                if (character >= 32 &&
                    character <= 125 &&
                    inputLength < MAX_FORMULA_LENGTH - 1)
                {
                    inputText[inputLength] = (char)character;
                    inputLength++;

                    inputText[inputLength] = '\0';
                }

                character = GetCharPressed();
            }

            // Remove one character with Backspace.
            if (IsKeyPressed(KEY_BACKSPACE) && inputLength > 0)
            {
                inputLength--;

                inputText[inputLength] = '\0';
            }

            // Save and compile the typed function.
            if (IsKeyPressed(KEY_ENTER))
            {
                lastFormulaWasValid = FunctionSet(
                    &function,
                    inputText
                );

                if (lastFormulaWasValid)
                {
                    editing = false;
                }
            }
        }

        // Start editing again with E.
        if (!editing && IsKeyPressed(KEY_E))
        {
            editing = true;
        }

        BeginDrawing();

        ClearBackground((Color){ 20, 22, 30, 255 });

        // -----------------------------
        // Title and instructions
        // -----------------------------
        DrawText(
            "Function Visualizer",
            25,
            20,
            30,
            RAYWHITE
        );

        DrawText(
            "Type a formula, then press ENTER. Press E to edit again.",
            25,
            60,
            18,
            LIGHTGRAY
        );

        // -----------------------------
        // Formula input box
        // -----------------------------
        Rectangle inputBox =
        {
            25,
            100,
            700,
            48
        };

        DrawRectangleRec(
            inputBox,
            (Color){ 35, 40, 55, 255 }
        );

        DrawRectangleLinesEx(
            inputBox,
            2,
            editing ? SKYBLUE : GRAY
        );

        DrawText(
            "f(x) =",
            38,
            112,
            24,
            RAYWHITE
        );

        DrawText(
            inputText,
            125,
            112,
            24,
            YELLOW
        );

        // Draw a simple text cursor while typing.
        if (editing)
        {
            int textWidth = MeasureText(inputText, 24);

            DrawText(
                "|",
                125 + textWidth,
                112,
                24,
                YELLOW
            );
        }

        // Display formula status.
        if (lastFormulaWasValid)
        {
            DrawText(
                TextFormat(
                    "Active function: %s",
                    FunctionGetText(&function)
                ),
                25,
                160,
                18,
                GREEN
            );
        }
        else
        {
            DrawText(
                TextFormat(
                    "Invalid formula near character %d",
                    FunctionGetErrorPosition(&function)
                ),
                25,
                160,
                18,
                RED
            );

            DrawText(
                "Your previous valid graph is still shown.",
                25,
                185,
                18,
                LIGHTGRAY
            );
        }

        // -----------------------------
        // Graph area
        // -----------------------------
        int graphLeft = 50;
        int graphTop = 230;
        int graphWidth = WIDTH - 100;
        int graphHeight = HEIGHT - 280;

        float originX = graphLeft + graphWidth / 2.0f;
        float originY = graphTop + graphHeight / 2.0f;

        float scaleX = 65.0f;
        float scaleY = 65.0f;

        DrawRectangleLines(
            graphLeft,
            graphTop,
            graphWidth,
            graphHeight,
            DARKGRAY
        );

        // X axis
        DrawLine(
            graphLeft,
            (int)originY,
            graphLeft + graphWidth,
            (int)originY,
            GRAY
        );

        // Y axis
        DrawLine(
            (int)originX,
            graphTop,
            (int)originX,
            graphTop + graphHeight,
            GRAY
        );

        // Draw small grid lines.
        for (int x = (int)originX; x < graphLeft + graphWidth; x += (int)scaleX)
        {
            DrawLine(
                x,
                graphTop,
                x,
                graphTop + graphHeight,
                (Color){ 45, 48, 60, 255 }
            );
        }

        for (int x = (int)originX; x > graphLeft; x -= (int)scaleX)
        {
            DrawLine(
                x,
                graphTop,
                x,
                graphTop + graphHeight,
                (Color){ 45, 48, 60, 255 }
            );
        }

        for (int y = (int)originY; y < graphTop + graphHeight; y += (int)scaleY)
        {
            DrawLine(
                graphLeft,
                y,
                graphLeft + graphWidth,
                y,
                (Color){ 45, 48, 60, 255 }
            );
        }

        for (int y = (int)originY; y > graphTop; y -= (int)scaleY)
        {
            DrawLine(
                graphLeft,
                y,
                graphLeft + graphWidth,
                y,
                (Color){ 45, 48, 60, 255 }
            );
        }

        // -----------------------------
        // Draw y = f(x)
        // -----------------------------
        Vector2 previousPoint = { 0 };
        bool hasPreviousPoint = false;

        for (int screenX = graphLeft;
             screenX < graphLeft + graphWidth;
             screenX++)
        {
            double mathX = (screenX - originX) / scaleX;

            double mathY = FunctionEvaluate(
                &function,
                mathX
            );

            if (!isfinite(mathY))
            {
                hasPreviousPoint = false;
                continue;
            }

            Vector2 currentPoint =
            {
                (float)screenX,
                originY - (float)mathY * scaleY
            };

            bool pointIsTooFarAway =
                currentPoint.y < graphTop - 1000 ||
                currentPoint.y > graphTop + graphHeight + 1000;

            if (pointIsTooFarAway)
            {
                hasPreviousPoint = false;
                continue;
            }

            // Avoid lines drawn across discontinuities such as 1/x at x = 0.
            if (hasPreviousPoint &&
                fabsf(currentPoint.y - previousPoint.y) < 250.0f)
            {
                DrawLineV(
                    previousPoint,
                    currentPoint,
                    GREEN
                );
            }

            previousPoint = currentPoint;
            hasPreviousPoint = true;
        }

        DrawText(
            "Examples: x^2     sin(x)     cos(x)*2     sqrt(x)     1/x     pi*x^2",
            25,
            HEIGHT - 30,
            18,
            LIGHTGRAY
        );

        EndDrawing();
    }

    FunctionUnload(&function);

    CloseWindow();

    return 0;
}
