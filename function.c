#include "function.h"
#include "raylib.h"
#include "tinyexpr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//!tinyexpr stuff
static char *CopyText(const char *text)
{
    size_t length = strlen(text);

    char *copy = malloc(length + 1);

    if (copy == NULL)
    {
        return NULL;
    }

    memcpy(copy, text, length + 1);

    return copy;
}

void FunctionInit(MathFunction *function)
{
    function->text = NULL;
    function->expression = NULL;
    function->x = 0.0;
    function->errorPosition = 0;
}

int FunctionSet(MathFunction *function, const char *text)
{
    te_variable variables[] =
    {
        { "x", &function->x }
    };

    int errorPosition = 0;

    te_expr *newExpression = te_compile(
        text,
        variables,
        1,
        &errorPosition
    );

    if (newExpression == NULL)
    {
        function->errorPosition = errorPosition;
        return 0;
    }

    char *newText = CopyText(text);

    if (newText == NULL)
    {
        te_free(newExpression);
        function->errorPosition = 0;
        return 0;
    }

    if (function->expression != NULL)
    {
        te_free(function->expression);
    }

    free(function->text);

    function->expression = newExpression;
    function->text = newText;
    function->errorPosition = 0;

    return 1;
}

double FunctionEvaluate(MathFunction *function, double x)
{
    if (function->expression == NULL)
    {
        return 0.0;
    }

    function->x = x;

    return te_eval(function->expression);
}

const char *FunctionGetText(const MathFunction *function)
{
    if (function->text == NULL)
    {
        return "";
    }

    return function->text;
}

int FunctionGetErrorPosition(const MathFunction *function)
{
    return function->errorPosition;
}

void FunctionUnload(MathFunction *function)
{
    if (function->expression != NULL)
    {
        te_free(function->expression);
    }

    free(function->text);

    function->expression = NULL;
    function->text = NULL;
    function->x = 0.0;
    function->errorPosition = 0;
}

//!function stuff
// //initialize the function
// void init_function(void)
// {
    
// }

// //draw the function
// void draw_function(float x, float y)
// {
//     //draw the function at the given coordinates
//     //for example, draw a point at (x,y)
//     DrawCircle(x, y, 5, RED);
// }

