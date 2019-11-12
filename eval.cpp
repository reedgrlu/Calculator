#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK
#include <iostream>
using namespace std;



int main () {
    Scanner S(cin);
    Token t;

    Stack<Token> numstack, opstack;  // 2x Stacks of type Token
    
    
    t = S.getnext();


    //while T is not EOF or opstack is not empty
    while (t.tt != eof || !opstack.isEmpty()) {
        
        //if T is a number
        if(t.tt == integer){ 
            numstack.push(t);
            t = S.getnext();
        
        //if T is left parenthesis
        }else if(t.tt == lptok){
            opstack.push(t);
            t = S.getnext();
        
        //if T is right parenthesis
        }else if(t.tt == rptok){
            
            //if top of operator stack is left parenthesis
            if(opstack.peek().tt == lptok){
                opstack.pop();
                t = S.getnext();
            
            //else pop top 2 numbers and top operator, and perform operation
            }else{
                Token num1 = numstack.pop();
                Token num2 = numstack.pop();
                Token op = opstack.pop();
                Token result;
                
                //if operation token type is "+", then perform operation with the integer values in each number token
                if(op.tt == pltok){
                    result.val = num1.val + num2.val;
                    
                    //output the expression and result
                    cout << num2.val << op.text << num1.val << " is " << result.val << endl;
                
                //if operation token type is "-", then perform operation with the integer values in each number token
                }else if(op.tt == mitok){
                    result.val = num2.val - num1.val;
                    
                    //output the expression and result
                    cout << num2.val << op.text << num1.val << " is " << result.val << endl;
                
                //if operation token type is "*", then perform operation with the integer values in each number token
                }else if(op.tt == asttok){
                    result.val = num1.val * num2.val;
                    
                    //output the expression and result
                    cout << num2.val << op.text << num1.val << " is " << result.val << endl;
                
                //if operation token type is "/", then perform operation with the integer values in each number token
                }else if(op.tt == slashtok){
                    result.val = num2.val / num1.val;
                    
                    //output the expression and result
                    cout << num2.val << op.text << num1.val << " is " << result.val << endl;
                };
                
                //push result token onto numstack for further operation
                numstack.push(result);
            };
        
        //if token type is "+", "-", or end of file
        }else if(t.tt == pltok || t.tt == mitok || t.tt == eof){
            
            //if opertator stack is nonempty and top element is "+" token, then pop the top 2 elements from numstack and perform operation
            if(!opstack.isEmpty() && opstack.peek().tt == pltok){
            
                Token num1 = numstack.pop();
                Token num2 = numstack.pop();
                Token op = opstack.pop();
                Token result;

                result.tt = integer;
                result.val = num1.val + num2.val;

                //push result token onto numstack, and output result
                numstack.push(result);
                cout << num2.val << op.text << num1.val << " is " << result.val << endl;
            
            //if opertator stack is nonempty and top element is "-" token, then pop the top 2 elements from numstack and perform operation
            }else if(!opstack.isEmpty() && opstack.peek().tt == mitok){
                Token num1 = numstack.pop();
                Token num2 = numstack.pop();
                Token op = opstack.pop();
                Token result;

                result.tt = integer;
                result.val = num2.val - num1.val;

                numstack.push(result);
                cout << num2.val << op.text << num1.val << " is " << result.val << endl;
            
            //if opertator stack is nonempty and top element is "*" token, then pop the top 2 elements from numstack and perform operation
            }else if(!opstack.isEmpty() && opstack.peek().tt == asttok){
                Token num1 = numstack.pop();
                Token num2 = numstack.pop();
                Token op = opstack.pop();
                Token result;

                result.tt = integer;
                result.val = num1.val * num2.val;

                numstack.push(result);
                cout << num2 << op.text << num1 << " is " << result.val << endl;
            
            //if opertator stack is nonempty and top element is "/" token, then pop the top 2 elements from numstack and perform operation
            }else if(!opstack.isEmpty() && opstack.peek().tt == slashtok){
                Token num1 = numstack.pop();
                Token num2 = numstack.pop();
                Token op = opstack.pop();
                Token result;

                result.tt = integer;
                result.val = num2.val / num1.val;

                numstack.push(result);
                cout << num2 << op.text << num1 << " is " << result.val << endl;
            
            //if none of above statements are met, push token to operator stack
            }else{
                opstack.push(t);
                t = S.getnext();
            };

        //if token is "*" or "/"   
        }else if(t.tt == asttok || t.tt == slashtok){
            
            //if operator stack is not empty and top element is "*", pop the top 2 elements from numstack and perform operation
            if(!opstack.isEmpty() && opstack.peek().tt == asttok){
                Token num1 = numstack.pop();
                Token num2 = numstack.pop();
                Token op = opstack.pop();
                Token result;

                result.tt = integer;
                result.val = num1.val * num2.val;

                numstack.push(result);
                cout << num2.val << op.text << num1.val << " is " << result.val << endl;
            
            //if operator stack is not empty and top element is "/", pop the top 2 elements from numstack and perform operation
            }else if(!opstack.isEmpty() && opstack.peek().tt == slashtok){
                Token num1 = numstack.pop();
                Token num2 = numstack.pop();
                Token op = opstack.pop();
                Token result;

                result.tt = integer;
                result.val = num2.val / num1.val;

                numstack.push(result);
                cout << num2.val << op.text << num1.val << " is " << result.val << endl;
            
            //otherwise, push token to operator stack and get next token
            }else{
                opstack.push(t);
                t = S.getnext();
            };
        
        //if input token is not an appropriate input, output "error" and get next token
        }else if(t.tt == errtok){
            cout << "error" << endl;
            t = S.getnext();
        };

    };

    return 0;
}


