//Math visualizer project

// first exemple, Fibonacci sequence

#include "raylib.h"
#include "fibonacci.h"
#include "graph.h"
#include "function.h"
#include "polar.h"
#include "rose.h"
#include "parametric.h"
#include "fractals.h"
#include "visualization.h"

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
int main(void)
{
    InitWindow(WIDTH, HEIGHT, "MathVis");
    InitFractal(900,600);
    

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        Vector2 cameraoffset = {0.0f, 0.0f};

        UpdateFractal();//update function once per frame

        BeginDrawing();

        ClearBackground(BLACK);


        //!fractals
        DrawFractal();


        draw_graph(0, 0);

        //!polar
        // draw_polar(0, 0);
        

        //!normal function
        // draw_function(0.0, 0.0);

        //!rose
        // draw_rose(0 , 0);
        // DrawText("hold M: increase 'a' , L: decrease 'a'", HEIGHT - 75, 50, 20, WHITE);
        // DrawText("hold K: increase 'n' , J: decrease 'n'", HEIGHT - 75, 70, 20, WHITE);
        // //display the equation of the rose curve
        // DrawText("Equation: r = a * sin(n * theta)", HEIGHT - 30, 90, 20, WHITE);

        //!parametric
        // draw_parametric(0, 0);

        //!visualization
        // TestVisualization();

        
    

        
   
    
        EndDrawing(); 
    }
    UnloadFractal();
    CloseWindow();

    return 0;
}


