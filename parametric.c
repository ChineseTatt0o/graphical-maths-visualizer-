#include "parametric.h"
#include "graph.h"
#include "raylib.h"
#include "visualization.h"
#include <math.h>

void draw_parametric(float k, float a)
{
    for (k = 0; k <= 2 * PI; k += 0.1f)
    {
    float a = 5.0f ; 
    float b ;
    float gama = 20.0f; 
    float x = cos(a*k+gama);
    float y = sin(b*k);

//normalized value of k to be between 0 and 1 so that it can be used to get rgb colors from the gradient
float t = (k - 0) / (2 * PI - 0);

    Vector2 PP = {x, y};
    Vector2 PP_screen = WorldToScreen(PP);
    DrawCircle(PP_screen.x , PP_screen.y , 2, SKYBLUE);
    DrawLine(0.0f, 0.0f, PP_screen.x , PP_screen.y , GetGradientColor(t, RED, GREEN));
    }
}