#include "raylib.h"
#include "polar.h"
#include "graph.h"
#include "visualization.h"
#include <math.h>


void draw_polar(float r, float theta)
{
   r = 1 +cos(theta);
   for (theta = 0; theta <= 2 * PI; theta += 0.1f)
   {
    r = 1 +cos(theta);
    float x = r * cos(theta);
    float y = r * sin(theta);
    Vector2 PP = {x, y};
    Vector2 PP_screen = WorldToScreen(PP);
    DrawLine(0.0f, 0.0f, PP_screen.x , PP_screen.y , GREEN);
   }
}
