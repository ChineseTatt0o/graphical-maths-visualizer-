//!mathematical coordinate system

#include "graph.h"
#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
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

    //reset the cam to the origin if the R key is pressed
    if (IsKeyPressed(KEY_R))
    {
        cameraoffset.x = 0.0f;
        cameraoffset.y = 0.0f;
    }

    //zoom in and out with the mouse wheel
    if (GetMouseWheelMove() > 0)
    {
        cameraoffset.x -= GetMousePosition().x * 0.1f;
        cameraoffset.y -= GetMousePosition().y * 0.1f;
    }
    else if (GetMouseWheelMove() < 0)
    {
        cameraoffset.x += GetMousePosition().x * 0.1f;
        cameraoffset.y += GetMousePosition().y * 0.1f;
    }

    //pan the camera with the arrow keys
    if (IsKeyDown(KEY_LEFT))
    {
        cameraoffset.x += 10.0f;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        cameraoffset.x -= 10.0f;
    }
    if (IsKeyDown(KEY_UP))
    {
        cameraoffset.y += 10.0f;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        cameraoffset.y -= 10.0f;
    }


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

 //ui
    Vector2 mousePos = GetMousePosition();
    Vector2 mouseWorld = ScreenToWorld(mousePos);
    DrawCircle(mousePos.x, mousePos.y, 5, RED); //draw a point at the mouse position
    DrawText(TextFormat("Mouse Position: (%.2f, %.2f)", mouseWorld.x, mouseWorld.y), 10, HEIGHT - 50, 20, WHITE); //display the mouse position in world coordinates down the screen
    DrawText(TextFormat("Camera Offset: (%.2f, %.2f)", cameraoffset.x, cameraoffset.y), 10, HEIGHT - 30, 20, WHITE); //display the camera offset down the screen
    DrawText("R: Reset Camera", WIDTH - 170, 10, 20, WHITE);

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
