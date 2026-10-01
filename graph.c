//mathematical coordinate system
#include "graph.h"
#include "raylib.h"
#define WIDTH 900
#define HEIGHT 600
#define SCALE 50.0f


//mini cam for the graph, to allow for panning and zooming
Vector2 cameraoffset = {0.0f, 0.0f};


//initialize the graph
void init_graph(void)
{
    Vector2 origin = {0.0f, 0.0f};
    
}
//draw the graph
void draw_graph(float x, float y )
{
     //grid lines (50 pixels apart)
    for (int i = 0; i < WIDTH; i += SCALE)
    {
        DrawLine(i, 0, i, HEIGHT,BLUE); //draw vertical grid lines
    }
    for (int i = 0; i < HEIGHT; i += SCALE)
    {
        DrawLine(0, i, WIDTH, i, BLUE); //draw horizontal grid lines
    }
    //draw the coordinate system
   DrawLine(0, HEIGHT/2, WIDTH, HEIGHT/2, WHITE); //draw x-axis
   DrawLine(WIDTH/2, 0, WIDTH/2, HEIGHT, WHITE); //draw y-axis

//draw a point at (3,4) to test the coordinate conversion
// Vector2 p = {3.0f, 4.0f};
// Vector2 p_screen = WorldToScreen(p);
// DrawCircle(p_screen.x, p_screen.y, 10, RED);

//select a point with the mouse and draw it on the graph
    Vector2 mousePos = GetMousePosition();
    Vector2 mouseWorld = ScreenToWorld(mousePos);
    DrawCircle(mousePos.x, mousePos.y, 5, RED); //draw a point at the mouse position
    DrawText(TextFormat("Mouse Position: (%.2f, %.2f)", mouseWorld.x, mouseWorld.y), 10, 10, 20, WHITE); //display the mouse position in world coordinates
    DrawText(TextFormat("Camera Offset: (%.2f, %.2f)", cameraoffset.x, cameraoffset.y), 10, 30, 20, WHITE); //display the camera offset
}

//convert world coordinates to screen coordinates
Vector2 WorldToScreen(Vector2 world)
{
    world.x = world.x * SCALE + WIDTH / 2 + cameraoffset.x;
    world.y = - world.y * SCALE + HEIGHT / 2 + cameraoffset.y;
    return world;
}
//convert screen coordinates to world coordinates
Vector2 ScreenToWorld(Vector2 screen)
{
   screen.x = (screen.x - WIDTH / 2 - cameraoffset.x) / SCALE;
   screen.y = -(screen.y - HEIGHT / 2 - cameraoffset.y) / SCALE;
    return screen;
}
