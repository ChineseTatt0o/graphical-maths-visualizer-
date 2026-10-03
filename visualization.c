#include "visualization.h"
#include "raylib.h"
#include "graph.h"
#include <math.h>
#define WIDTH 900
#define HEIGHT 600

Color GetGradientColor(float t, Color A, Color B) {

    //creating two color gradients for any color A and B, where t is the normalized value between 0 and 1
    Color color1;
    color1.r = (unsigned char)((1 - t) * A.r + t * B.r);
    color1.g = (unsigned char)((1 - t) * A.g + t * B.g);
    color1.b = (unsigned char)((1 - t) * A.b + t * B.b);
    color1.a = (unsigned char)((1 - t) * A.a + t * B.a);

    // Ensure t is clamped between 0 and 1
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    //changing palette forever to the next color when pressing p
    if (IsKeyDown(KEY_P))
    {
        Color temp = A;
        A = B;
        B = temp;
    }
   
    //and apply the new palette to the color1 forever not just for one frame
    color1.r = (unsigned char)((1 - t) * A.r + t * B.r);
    color1.g = (unsigned char)((1 - t) * A.g + t * B.g);
    color1.b = (unsigned char)((1 - t) * A.b + t * B.b);
    color1.a = (unsigned char)((1 - t) * A.a + t * B.a);
    

    DrawText("hold P: change the palette", WIDTH - 274, 30, 20, WHITE);

    return color1;
}

void TestVisualization() {
    // Example usage of GetGradientColor
    for (float t = 0.0f; t <= 1.0f; t += 0.1f) {
        Color color1 = GetGradientColor(t, YELLOW, GREEN);
        // Here you can use the color for visualization purposes
        // For example, you could draw a rectangle with this color
        DrawRectangle(50 + (int)(t * 400), 50, 40, 40, color1);
        
    }
}

//!to use the color effects activate the visiualization and normalize a value for parameters so it can be transformed to screen






