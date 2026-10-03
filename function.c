#include "function.h"
#include "graph.h"
#include "raylib.h"
#include "visualization.h"
#include <math.h>


//draw the function
void draw_function(float x, float y)
{
   for (x = 1; x <= 10; x += 0.1f)
   {
      //normalized value of x 
      for (float t = 0.0f; t <= 1.0f; t += 0.01f)
      {
    y = x*x;
    Vector2 PP = {x, y};
   Vector2 PP_screen = WorldToScreen(PP);
    DrawLine(0.0f, 0.0f, PP_screen.x , PP_screen.y , GetGradientColor(t, RED, GREEN));
      }
   }
}

