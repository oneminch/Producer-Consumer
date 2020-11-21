#if !defined NULL
	#define NULL 0
#endif

#if !defined TREE_NODE
#define TREE_NODE

namespace CSC1310
{
template < class T >
class TreeNode 
{
   private:
      TreeNode<T>* left;
      TreeNode<T>* right;
      T* item;

   public:
      TreeNode(T* item);
      ~TreeNode();

      TreeNode<T>* getLeft();
      TreeNode<T>* getRight();
      T* getItem();

      void setLeft(TreeNode<T>* tNode);
      void setRight(TreeNode<T>* tNode);
      void setItem(T* item);
};

template < class T >
TreeNode<T>::TreeNode(T* itm)
{
   left = NULL;
   right = NULL;
   item = itm;
}

template < class T >
TreeNode<T>::~TreeNode()
{}

template < class T >
TreeNode<T>* TreeNode<T>::getLeft()
{
   return left;
}

template < class T >
TreeNode<T>* TreeNode<T>::getRight()
{
   return right;
}

template < class T >
T* TreeNode<T>::getItem()
{
   return item;
}

template < class T >
void TreeNode<T>::setLeft(TreeNode<T>* l)
{
   left = l;
}

template < class T >
void TreeNode<T>::setRight(TreeNode<T>* r)
{
   right = r;
}

template < class T >
void TreeNode<T>::setItem(T* itm)
{
  item = itm;
}
}

#endif
