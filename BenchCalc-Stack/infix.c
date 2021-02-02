#include "infix.h"

int precedence(char operator)
{
  if(operator == '+' || operator == '-'){
     return 1;
  }
  else if (operator == 'X' || operator == '/'){
    return 2;
  }
    
  else if (operator == '^'){
    return 3;
  }
  else{
    return 0;
  }
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char **args, int nargs) {
 struct double_stack *stackOp = double_stack_new(nargs - 1);
  memset(stackOp->items, 0, (nargs - 1) * sizeof(double));

  char  **postfixExp = malloc(sizeof(char *) * nargs);
  int j = 0;
  for (int i = 0; i < nargs; i++)
  {
    if ((args[i][0] >= '0' && args[i][0] <= '9')||(args[i][1] >= '0' && args[i][1] <= '9')){
      postfixExp[j] = args[i];
      j++;
    }
    else if (args[i][0] == '(')
    {
      double_stack_push(stackOp, args[i][0]);
    }
    else if (args[i][0] == '+' || args[i][0] == '-' || args[i][0] == 'X' || args[i][0] == '/' || args[i][0] == '^')
    {
      while (precedence((char)stackOp ->items[stackOp -> top]) >= precedence(args[i][0]))
      {
          postfixExp[j] = malloc(sizeof(char) * 2);
          postfixExp[j][0] = (char) double_stack_pop(stackOp);
          postfixExp[j][1] = '\0';
          j++;
        }
      double_stack_push(stackOp, args[i][0]);
    }
    else if (args[i][0] == ')')
    {
      while ((char)(stackOp ->items[stackOp -> top]) != '(')
      {
          postfixExp[j] = malloc(sizeof(char) * 2);
          postfixExp[j][0] = (char) double_stack_pop(stackOp);
          postfixExp[j][1] = '\0';
          j++;
      }
      double_stack_pop(stackOp);
    }
  }
  while (stackOp->top != 0)
  {
    double temp = double_stack_pop(stackOp);
    postfixExp[j] = malloc(sizeof(char) * 2);
    postfixExp[j][0] = (char)temp;
    postfixExp[j][1] = '\0';
    j++;
  }

  double postfixExp_result = evaluate_postfix_expression(postfixExp, j);
  return postfixExp_result;
}