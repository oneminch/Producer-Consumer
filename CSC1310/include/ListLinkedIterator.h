#if !defined LIST_LINKED_ITERATOR_H
#define LIST_LINKED_ITERATOR_H

#include "NextNode.h"

namespace CSC1310
{
template < class T >
class ListLinkedIterator
{

   private:
      NextNode<T>* ref;

   public:
      ListLinkedIterator(NextNode<T>* head);
      ~ListLinkedIterator();

      bool hasNext();
      T* next();

};

template < class T >
ListLinkedIterator<T>::ListLinkedIterator(NextNode<T>* first)
{
   ref = first;  //the iterator is not independent of the list
}

template < class T >
ListLinkedIterator<T>::~ListLinkedIterator()
{
   ref = NULL;
}

template < class T >
bool ListLinkedIterator<T>::hasNext()
{
   return ref != NULL;
}

template < class T >
T* ListLinkedIterator<T>::next()
{
   T* item = NULL;

   if (hasNext())
   {
      item = ref->getItem();
      ref = ref->getNext();
   }

   return item;
}
}

#endif
