#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include "Stack.h"

using namespace std;

class BinaryTree
{
 public:
  //Constructor
  BinaryTree();
  //Copy Constructor - TODO in .cpp file
  BinaryTree(const BinaryTree&);
  //Destructor
  ~BinaryTree();
  
  // Insertion method
  void insert(int);
    
 // operations
    BinaryTree & operator=(const BinaryTree & rhs);
    friend const bool operator==(const BinaryTree &rhs, const BinaryTree &);
    friend const bool operator!=(const BinaryTree &rhs, const BinaryTree &);
    BinaryTree operator+=(const BinaryTree &rhs);
    BinaryTree operator+=(const int num);
    friend const BinaryTree operator+(int, const BinaryTree &rhs);
    friend const BinaryTree operator+(const BinaryTree &rhs, int num);
    friend const BinaryTree operator+(const BinaryTree &rhs, const BinaryTree &);
    friend ostream & operator << (ostream &output, const BinaryTree &rhs);

private:
  //The root of the tree
  TreeNode* root;

  friend class Iterator;
    void dhelper(TreeNode* root);
    void ihelper(int key, TreeNode *root);
};

class Iterator{
public:
  //Constructor
  Iterator();
  
  void Init(const BinaryTree& );
  bool hasNext();
  TreeNode* Next();
  
private:
  TreeNode* myCurrent;
  Stack* stack;
};

#endif
