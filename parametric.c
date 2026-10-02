#include "parametric.h"
#include "graph.h"
#include "raylib.h"
#include <math.h>

void draw_parametric(float t, float a)
{
    for (t = 0; t <= 2 * PI; t += 0.1f)
    {
    float a = 5.0f ; 
    float b ;
    float gama = 20.0f; 
    float x = cos(a*t+gama);
    float y = sin(b*t);
    Vector2 PP = {x, y};
    Vector2 PP_screen = WorldToScreen(PP);
    DrawCircle(PP_screen.x , PP_screen.y , 2, SKYBLUE);
    DrawLine(0.0f, 0.0f, PP_screen.x , PP_screen.y , PURPLE);
    }
}