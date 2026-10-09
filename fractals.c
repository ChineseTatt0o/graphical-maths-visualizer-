#include "fractals.h"
#include "raylib.h"
#include "visualization.h"
#include "graph.h"
#include <stdbool.h>


static Texture2D fractalTexture;
static int fractalWidth;
static int fractalHeight;

static double centerReal = -0.5;
static double centerImag = 0.0;
static double viewWidth = 4.0;

static const int MAX_ITERATIONS = 100;

static Color GetMandelbrotColor(int iterations)
{
    if (iterations == MAX_ITERATIONS)
    {
        return BLACK;
    }

    float t = (float)iterations / MAX_ITERATIONS;

    unsigned char red = (unsigned char)(255 * t);
    unsigned char green = (unsigned char)(100 * (1.0f - t));
    unsigned char blue = (unsigned char)(255 * (1.0f - t));

    return (Color){red, green, blue, 255};
}

static void RenderMandelbrot(void)
{
    Image image = GenImageColor(
        fractalWidth,
        fractalHeight,
        BLACK
    );

    Color *pixels = (Color *)image.data;

    double viewHeight =
        viewWidth * (double)fractalHeight / fractalWidth;

    double minReal = centerReal - viewWidth / 2.0;
    double minImag = centerImag - viewHeight / 2.0;

    for (int y = 0; y < fractalHeight; y++)//* Calculate the complex number for this pixel. Iterate the Mandelbrot equation. Store the resulting color in the pixel.

    {
        for (int x = 0; x < fractalWidth; x++)
        {
            double cReal =
                minReal + (double)x / fractalWidth * viewWidth;

            double cImag =
                minImag + (double)y / fractalHeight * viewHeight;

            double real = 0.0;
            double imag = 0.0;

            int iterations = 0;

            while (real * real + imag * imag <= 4.0
                   && iterations < MAX_ITERATIONS)
            {
                double newReal =
                    real * real - imag * imag + cReal;

                double newImag =
                    2.0 * real * imag + cImag;

                real = newReal;
                imag = newImag;

                iterations++;
            }

            pixels[y * fractalWidth + x] =
                GetMandelbrotColor(iterations);
        }
    }

    fractalTexture = LoadTextureFromImage(image);
    UnloadImage(image);
}

void InitFractal(int width, int height)
{
    fractalWidth = width;
    fractalHeight = height;

    RenderMandelbrot();
}

void DrawFractal(void)
{
    DrawTexture(fractalTexture, 0, 0, WHITE);
}

void ResetFractal(void)
{
    centerReal = -0.5;
    centerImag = 0.0;
    viewWidth = 4.0;

    UnloadTexture(fractalTexture);
    RenderMandelbrot();
}

void UnloadFractal(void)
{
    UnloadTexture(fractalTexture);
}


void UpdateFractal(void)//cam settings for zoom and re-rendering
{
    float wheel = GetMouseWheelMove();

    bool changed = false;

    if (wheel != 0.0f)
    {
        viewWidth *= (wheel > 0.0f) ? 0.8 : 1.25;
        changed = true;
    }

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
        double viewHeight =
            viewWidth * (double)fractalHeight / fractalWidth;

        centerImag -= viewHeight * 0.1;
        changed = true;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        double viewHeight =
            viewWidth * (double)fractalHeight / fractalWidth;

        centerImag += viewHeight * 0.1;
        changed = true;
    }

    if (IsKeyPressed(KEY_R))
    {
        centerReal = -0.5;
        centerImag = 0.0;
        viewWidth = 4.0;
        changed = true;
    }

    if (changed)
    {
        UnloadTexture(fractalTexture);
        RenderMandelbrot();
    }
}

