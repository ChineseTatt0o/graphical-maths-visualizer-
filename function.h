#ifndef FUNCTION_H
#define FUNCTION_H
#include "tinyexpr.h"

//!tinyexpr stuff
typedef struct
{
    char *text;
    te_expr *expression;
    double x;
    int errorPosition;
} MathFunction;

void FunctionInit(MathFunction *function);

int FunctionSet(MathFunction *function, const char *text);

double FunctionEvaluate(MathFunction *function, double x);

const char *FunctionGetText(const MathFunction *function);

int FunctionGetErrorPosition(const MathFunction *function);

void FunctionUnload(MathFunction *function);

//!function stuff
// void init_function(void);
// void draw_function(float x, float y);

#endif // FUNCTION_H