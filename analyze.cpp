#include "analyze.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

GenStack <char> stack(10);
string mystring;
string filename; //if user wants to input another filename after commandline
int useCase = 0; //case to determine error message
int lineNumber = 1;

Analyze::Analyze()
{

}

Analyze::~Analyze()
{

}

void Analyze::readFile(string location)
{
  int nums = 1;
  ::mystring = ""; //creating empty string for after first use
  string line;
  ifstream file;
  while(nums == 1)
  {
    file.open(location, ios::in);
    if (file.is_open())
    {
      while(!file.eof())
      {
        getline(file, line);
        string st = line.substr(0, line.size()-1);
        ::mystring.append(st);
        ::mystring.append("|"); //parsing lines apart in the string
      }
      nums = 0;
    }
    else
    {
      cout << "not a valid file path" << endl;
      cout << "insert another filepath: ";
      cin >> location;
    }
  }
}

bool Analyze::checkBalance()
{
  int size = ::mystring.size();
  for (int i = 0; i < size; i++)
  {
    if(::mystring[i] == '(' || ::mystring[i]  == '{' || ::mystring[i] == '[') //pushing open brackets into stack
    {
      ::stack.push(::mystring[i]);
    }
    else if(::mystring[i] == ')')
    {
      if(::stack.isEmpty() == true || ::stack.peek() != '(') //returning false if no match
      {
        ::useCase = 1;
        return false;
      }
      else
      {
        ::stack.pop(); //removing if match is correct
      }
    }
    else if(::mystring[i] == '}')
    {
      if(::stack.isEmpty() == true || ::stack.peek() != '{') //returning false if no match
      {
        ::useCase = 2;
        return false;
      }
      else
      {
        ::stack.pop(); //removing if match is correct
      }
    }
    else if(::mystring[i] == ']')
    {
      if(::stack.isEmpty() == true || ::stack.peek() != '[') //returning false if no match
      {
        ::useCase = 3;
        return false;
      }
      else
      {
        ::stack.pop(); //removing if match is correct
      }
    }
    else if(::mystring[i] == '|')
    {
      ::lineNumber++;
    }
    else continue;
  }
  if(::stack.isEmpty() == true)
  {
    return true; //syntax is correct if there is an empty stack
  }
  else
  {
    ::useCase = 4;
    return false; //syntax is incorrect if there are still elements in stack
  }
}

void Analyze::outputError()
{
  if(checkBalance() == true)
  {
    char answer;
    int num = 1;
    while(num == 1)
    {
      cout << "syntax is correct." << endl;
      cout << "would you like to insert another file path? (y/n): "; //prompting user for another filename
      cin >> answer;
      if(answer == 'y')
      {
        cout << "enter the name of the file: ";
        cin >> ::filename;
        readFile(::filename);
        outputError();
        num = 0;
      }
      else if(answer == 'n')
      {
        num = 0;
      }
      else
      {
        cout << "not a valid option" << endl;
      }
    }
  }
  else //output error cases. gives element on top of the stack and what is expected to be on top of stack
  {
    if(::useCase == 1)
    {
      if(::stack.isEmpty() == true)
      {
        cout << "Line: " << lineNumber << " expected ( as match, found no matching parenthesis" << endl;
      }
      else
      {
        cout << "Line: " << lineNumber << " expected ( as match, found " << ::stack.peek() << endl;
      }
    }
    else if(::useCase == 2)
    {
      if(::stack.isEmpty() == true)
      {
        cout << "Line: " << lineNumber << " expected { as match, found no matching parenthesis" << endl;
      }
      else
      {
        cout << "Line: " << lineNumber << " expected { as match, found " << ::stack.peek() << endl;
      }
    }
    else if(::useCase == 3)
    {
      if(::stack.isEmpty() == true)
      {
        cout << "Line: " << lineNumber << " expected [ as match, found no matching parenthesis" << endl;
      }
      else
      {
        cout << "Line: " << lineNumber << " expected [ as match, found " << ::stack.peek() << endl;
      }
    }
    else if(::useCase == 4)
    {
      cout << "reached end of file: missing }" << endl;
    }
  }
}
