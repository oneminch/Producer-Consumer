#if !defined NULL
   #define NULL 0
#endif

#if !defined NEXT_NODE
#define NEXT_NODE

namespace CSC1310
{
template < class T >
class NextNode 
{

   private:
      NextNode<T>* next;
      T* item;

   public:
      NextNode(T* item);
      ~NextNode();
      NextNode<T>* getNext();
      void setNext(NextNode<T>* next);
      T* getItem();

};

template < class T >
NextNode<T>::NextNode(T* itm)
{
   item = itm;
   next = NULL;
}

template < class T >
NextNode<T>::~NextNode()
{
   item = NULL;
   next = NULL;
}

template < class T >
NextNode<T>* NextNode<T>::getNext()
{
   return next;
}

template < class T >
void NextNode<T>::setNext(NextNode<T>* nxt)
{
   next = nxt;
}

template < class T >
T* NextNode<T>::getItem()
{
   return item;
}
}

#endif
