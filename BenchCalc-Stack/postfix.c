#include "postfix.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char **args, int nargs)
{
    struct double_stack *stackOp = double_stack_new(nargs);
   // memset(stackOp->items, 0, (nargs) * sizeof(double));
    double op1, op2, result;
    for (int i = 0; i < nargs; i++)
    {
        if (((args[i][0] >= '0') && (args[i][0] <= '9')) || ((args[i][1] >= '0') && (args[i][1] <= '9')))
        {
            double_stack_push(stackOp, atof(args[i]));
        }
        else if (args[i][0] == '+' || args[i][0] == '-' || args[i][0] == 'X' || args[i][0] == '/' || args[i][0] == '^')
        {
            op2 = double_stack_pop(stackOp);
            op1 = double_stack_pop(stackOp);
            switch (args[i][0])
            {
            case '/':
                result = op1 / op2;
                double_stack_push(stackOp, result);
                break;

            case 'X':
                result = op2 * op1;
                double_stack_push(stackOp, result);
                break;

            case '+':
                result = op2 + op1;
                double_stack_push(stackOp, result);
                break;

            case '-':
                result = op1 - op2;
                double_stack_push(stackOp, result);
                break;

            case '^':
                result = pow(op1, op2);
                double_stack_push(stackOp, result);
                break;
            }
        }
    }
    return double_stack_pop(stackOp);
}