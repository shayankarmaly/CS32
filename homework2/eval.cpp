/*#include <iostream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

bool fin(const bool values[], string& postfix);

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    postfix = "";
    
    stack<char> stackOp;
    
    int pTracker = 0;
    
    
    int numCounter = 0;
    
    for (int k = 0; k < infix.size(); k++)
    {
        switch (infix[k])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                int ind = k;
                while (ind > 0 && infix[ind - 1] == ' ')
                    ind--;
                if (ind > 0 && isdigit(infix[ind - 1]))
                    return 1;
                
                numCounter++;
                postfix += infix[k];
                break;
            }
            case '(':
            {
                int ind = k;
                while (ind > 0 && infix[ind - 1] == ' ')
                    ind--;
                if (ind > 0 && isdigit(infix[ind - 1]))
                    return 1;
                
                pTracker++;
                stackOp.push(infix[k]);
                break;
            }
            case '!':
            {
                stackOp.push(infix[k]);
                break;
            }
            case ')':
            {
                int ind = k;
                while (ind < infix.size() && infix[ind + 1] == ' ')
                    ind++;
                if (ind < infix.size() && isdigit(infix[ind + 1]))
                    return 1;
                
                pTracker--;
                while (! stackOp.empty() && stackOp.top() != '(')
                {
                    postfix += stackOp.top();
                    stackOp.pop();
                }
                
                if (!stackOp.empty())
                    stackOp.pop();
                break;
            }
            case '&':
            case '|':
            {
                int ind = k;
                while (ind > 0 && (infix[ind - 1] == ' ' || infix[ind - 1] == ')'))
                    ind--;
                if (ind == 0 || ! isdigit(infix[ind - 1]))
                {
                    return 1;
                }
                
                ind =k;
               
                while (ind < infix.size() && (infix[ind + 1] == ' ' || infix[ind + 1] == '(' || infix[ind + 1] == '!'))
                    ind++;
                if (ind == infix.size() || ! isdigit(infix[ind + 1]))
                {
                    return 1;
                }
                while (! stackOp.empty() && ! (stackOp.top() == '('))
                {
                    if (infix[k] == '&')
                    {
                        if (stackOp.top() == '|')
                            break;
                    }
                    else if (infix[k] == '!')
                    {
                        if (stackOp.top() == '|' || stackOp.top() == '&')
                            break;
                    }
                    postfix += stackOp.top();
                    stackOp.pop();
                }
                stackOp.push(infix[k]);
                break;
            }
        }
    }
    
    if (pTracker != 0 || numCounter == 0)
        return 1;
    
    while (! stackOp.empty())
    {
        postfix += stackOp.top();
        stackOp.pop();
    }
    
    result = fin(values, postfix);
    return 0;
}

bool fin(const bool values[], string& postfix)
{
    stack<bool> stackOp;
    
    for (int ind = 0; ind < postfix.size(); ind++)
    {
        if (isdigit(postfix[ind]))
        {
            int total = postfix[ind] - '0';
            stackOp.push(values[total]);
        }
        else if (postfix[ind] == '!')
        {
            bool op1 = stackOp.top();
            stackOp.pop();
            op1 = !op1;
            stackOp.push(op1);
        }
        else
        {
            bool op2 = stackOp.top();
            stackOp.pop();
            bool op1 = stackOp.top();
            stackOp.pop();
            bool end;
            if (postfix[ind] == '&')
            {
                if (op1 == true && op2 == true)
                    end = true;
                else
                    end = false;
            }
            else if (postfix[ind] == '|')
            {
                if (op1 == false && op2 == false)
                    end = false;
                else
                    end = true;
            }
            stackOp.push(end);
        }
    }
    return stackOp.top();
}

int main()
        {
            bool ba[10] = {
              //  0      1      2      3      4      5      6      7      8      9
                true,  true,  true,  false, false, false, true,  false, true,  false
            };
            string pf;
            bool answer;
            assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
            assert(evaluate("8|", ba, pf, answer) == 1);
            assert(evaluate(" &6", ba, pf, answer) == 1);
            assert(evaluate("4 5", ba, pf, answer) == 1);
            assert(evaluate("01", ba, pf, answer) == 1);
            assert(evaluate("()", ba, pf, answer) == 1);
            assert(evaluate("()4", ba, pf, answer) == 1);
            assert(evaluate("2(9|8)", ba, pf, answer) == 1);
            assert(evaluate("2(&8)", ba, pf, answer) == 1);
            assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
            assert(evaluate("x+5", ba, pf, answer) == 0);
            assert(evaluate("", ba, pf, answer) == 1);
            assert(evaluate("2|3|4", ba, pf, answer) == 0
                                   &&  pf == "23|4|"  &&  answer);
            assert(evaluate("2|(3|4)", ba, pf, answer) == 0
                                   &&  pf == "234||"  &&  answer);
            assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
                                   &&  pf == "43!03&&|"  &&  !answer);
            assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
            ba[2] = false;
            ba[9] = true;
            assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
            assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
            cout << "Passed all tests" << endl;
        }
*/