#include "rose.h"
#include "graph.h"
#include "raylib.h"
#include "visualization.h"
#include  <math.h>

void draw_rose(float r, float theta)
{
    for (theta = 0; theta <= 2 * PI; theta += 0.1f)
    {
     //making "a" interactive to increase and decrease it value when pressing m key and l
     float a;
     if (IsKeyDown(KEY_M))
     {
         a += 0.1f;
     }
     else if (IsKeyDown(KEY_L))
     {
         a -= 0.1f;
     }
     //making "n" interactive to increase and decrease it value when pressing k key and j
     float n;
        if (IsKeyDown(KEY_K))
        {
            n += 1.0f;
        }
        else if (IsKeyDown(KEY_J))
        {
            n -= 1.0f;
        } 
    //normalizing the value of theta to be between 0 and 1 so that it can be used to get rgb colors from the gradient
    float t = (theta - 0) / (2 * PI - 0);
    
     r =  a * sin(n * theta);
     float x = r * cos(theta);
     float y = r * sin(theta);
     Vector2 PP = {x, y};
     Vector2 PP_screen = WorldToScreen(PP);
     DrawLine(0.0f, 0.0f, PP_screen.x , PP_screen.y , GetGradientColor(t, RED, GREEN));
    DrawCircle(PP_screen.x , PP_screen.y , 2, RED);
    }
}