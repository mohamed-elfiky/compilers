#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std ;
const char num = '1';
const char opsy='5' ;
const char iden='9' ;
map<string, double >lookup;
////////////////////////////////////////////////////////
void error (string s)
{
  throw runtime_error (s);
}
/////////////////////////////////////////////////////////
struct Token
{
    char kind;
	double value;
	char alpha ;
    //string ident;
    Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val){ }
    Token(char alph , char ki):alpha(alph), kind(ki){ }
    //Token(char ch , string  id) :kind(ch) ,ident(id){ }
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
lookup["M"]=10;
cout<<eval("5.5+12*sin(M/2)+2.2^4;");
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
        t = get_token();if(t.kind!=')'){ error(" missing )");}// should return error here
        t = get_token();
        break;
}
case '^':
        left=pow(left,factor());
        t = get_token();
        break;
case '1':
        left= t.value;
        t = get_token();
        break;
//////////////////////////////////////////////////////////////////////////////
case '5':
        {

                            string s;
                            char ch=t.alpha;
                            cout<<t.alpha<<endl;
                            while(true)
                            {
                            s+=ch;
                            math_exp>>ch;
                            cout<<s<<endl;
                            if(s== "sin" )
                                        {
                                          double d =expression();
                                          d=sin(d);
                                          math_exp>>ch;
                                          return d;
                                         }
                            else if (s== "cos" )
                                             {
                                            double d =expression();
                                            cout<<d<<"low"<<endl;
                                            d=sin(d);
                                            math_exp>>ch;

                                            return d;
                                            }
                            else if (s=="tan" )
                                        {
                                          double d =expression();
                                          cout<<d<<"low"<<endl;
                                          d=tan(d);
                                          math_exp>>ch;

                                          return d;
                                         }

                            else if (s=="log" )
                                        {
                                          double d =expression();
                                          cout<<d<<"low"<<endl;
                                          d=log(d);
                                          math_exp>>ch;

                                          return d;
                                         }

                            else if (s=="sqrt" )
                                         {
                                          double d =expression();
                                          cout<<d<<"low"<<endl;
                                          d=sqrt(d);
                                          math_exp>>ch;

                                          return d;
                                         }

                        }
                }

/////////////////////////////////////////////////////////////////////////

case '9':         //identifier
         {
         double d=t.value;
         char ch;
         math_exp>>ch;
         return d;

         }

/////////////////////////////////////////////////////////////////////////
 default:
        math_exp.putback(t.kind);
        return left;

    }
  }
 }
///////////////////////////////////////////////////

//////////////////////////////////////////////////
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
        {
        double d = factor() ;
        if(d==0) error("division by zero");
        left =left/ d;
        t = get_token();
        break;
        }
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
                cout<<"here5"<<endl;
                left += term();
                t = get_token();
                break;
        case '-':
                left -= term();
                t = get_token();
                break;
         default:
                math_exp.putback(t.kind);
                //cout<<left<<endl;
                return left;
		}
}
}
Token get_token()
{

    cout<<"here"<<endl;

	char ch;
    math_exp>> ch;
	if (ch== '(') 		return Token(ch);
	else if (ch== ')')	return Token(ch);
	else if (ch== '+')	return Token(ch);
	else if (ch== '-')	return Token(ch);
	else if (ch== '*')	return Token(ch);
	else if (ch== '/')	return Token(ch);
	else if (ch== '%')  return Token(ch);
 	else if (ch== '^')	return Token(ch);
	else if (ch== '=')	return Token(ch);
    else if(
      (ch=='.')||
	  (ch=='0')||
	  (ch=='1')||
	  (ch=='2')||
	  (ch=='3')||
	  (ch=='4')||
	  (ch=='5')||
	  (ch=='6')||
	  (ch=='7')||
	  (ch=='8')||
	  (ch=='9'))
            {	math_exp.putback(ch);
                double val;
                math_exp >> val;
                return Token(num,val);
            }

           else if(isalpha(ch))
            {
                            char ch1;
                            math_exp>>ch1;      //lookahead
                            if(isalpha(ch1))
                            {
                            math_exp.putback(ch1);
                            math_exp.putback(ch);
                            math_exp>>ch;
                            return Token(ch,opsy);
                            }


                            else // idendtifier is called
                            {
                            math_exp.putback(ch1);
                            math_exp.putback(ch);
                            string k;
                            k =ch;

                            double d =lookup[k];
                            return Token(iden,d);
                            }

            }
else
    return 0;
}







