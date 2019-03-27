#include <iostream>

using namespace std;

template <class T>
class GenStack
{
  public:
    GenStack(); //constructor
    GenStack(int maxSize); //overloading constructor
    ~GenStack(); //deconstructor
    void push(T d);
    void newArray();
    T pop();
    T peek(); //top
    bool isFull();
    bool isEmpty();

    int size;
    int top;
    T *myArray; //declaring pointer to a char
    T *temp;
};

class Analyze
{
  public:
    Analyze();
    ~Analyze();
    void readFile(string location);
    bool checkBalance();
    void outputError();
};

template <class T>
GenStack<T>::GenStack() //defualt constructor
{
  //initialization of default values
  myArray = new T[10]; //"new" allocates memory dynamically on the heap. need to delete memory before you exit program with deconstructor
  size = 10;
  top = -1;
}

template <class T>
GenStack<T>::GenStack(int maxSize)
{
  myArray = new T[maxSize]; //"new" allocates memory dynamically on the heap. need to delete memory before you exit program with deconstructor
  size = maxSize;
  top = -1;
}

template <class T>
GenStack<T>::~GenStack()
{
  delete [] myArray;
  delete [] temp;
}

template <class T>
void GenStack<T>::push(T d)
{
  //neeed to error boundary check
  //add to a new stack of increased size
  if(isFull() != true)
  {
    myArray[++top] = d;
  }
  else
  {
    newArray();
    myArray[++top] = d;
  }
}

template <class T>
void GenStack<T>::newArray()
{
  temp = new T[2*size];
  for (int i = 0; i < size; i++)
  {
    temp[i] = myArray[i];
  }
  size *= 2;
  delete [] myArray;
  myArray = temp;
}

template <class T>
T GenStack<T>::pop()
{
  //error checking, make sure its not isEmpty
  if(isEmpty() != true)
  {
    return myArray[top--];
  }
  else
  {
    cout << "The stack is empty." << endl;
  }
}

template <class T>
T GenStack<T>::peek()
{
  //check if empty
  if(isEmpty() != true)
  {
    return myArray[top];
  }
  else
  {
    cout << "The stack is empty" << endl;
  }
}

template <class T>
bool GenStack<T>::isFull()
{
  return (top == size-1);
}

template <class T>
bool GenStack<T>::isEmpty()
{
  return (top == -1);
}
