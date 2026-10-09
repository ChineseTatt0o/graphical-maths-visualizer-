#include "julia.h"
#include "graph.h"
#include "raylib.h"
#include "visualization.h"

#include <stdbool.h>
#include <stdlib.h>

static Texture2D juliaTexture;
static int juliaWidth;
static int juliaHeight;
static bool juliaInitialized = false;

static const int MAX_ITERATIONS = 150;

static double centerReal = 0.0;
static double centerImag = 0.0;
static double viewWidth = 4.0;

// Fixed complex constant: c = cReal + cImag*i
static double cReal = -0.7;
static double cImag = 0.27015;

static Color GetJuliaColor(int iterations)
{
    if (iterations == MAX_ITERATIONS)
    {
        return BLACK;
    }

    float t = (float)iterations / MAX_ITERATIONS;

    unsigned char red = (unsigned char)(255.0f * t);
    unsigned char green = (unsigned char)(100.0f * (1.0f - t));
    unsigned char blue = (unsigned char)(255.0f * (1.0f - t));

    return (Color){red, green, blue, 255};
}

static void RenderJulia(void)
{
    if (juliaWidth <= 0 || juliaHeight <= 0)
    {
        return;
    }

    Image image = GenImageColor(juliaWidth, juliaHeight, BLACK);
    Color *pixels = (Color *)image.data;

    double viewHeight =
        viewWidth * (double)juliaHeight / juliaWidth;

    double minReal = centerReal - viewWidth / 2.0;
    double minImag = centerImag - viewHeight / 2.0;

    for (int y = 0; y < juliaHeight; y++)
    {
        for (int x = 0; x < juliaWidth; x++)
        {
            // The pixel determines the initial z value.
            double real =
                minReal + (double)x / juliaWidth * viewWidth;

            double imag =
                minImag + (double)y / juliaHeight * viewHeight;

            int iterations = 0;

            // c remains fixed for every pixel.
            while (real * real + imag * imag <= 4.0 &&
                   iterations < MAX_ITERATIONS)
            {
                double newReal =
                    real * real - imag * imag + cReal;

                double newImag =
                    2.0 * real * imag + cImag;

                real = newReal;
                imag = newImag;

                iterations++;
            }

            pixels[y * juliaWidth + x] =
                GetJuliaColor(iterations);
        }
    }

    // Replace the old texture when re-rendering.
    Texture2D newTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    if (juliaInitialized)
    {
        UnloadTexture(juliaTexture);
    }

    juliaTexture = newTexture;
    juliaInitialized = true;
}

void InitJulia(int width, int height)
{
    juliaWidth = width;
    juliaHeight = height;

    RenderJulia();
}

void UpdateJulia(void)
{
    bool changed = false;
    float wheel = GetMouseWheelMove();

    // Zoom with the mouse wheel.
    if (wheel != 0.0f)
    {
        viewWidth *= (wheel > 0.0f) ? 0.8 : 1.25;

        if (viewWidth < 0.00001)
        {
            viewWidth = 0.00001;
        }

        if (viewWidth > 10.0)
        {
            viewWidth = 10.0;
        }

        changed = true;
    }

    double viewHeight =
        viewWidth * (double)juliaHeight / juliaWidth;

    // Pan with the arrow keys.
    if (IsKeyPressed(KEY_LEFT))
    {
        centerReal -= viewWidth * 0.1;
        changed = true;
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        centerReal += viewWidth * 0.1;
        changed = true;
    }

    if (IsKeyPressed(KEY_UP))
    {
        centerImag -= viewHeight * 0.1;
        changed = true;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        centerImag += viewHeight * 0.1;
        changed = true;
    }

    // Change the real component of c.
    if (IsKeyPressed(KEY_A))
    {
        cReal -= 0.01;
        changed = true;
    }

    if (IsKeyPressed(KEY_D))
    {
        cReal += 0.01;
        changed = true;
    }

    // Change the imaginary component of c.
    if (IsKeyPressed(KEY_W))
    {
        cImag += 0.01;
        changed = true;
    }

    if (IsKeyPressed(KEY_S))
    {
        cImag -= 0.01;
        changed = true;
    }

    if (IsKeyPressed(KEY_R))
    {
        centerReal = 0.0;
        centerImag = 0.0;
        viewWidth = 4.0;

        cReal = -0.7;
        cImag = 0.27015;

        changed = true;
    }

    // Avoid rendering the entire image unless needed.
    if (changed)
    {
        RenderJulia();
    }
}

void DrawJulia(void)
{
    if (juliaInitialized)
    {
        DrawTexture(juliaTexture, 0, 0, WHITE);
    }

    // Draw UI after the fractal so the text stays visible.
    DrawText("Julia Set", 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("c = %.3f + %.3fi", cReal, cImag),
             10, 35, 18, RAYWHITE);

    DrawText("Wheel: Zoom | Arrows: Pan | WASD: Change c ",
             10, 60, 16, RAYWHITE);
}

void ResetJulia(void)
{
    centerReal = 0.0;
    centerImag = 0.0;
    viewWidth = 4.0;

    cReal = -0.7;
    cImag = 0.27015;

    RenderJulia();
}

void UnloadJulia(void)
{
    if (juliaInitialized)
    {
        UnloadTexture(juliaTexture);
        juliaInitialized = false;
    }
}