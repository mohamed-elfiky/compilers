/*mohamed elfiky*/
/*recursive decent algorithm*/
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
using namespace std ;
const char number = '8';
//////////////////////////////////////////////
struct Token
{
    char kind;
	double value;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
};
///////////////////////////////////////////////////////////
stringstream math_exp;
Token get_token();
double expression();
double factor();
double term();
double eval(string) ;
////////////////////////////////////////////////////////////
int main()
{
cout<<eval("1+2/2;");
return 0;
}
////////////////////////////////////////////
double eval(string k)
{
math_exp<<k;
return expression();
}
//////////////////////////////////////////////////
double factor()
{
Token t = get_token();
double left;


while(true)
{
switch (t.kind)
{
case '(':
{
        left = expression();
        t = get_token();if(t.kind!=')')return 0;
        t = get_token();
        break;
}
case '^':
        left=pow(left,factor());
        t = get_token();
        break;
case '8':
        left= t.value;
        t = get_token();
        break;
default:
        math_exp.putback(t.kind);
        return left;
}
}
}
///////////////////////////////////////////////////
double term()
{
double left = factor();
Token t = get_token();
while (true)
{
switch (t.kind)
{
case '*':
        left =left*factor();
        t = get_token();
        break;
case '/':
        left =left/ factor();
        t = get_token();
        break;

default:
        math_exp.putback(t.kind);
        return left;
}
}
}
/////////////////////////////////////////////////////
double expression()
{
double left = term();
Token t = get_token();
while(true)
{
		switch(t.kind)
		{
		case '+':
                left += term();
                t = get_token();
                break;
        case '-':
                left -= term();
                t = get_token();
                break;
         default:
                math_exp.putback(t.kind);
                return left;
		}
}
}
Token get_token()
{

	char ch;
    math_exp>> ch;
	switch (ch)
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '^':
	case '=':
		return Token(ch);
	case '.':
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
            {	math_exp.putback(ch);
                double val;
                math_exp >> val;
                return Token(number,val);
            }

    }
}
