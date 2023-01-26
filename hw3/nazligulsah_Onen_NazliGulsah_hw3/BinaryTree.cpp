#include "BinaryTree.h"
#include <iostream>

using namespace std;

//Constructor
BinaryTree::BinaryTree(){
  root = nullptr;
}

//Copy Constructor
BinaryTree::BinaryTree(const BinaryTree& rhs){
  //TODO: Implement deep copy constructor
  //You may make use of Iterator class
   root = nullptr;
   Iterator it;
   it.Init(rhs);
   while (it.hasNext())
     insert(it.Next()->value);
}

// Helper fonksion for destructor
// Recersion fonksion
void BinaryTree::dhelper(TreeNode* root) {
    if (root != nullptr) {
        dhelper(root->left);
        dhelper(root->right);
        delete root;
    }
}


//Destructor
BinaryTree::~BinaryTree(){
  dhelper(root);
}
// ihelper for insert fonksion
void BinaryTree::ihelper(int key, TreeNode *root)
{
  if(key < root->value)
  {
    if(root->left!=NULL)
     ihelper(key, root->left);
    else
    {
      root->left=new TreeNode;
      root->left->value=key;
      root->left->left=NULL;    //Sets the left child of the child node to null
      root->left->right=NULL;   //Sets the right child of the child node to null
    }
  }
  else if(key > root->value)
  {
    if(root->right!=NULL)
      ihelper(key, root->right);
    else
    {
      root->right=new TreeNode;
      root->right->value=key;
      root->right->left=NULL;  //Sets the left child of the child node to null
      root->right->right=NULL; //Sets the right child of the child node to null
    }
  }
  else{ // key == value
      cout << "Dublicate value found in tree." << endl;
  }
    
}

void BinaryTree::insert(int num) {
  //TODO: Implement insert function for BinaryTree
 // if root is nullptr create a new treenode and set root to num
    if(root == nullptr){  // if(!root)
      root=new TreeNode;
      root->value=num;
      root->left= nullptr;  // left child nullptr
      root->right=nullptr; // right child nullptr
    }
      
    else{
     ihelper(num, root);  //now insert the num 
    }
}

//Operators
//Give the implementations of operators in here either as free function or member function

ostream & operator << (ostream &output,const BinaryTree &rhs) {
    Iterator it;
    it.Init(rhs);
    while(it.hasNext())
        output << it.Next()->value << " ";
    output << endl;
    return output;
}
BinaryTree & BinaryTree::operator=(const BinaryTree &rhs){
    BinaryTree node(rhs); // since rhs binarytree member i cannot write rhs.swap(*this)
    swap(node.root,root);
    return *this;
}
const bool operator==( BinaryTree const & rhs, BinaryTree const &lhs)  {
  Iterator right;
  Iterator left;
  right.Init(rhs);
  left.Init(lhs);
    // until they have a next element
  while(right.hasNext() && left.hasNext()){
        // check equality
        if(left.Next()-> value != right.Next()->value){
            return false;
        }
         }
        // if the element numbers is not equal return false
        if(right.hasNext() || left.hasNext()){
            return false;
        }
    // they have same number of element and their element are same orderly
   return true;
}
const bool operator!=(const BinaryTree & lhs, const BinaryTree & rhs){
        // inverse of bool == operator
            return !(operator==(rhs,lhs));
}
// add a tree
BinaryTree BinaryTree::operator+=(const BinaryTree &rhs){
    Iterator it;
    it.Init(rhs);
    while(it.hasNext());
    this -> insert(it.Next()->value);
      return *this;
}
// add a number
 BinaryTree BinaryTree::operator+=(const int num){
    int inum= num;
    this-> insert(num);
        return *this;
}

// adding num to tree
  const BinaryTree operator+(int num, const BinaryTree &rhs) {
    BinaryTree add = rhs;
    add.insert(num);
    return add;
}
// adding tree to num
 const BinaryTree operator+(const BinaryTree & rhs, int num) {
    return operator+(num,rhs);
    
}
        
// adding two tree
const BinaryTree operator+(const BinaryTree & lhs, const BinaryTree & rhs2){
    Iterator it;
    BinaryTree add = lhs;
    it.Init(rhs2);
    while(it.hasNext()){
        add.insert(it.Next()->value);
    }
    return add;
}

/*
 *  ITERATOR CLASS
 */

//Constructor
Iterator::Iterator()
  :myCurrent(nullptr), stack(nullptr)
{}

void Iterator::Init(const BinaryTree &tree)
{
  myCurrent = tree.root;
  stack = new Stack();
}

//Returns true if tree has more nodes to explore
bool Iterator::hasNext()
{
  //TODO: Implement a function to see if there is more nodes to iterate over.
    return(!stack->isEmpty() || myCurrent != nullptr);
    // mycurrent or stack which is pointer should be nullptr
}

//Next node to explore
TreeNode* Iterator::Next()   // iterates to the next smallest element in BST
{
   while (myCurrent != NULL){
      stack->push(myCurrent);
      myCurrent = myCurrent->left;   // left the smaller
    }
    // after find samllest next node update mycurrent
    myCurrent = stack->pop();  // delete mycurrent
    TreeNode *curr = myCurrent;
    myCurrent = myCurrent->right; // right of mycurrent now new mycurrent
  return curr;
}




// ALTERNATIVE NEXT ITERATOR
/*TreeNode* Iterator::Next()   // iterates to the next smallest element in BST
{
TreeNode currValue; // a need to initilazed otherwise taking uninizilation warning                              for curr
 TreeNode* curr  = &currValue;  //  a pointer which points to treenode
 
 myCurrent = stack->pop();
 curr -> value = myCurrent-> value;  //  stack.top()->right
  myCurrent = myCurrent -> right;
while (myCurrent != NULL){
  stack->push(myCurrent);
  myCurrent = myCurrent->left;   // left the smaller
}
}*/
