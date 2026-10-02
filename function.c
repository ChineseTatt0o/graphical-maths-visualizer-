#include "function.h"
#include "graph.h"
#include "raylib.h"
#include <math.h>


//draw the function
void draw_function(float x, float y)
{
   for (x = 1; x <= 10; x += 0.1f)
   {
    y = x*x;
    Vector2 PP = {x, y};
   Vector2 PP_screen = WorldToScreen(PP);
    DrawLine(0.0f, 0.0f, PP_screen.x , PP_screen.y , RED);
   }
}

