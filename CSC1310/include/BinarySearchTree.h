#if !defined BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <cmath>
#include "ListArray.h"
#include "TreeNode.h"
#include "BinaryTreeIterator.h"
#include "String_.h"

namespace CSC1310
{
template < class T >
class BinarySearchTree
{
   private:
      TreeNode<T>* root;
      int sze;
      void destroyItem(TreeNode<T>* tNode);
      void destroy();

      TreeNode<T>* insertItem(TreeNode<T>* tNode, T* item);
      TreeNode<T>* removeItem(TreeNode<T>* tNode, CSC1310::String* sk);
      TreeNode<T>* removeNode(TreeNode<T>* tNode);
      TreeNode<T>* removeLeftMost(TreeNode<T>* tNode);
      T* findLeftMost(TreeNode<T>* tNode);

      TreeNode<T>* getRootNode();
      void setRootNode(TreeNode<T>* tNode);
      int getHeight(TreeNode<T>* tNode);
      bool isBalanced(TreeNode<T>* tNode);
	  
	  void minimize(T** items, int first, int last);
      T** toArrayComplete();
      bool traverseComplete(T** items, int array_length, TreeNode<T>* tNode, int index);
      void minimizeComplete(T** items, int first, int last);

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (CSC1310::String* key, T* item);
	  
	  void checkInorderSuccessor(TreeNode<T>* tNode, CSC1310::String* sk, CSC1310::ListArray<T>* items);

   public:
      BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (CSC1310::String* key, T* item));
      ~BinarySearchTree();

      bool isEmpty();
      void makeEmpty();

      T* retrieve(CSC1310::String* search_key);
	  CSC1310::ListArray<T>* retrieveDuplicates(CSC1310::String* search_key);
      void insert(T* item);
      void remove(CSC1310::String* search_key);

      BinaryTreeIterator<T>* iterator();
      T* getRootItem();
      int getHeight();
      bool isBalanced();
	  
	  BinarySearchTree<T>* minimize();
      BinarySearchTree<T>* minimizeComplete();

      T** toArray();
};

template < class T >
void BinarySearchTree<T>::checkInorderSuccessor(TreeNode<T>* tNode, CSC1310::String* sk, CSC1310::ListArray<T>* items)
{
	while(tNode->getLeft() != NULL)
	{
		tNode = tNode->getLeft();
	}
	
	T* node_item = tNode->getItem();
	int comp = (*compare_keys) (sk, node_item);
	if (comp == 0)
	{
		items->add(node_item);
		TreeNode<T>* right = tNode->getRight();
		if (right != NULL)
		{
			checkInorderSuccessor(right, sk, items);
		}
	}
}

template < class T >
CSC1310::ListArray<T>* BinarySearchTree<T>::retrieveDuplicates(CSC1310::String* sk)
{
	CSC1310::ListArray<T>* items = new CSC1310::ListArray<T>();
	TreeNode<T>* tNode = getRootNode();

	//find the first match
	while (tNode != NULL)
	{
		T* node_item = tNode->getItem();
		int comp = (*compare_keys) (sk, node_item);

		if (comp == 0)
		{
				items->add(node_item);
				
				//if there is another item with the same sk, it will be the inorder successor of this node
				TreeNode<T>* right = tNode->getRight();
				if (right != NULL)
				{
					checkInorderSuccessor(right, sk, items);
				}
				
				break;
		}
		else if (comp < 0)
		{
				tNode = tNode->getLeft();
		}
		else
		{
				tNode = tNode->getRight();
		}
	}
	
	return items;
}

template < class T >
void BinarySearchTree<T>::insert(T* item)
{
   root = insertItem(root, item);
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::insertItem(TreeNode<T>* tNode, T* item)
{
   TreeNode<T>* subtree;
   if (tNode == NULL)
   { 
      sze++;
      return new TreeNode<T>(item);
   }

   T* node_item = tNode->getItem();
   int comp = (*compare_items) (item, node_item);

   //FIFO for duplicates
   if (comp >= 0)
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);
   }
   else
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
   }
   
   return tNode;
}

template < class T >
T* BinarySearchTree<T>::retrieve(CSC1310::String* sk)
{
   TreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_item = tNode->getItem();
      int comp = (*compare_keys) (sk, node_item);

      if (comp == 0)
      {
			return tNode->getItem();
      }
      else if (comp < 0)
      {
			tNode = tNode->getLeft();
      }
	  else
	  {
			tNode = tNode->getRight();
	  }
   }

   return NULL; //item is not in the tree
}

template < class T >
void BinarySearchTree<T>::remove(CSC1310::String* sk)
{
   root = removeItem(root, sk);
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeItem(TreeNode<T>* tNode, CSC1310::String* sk)
{
   if (tNode == NULL)
   { 
      return tNode;  //take no action, item not present
   }

   T* node_items = tNode->getItem();
   int comp = (*compare_keys) (sk, node_items);

   if (comp == 0)
   {
      sze--;
      return removeNode(tNode);  //delete the node
   }
   else if (comp < 0)
   {
      TreeNode<T>* subtree = removeItem(tNode->getLeft(), sk);
      tNode->setLeft(subtree);
      return tNode;
   }
   else
   {
      TreeNode<T>* subtree = removeItem(tNode->getRight(), sk);
      tNode->setRight(subtree);
      return tNode;
   }
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T>* tNode)
{
   if (tNode->getLeft() == NULL && tNode->getRight() == NULL)
   {
      delete tNode;
      return NULL;
   }
   else if (tNode->getLeft() == NULL)
   {
      TreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   }
   else if (tNode->getRight() == NULL)
   {
      TreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }
   else 
   {
      T* replace = findLeftMost(tNode->getRight());
      tNode->setItem(replace);
      TreeNode<T>* subtree = removeLeftMost(tNode->getRight());
      tNode->setRight(subtree);
      return tNode;
   }
}

template < class T >
T* BinarySearchTree<T>::findLeftMost(TreeNode<T>* tNode)
{
   while (tNode->getLeft() != NULL)
   {
      tNode = tNode->getLeft();
   }

   return tNode->getItem();
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeLeftMost(TreeNode<T>* tNode)
{
   if (tNode->getLeft() == NULL)
   {
      TreeNode<T>* right = tNode->getRight();
      delete tNode;
      return right;
   }
   else
   {
      TreeNode<T>* subtree = removeLeftMost(tNode->getLeft());
      tNode->setLeft(subtree);
      return tNode;
   }
}

template < class T >
T** BinarySearchTree<T>::toArray()
{
   T** items = new T*[sze];

   BinaryTreeIterator<T>* iter = iterator();
   iter->setInorder();
   int i = 0;
   while(iter->hasNext())
   {
      items[i] = iter->next();
      i++;
   }
   delete iter;

   return items;
}

template < class T >
int BinarySearchTree<T>::getHeight()
{
   return getHeight(getRootNode());
}

template < class T >
int BinarySearchTree<T>::getHeight(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       int left = getHeight(tNode->getLeft());
       int right = getHeight(tNode->getRight());

       if (left >= right)
       {
           return left + 1;
       }
       else
       {
          return right + 1;
       }
   }
}

template < class T >
bool BinarySearchTree<T>::isBalanced()
{
    bool bal = isBalanced(root);
    return bal;
}

template < class T >
bool BinarySearchTree<T>::isBalanced(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return true;
   }

   TreeNode<T>* left = tNode->getLeft();
   TreeNode<T>* right = tNode->getRight();

   bool left_bal = isBalanced(left);
   if (left_bal == false)
   {
      return false;
   }

   bool right_bal = isBalanced(right);
   if (right_bal == false)
   {
      return false;
   }

   int lh = getHeight(left);
   int rh = getHeight(right);
   if (abs(lh - rh) > 1)
   {
      return false;
   }

   return true;
}

template < class T >
BinarySearchTree<T>::BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (CSC1310::String* key, T* item))
{
   root = NULL;
   sze = 0;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
BinarySearchTree<T>::~BinarySearchTree()
{
   destroy();
}

template < class T >
void BinarySearchTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void BinarySearchTree<T>::destroyItem(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool BinarySearchTree<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
void BinarySearchTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::getRootNode()
{
   return root;
}

template < class T >
void BinarySearchTree<T>::setRootNode(TreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T* BinarySearchTree<T>::getRootItem()
{
   T* rootItem = root->getItem();
   return rootItem;
}

template < class T >
BinaryTreeIterator<T>* BinarySearchTree<T>::iterator()
{
   return new BinaryTreeIterator<T>(root);
}

template < class T >
BinarySearchTree<T>* BinarySearchTree<T>::minimize()
{
   T** items = toArray();
   BinarySearchTree<T>* bst = new BinarySearchTree<T>(compare_items, compare_keys);
   bst->minimize(items, 0, sze - 1);
   delete[] items;
   return bst;
}

template < class T >
void BinarySearchTree<T>::minimize(T** items, int first, int last)
{
   if (first <= last)
   {
      //the rounding ensures that mid is included in the count (it is necessary)
      int mid = first + (last - first)/2;

      T* root = items[mid];  //found the next element to insert into the tree

      insert(root);  //insert the next element into the tree
      minimize(items, first, mid - 1);  //repeat for left subtree
      minimize(items, mid + 1, last);   //repeat for right subtree
   }
}

template < class T >
BinarySearchTree<T>* BinarySearchTree<T>::minimizeComplete()
{
   T** items = toArray();
   BinarySearchTree<T>* bst = new BinarySearchTree<T>(compare_items, compare_keys);
   bst->minimizeComplete(items, 0, sze - 1);
   delete[] items;
   return bst;
}

template < class T >
void BinarySearchTree<T>::minimizeComplete(T** items, int first, int last)
{
   double TOL = 0.0001;
   //the log base e of 2 is 0.69314718
   //one over 0.69314718 = 1.442695042
   double log_factor = 1.442695042;

   if (first <= last)
   {
      //the rounding ensures that mid is included in the count (it is necessary)
      int mid = (int) ((last + first)/2.0 + 0.5);  //int mid = (last + first + 1)/2 to bias the midpoint to the right

      //create a complete binary search tree
      //start at mid and gradually move to the right to find the next element to insert into the tree
      if (first < last)
      {  
         double k_left = log(mid - first + 1)*log_factor;
         double int_k_left = (int) (k_left + 0.5);
         double k_right = log(last - mid + 1)*log_factor;
         double int_k_right = (int) (k_right + 0.5);

         //keep searching for spot where the number of elements to the left of mid is 2^k - 1 (a full tree)
         //which means the number of elements to the left of mid including mid is 2^k 
         //or the number of elements to the right of mid is 2^k
         //compare the direct log computation and the computation cast to an int
         //to determine if the direct computation is an int
         while (fabs(k_left - int_k_left) > TOL && fabs(k_right - int_k_right) > TOL)
         {
            mid++;
            k_left = log(mid - first + 1)*log_factor;
            int_k_left = (int) (k_left + 0.5);
            k_right = log(last - mid + 1)*log_factor;
            int_k_right = (int) (k_right + 0.5);
         }
      }

      T* root = items[mid];  //found the next element to insert into the tree

      insert(root);  //insert the next element into the tree
      minimizeComplete(items, first, mid - 1);  //repeat for left subtree
      minimizeComplete(items, mid + 1, last);   //repeat for right subtree
   }
}

//the test for completeness involves traversing the reference based BST and inserting the items in an array
//the left and right child of a given node are placed in the array using the index formula for complete binary trees
//the formulas should never result in going out of bounds of the array if the ref based BST is complete
template < class T >
bool BinarySearchTree<T>::traverseComplete(T** items, int array_length, TreeNode<T>* tNode, int index)
{
   if (tNode != NULL)
   {
      if (index >= array_length)
      {
         return false;  //return false (the ref based BST is not complete)
      }

      items[index] = tNode->getItem();

      int left = 2*index + 1;
      int right = left + 1;

      bool bl = traverseComplete(items, array_length, tNode->getLeft(), left);
      bool br = false;

      if (bl)
      {
         br = traverseComplete(items, array_length, tNode->getRight(), right);
      }

      return (bl && br); //both left and right subtrees are complete
   }

   return true;  //return true
}

template < class T >
T** BinarySearchTree<T>::toArrayComplete()
{
   T** items = new T*[sze];
   bool result = traverseComplete(items, sze, getRootNode(), 0);

   if (result)
   {
      return items;
   }
   else
   {
      delete[] items;
      return NULL;
   }
}

}

#endif
