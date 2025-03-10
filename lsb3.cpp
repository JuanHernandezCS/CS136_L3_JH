#include <iostream>
using namespace std;

// Maximum size of Stack
#define MAX 80

//Stack class. Has functions to push, pop, get top element, and check if stack is empty.
class Stack {
//Current size of the stack
int size;

public:
char a[MAX];

//Initialisation
Stack() {
size = -1;
}

//Push new char into stack if size permits.
bool push(char x) {
if (size >= (MAX - 1)) {
cout<<"Stack Overflow";
return false;
} else {
a[++size] = x;
cout<<x<<" pushed into stack\n";
return true;
}
}

//Pop the topmost char from a non empty stack.
char pop() {
if (size < 0) {
cout<<"Stack Underflow";
return 0;
}
else {
char x = a[size--];
return x;
}
}

//Returns the top element.
char top() {
if (size < 0) {
cout<<"Stack is Empty";
return 0;
}
else {
char x = a[size];
return x;
}
}

//Checks if stack is empty or not.
bool isEmpty() {
return (size < 0);
}
};

//Function to print the main menu options.
void printMainMenu() {
printf("\n------------\n");
printf("Main Menu:-\n");
printf("------------\n");
printf("Press 1: Process an Expression\n");
printf("Press 2: Output Originial Expression\n");
printf("Press 3: Determine if Expression is Balanced\n");
printf("Press 4: Ouput Expressions with Opening and Closing Symbols\n");
printf("Press 5: Exit\n\n");
printf("Enter Your Option (1-5): ");
}

//Function to ask for a new expression.
void showAddExpressionMenu(string &str) {
printf("\nPlease Input The Expression: ");

//Two getlines to discard the trailing "\n" after the main menu choice selection.
getline(cin, str);
//This inputs the actual expression.
getline(cin, str);
if(str.length() > 80) {
printf("Expression can't be more than 80 length. Please try again!! Redirecting to Main Menu!!");
str = "";
return;
}

printf("Expression Added Successfully!!");
}

//Function to return only the symbols present in the expression.
string getSymbolsOnly(string expr) {
string ret = "";
for(char ch: expr) {
if(ch == '(' || ch == '{' || ch == '[' || ch == '<' || ch == ')' || ch == '}' || ch == ']' || ch == '>' || ch == '\'' || ch == '\"')
ret += ch;
else
continue;
}

return ret;
}

//Function to determine if a given expression is balanced or not.
string determineBalancedExpression(string expr) {
//Initialise empty stack
Stack st;
//Get only the symbols from the expression.
expr = getSymbolsOnly(expr);

//Used for finding if the quote (single/double) is an opening or a closing quote.
int singleQuoteCount = 0, doubleQuoteCount = 0;
for(char ch: expr) {
//All opening symbols. For quotes the count will always be divisible by 2 (and we increase the count by 1, while checking the condition).
if( ch == '(' || ch == '{' || ch == '[' || ch == '<' ||
(ch == '\'' && (singleQuoteCount++)%2 == 0) ||
(ch == '\"' && (doubleQuoteCount++)%2 == 0) )
st.push(ch);
//All closing symbols. For quotes the count will be divisible by 2 since the above if will evaluate first and increase the count value by 1.
else if( (ch == ')' && st.top() == '(') || ((ch == '}' && st.top() == '{')) ||
(ch == ']' && st.top() == '[') || (ch == '>' && st.top() == '<') ||
((ch == '\'' && singleQuoteCount%2 == 0 && st.top() == '\'')) ||
((ch == '\"' && doubleQuoteCount%2 == 0 && st.top() == '\"')) )
st.pop();
//If the top in stack is an opening symbol and doesn't match with the closing symbol in ch, then expression in not balanced.
else
return "False";
}

//For cases like -> {[]}(, the initial expression is balanced, but the trailing opening bracket will not be covered by the above loop.
if(st.isEmpty())
return "True";

//Return expression unbalanced if stack is not empty.
return "False";
}

int main()
{
string expr;

//Main Menu Driver
int inp = 0;
while(true) {
printMainMenu();
cin>>inp;

if(inp > 5 || inp <= 0) {
printf("\n==>> Sorry Incorrect Input!! Please Enter A Choice Between 1-5!! Redirecting to Main Menu.\n\n");
continue;
}

if(inp == 1) showAddExpressionMenu(expr);
else if(inp == 2) printf("\nOriginal Expression: %s\n", expr.c_str());
else if(inp == 3) printf("\nIs Expression Balanced: %s\n", determineBalancedExpression(expr).c_str());
else if(inp == 4) printf("\nExpression With Symbols Only: %s\n", getSymbolsOnly(expr).c_str());
else break;
}

return 0;
}
