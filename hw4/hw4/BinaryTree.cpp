//#include "BinaryTree.h"  I don't need anymore
//Collection one cpp
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class Stack;

template<class T>
class Iterator;
//#include "Stack.h" I don't need anymore

//HEADER OF STACK
#ifndef _STACK_H
#define _STACK_H
template<class T>         // template for struct
struct TreeNode
{
  T value;      // int should be T
  TreeNode<T> *left;               //TreeNode --> TreeNode<T>
  TreeNode<T> *right;

  TreeNode<T>(){
    left = nullptr;
    right = nullptr;
  }
};
template<class T>
struct StackNode
{
  TreeNode<T>* value;
  StackNode<T> *next;           //StackNode --> StackNode<T>
};

template <class T>
class Stack
{
private:
  StackNode<T> *top;
  StackNode<T>* GetTopPointer(Stack<T> myStack);
  
public:
  Stack<T>(void);
  void push(TreeNode<T>*);
  TreeNode<T>* pop();
  bool isEmpty();
};

#endif

// HEADER OF BINARYTREE
#ifndef _BINARYTREE_H
#define _BINARYTREE_H
template <class T>
class BinaryTree
{
 public:
  //Constructor
  BinaryTree();
  //Copy Constructor
  BinaryTree(const BinaryTree<T>&);
  //Destructor
  ~BinaryTree();
  
  // Insertion method
  void insert(T);
  TreeNode<T>* getRoot();
  
  //operators
  //template for operators
  // const BinaryTree& operator= (const BinaryTree& rhs);  before no template
  const BinaryTree<T>& operator= (const BinaryTree<T>& rhs);
  bool operator== (const BinaryTree<T>& rhs);
  bool operator!= (const BinaryTree<T>& rhs);
  void operator+= (const BinaryTree<T>& rhs);
  BinaryTree<T> operator+ (const BinaryTree<T>& rhs);
  void operator+= (T number);
  BinaryTree<T> operator+(T number);
  // since they are friend function we should define as template
  template <typename B>
  friend BinaryTree<B> operator+(B number, const BinaryTree<B>&);
  template <typename B>
  friend ostream& operator<< (ostream&, const BinaryTree<B>&);

 private:
  //The root of the tree
   TreeNode<T>* root;
  //since it is friend function we should define as template
   template <typename B>
   friend class Iterator;
};
// Iterator class
template<class T>
class Iterator{
 public:
  //Constructor
  Iterator();

  void Init(const BinaryTree<T>& );
  bool hasNext();
  TreeNode<T>* Next(); //Actually the same with InOrderNext()
  TreeNode<T>* InOrderNext();
  TreeNode<T>* PreOrderNext();
  
 private:
  TreeNode<T>* myCurrent;
  Stack<T>* stack;
  Stack<T>* stack2;
};

#endif


// CPP OF STACK
//Constructor
template <class T>       // before all function we define as a template <class T>
Stack<T>::Stack()
{
    top=nullptr;
}
template <class T>
StackNode<T>* Stack<T>::GetTopPointer(Stack<T> myStack)
{
    return myStack.top;
}

//Push back elements to the stack
template <class T>
void Stack<T>::push(TreeNode<T>* elmt)
{
    StackNode<T> *newNode;

    newNode = new StackNode<T>;
    newNode->value = elmt;

    if(isEmpty())
    {
        top = newNode;
        newNode->next = nullptr;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }
}
//Pop up elements from the stack
template <class T>
TreeNode<T>* Stack<T>::pop()
{
    StackNode<T> *temp;

    if(!isEmpty())
    {
        TreeNode<T>* elmt = top->value;
        temp = top->next;
        delete top;
        top = temp;
        return elmt;
    }
    return nullptr;
}

//If the stack is empty check function
template <class T>
bool Stack<T>::isEmpty()
{
    return (top==nullptr);
}

//CPP OF BINARYTREE
//Constructor
template <class T>
BinaryTree<T>::BinaryTree(){
  root = nullptr;
}

//Copy Constructor
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& rhs){
  
  root = nullptr;
  
  Iterator<T> iter;
  iter.Init(rhs);
    
  while(iter.hasNext()){
    this->insert(iter.InOrderNext()->value);
  }
}

//Destructor
template <class T>
BinaryTree<T>::~BinaryTree(){
  Iterator<T> iter;
  iter.Init(*this);
    
  while(iter.hasNext()){
    delete iter.InOrderNext();
  }
}
template <class T>
TreeNode<T>* BinaryTree<T>::getRoot(){
  return this->root;
}

//First create the new node with the given value
template <class T>
void BinaryTree<T>::insert(T num) {
  TreeNode<T> *newNode,	// Pointer to a new node
    *nodePtr;	// Pointer to traverse the tree
  
  // Create a new node
  newNode = new TreeNode<T>;
  newNode->value = num;
  newNode->left = newNode->right = nullptr;
  
  if (!root)	// Is the tree empty?
    root = newNode;
  else 
    {
      //we have a root, need to find the location for the next item
      nodePtr = root; 
      while (nodePtr) {
	if (num < nodePtr->value) {
	  if (nodePtr->left)
	    nodePtr = nodePtr->left;
	  else {
	    nodePtr->left = newNode;
	    break;
	  }
	}
	else if (num > nodePtr->value) {
	  if (nodePtr->right)
	    nodePtr = nodePtr->right;
	  else {
	    nodePtr->right = newNode;
	    break;
	  }
	}
	else { //num is not greater or smaller. So it is equal
	  cout << "Duplicate value found in tree.\n";
	  break;
	}
      }		
    }
}

//Operators
template <class T>
const BinaryTree<T>& BinaryTree<T>::operator= (const BinaryTree<T>& rhs){
  if(this!=&rhs)
    {
      this->~BinaryTree();
      this->root = nullptr;
      
      Iterator<T> iter;
      iter.Init(rhs);
      while (iter.hasNext()) {
	this->insert(iter.Next()->value);
      }
    }
  return *this;
}
template <class T>
bool BinaryTree<T>::operator== (const BinaryTree<T>& rhs){
  if(this != &rhs){
    Iterator<T> iter_lhs, iter_rhs;
    iter_lhs.Init(*this);
    iter_rhs.Init(rhs);
    while (iter_lhs.hasNext() && iter_rhs.hasNext()) {
      if(iter_lhs.Next()->value != iter_rhs.Next()->value){
	return false;
      }
    }
    if(iter_lhs.hasNext() || iter_rhs.hasNext()){
      return false;
    }
  }
  return true;
}
template <class T>
bool BinaryTree<T>::operator!= (const BinaryTree<T>& rhs){
  return !operator==(rhs);
}
template <class T>
void BinaryTree<T>::operator+=(const BinaryTree<T>& rhs){
  Iterator<T> iter;
  iter.Init(rhs);
  while (iter.hasNext()) {
    this->insert(iter.Next()->value);
  }
}
template <class T>
BinaryTree<T> BinaryTree<T>::operator+(const BinaryTree<T>& rhs){
  BinaryTree<T> temp(*this);
  temp += rhs;
  return temp;
}
template <class T>
void BinaryTree<T>::operator+=(T number){
  this->insert(number);
}
template <class T>
BinaryTree<T> BinaryTree<T>::operator+(T number){
  BinaryTree<T> temp(*this);
  temp.insert(number);
  return temp;
}

// they are friends function we change their template T
template <class T>
BinaryTree<T> operator+(T number, const BinaryTree<T>& tree){
  BinaryTree<T> temp(tree);
  temp.insert(number);
  return temp;
}
template <class T>
ostream & operator<< (ostream & os, const BinaryTree<T> & rhs)
{
  Iterator<T> iter;
  iter.Init(rhs);
  while (iter.hasNext()) {
    os << iter.Next()->value << " ";
  }
  os << endl;
  return os;
}


/*
 *  ITERATOR CLASS
 */

//Constructor
template <class T>
Iterator<T>::Iterator()
  :myCurrent(nullptr), stack(nullptr), stack2(nullptr)
{}
template <class T>
void Iterator<T>::Init(const BinaryTree<T> &tree)
{
  myCurrent = tree.root;
  stack = new Stack<T>();
}
template <class T>
bool Iterator<T>::hasNext()
{
  return (!stack->isEmpty() || myCurrent != nullptr);
}
template <class T>
TreeNode<T>* Iterator<T>::Next()
{
  while (myCurrent != nullptr) {
    stack->push(myCurrent);
    myCurrent = myCurrent->left;
  }
  
  myCurrent = stack->pop();
  TreeNode<T>* node = myCurrent;
  myCurrent = myCurrent->right;
  
  return node;
}
template <class T>
TreeNode<T>* Iterator<T>::InOrderNext()
{
  while (myCurrent != nullptr) {
    stack->push(myCurrent);
    myCurrent = myCurrent->left;
  }
  
  myCurrent = stack->pop();
  TreeNode<T>* node = myCurrent;
  myCurrent = myCurrent->right;
  
  return node;
}


//This is just to show. Iterative post-order is much more complex.
template <class T>
TreeNode<T>* Iterator<T>::PreOrderNext()
{
  if(myCurrent->left != nullptr || myCurrent->right != nullptr){
    stack->push(myCurrent);
  }
  
  TreeNode<T>* node = myCurrent;

  if(myCurrent->left == nullptr && myCurrent->right == nullptr){
    if(!stack->isEmpty()){
      myCurrent = stack->pop();
    }
    else{
      myCurrent = nullptr;
      return node;
    }
    if(myCurrent->right){
      myCurrent = myCurrent->right;
    }
    else{
      while(!myCurrent->right){
	myCurrent = stack->pop();
	myCurrent = myCurrent->right;
      }
    }   
  }
  else if(myCurrent->left){
    myCurrent = myCurrent -> left;
  }
  else if(myCurrent->right){
    myCurrent = stack->pop();
    myCurrent = myCurrent -> right;
  }

  return node;
}


  
