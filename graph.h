#ifndef GRAPH_H
#define GRAPH_H
#include "raylib.h"

void init_graph(void);
void draw_graph(float x, float y);
Vector2 WorldToScreen(Vector2 world);//convert world coordinates to screen coordinates
Vector2 ScreenToWorld(Vector2 screen);//convert screen coordinates to world coordinates

#endif // GRAPH_H