#if !defined LIST_LINKED
#define LIST_LINKED

#include "ListLinkedIterator.h"
#include "NextNode.h"

namespace CSC1310
{
template < class T >
class ListLinked
{
   private:
      NextNode<T>* head;
      int sz;
      NextNode<T>* find(int index);

   public:
      ListLinked();
      ~ListLinked();

      bool isEmpty();
      int size();
      void removeAll(); 
      T* get(int index);
      bool add(int index, T* item);
      bool add(T* item);
      bool remove(int index);

      ListLinkedIterator<T>* iterator();
};

template < class T >
ListLinked<T>::ListLinked()
{
   head = NULL;
   sz = 0;
}

template < class T >
ListLinked<T>::~ListLinked()
{
   removeAll();
}

template < class T >
bool ListLinked<T>::isEmpty()
{
   return sz == 0;
}

template < class T >
int ListLinked<T>::size()
{
   return sz;
}

template < class T >
void ListLinked<T>::removeAll()
{
   //loop over the list, deleting the nodes
   //the actual items are not deleted
   if (sz == 0) return;

   NextNode<T>* curr = head;
   NextNode<T>* prev = NULL;
   while (curr != NULL)
   {
      prev = curr;
      curr = curr->getNext();
      prev->setNext(NULL);
      delete prev;
   }

   sz = 0;
   head = NULL;
}

template < class T >
NextNode<T>* ListLinked<T>::find(int index)
{
   NextNode<T>* node = head;
   for (int i = 1; i < index; i++)
   {
      node = node->getNext();
   }
   return node;
}

template < class T >
T* ListLinked<T>::get(int index)
{
   T* item = NULL;

   if (index >= 1 && index <= sz)
   {
      NextNode<T>* curr = find(index);
      item = curr->getItem();
   }

   return item;
}

template < class T >
bool ListLinked<T>::add(T* item)
{
   return add(sz + 1, item);
}

template < class T >
bool ListLinked<T>::add(int index, T* item)
{
   if (index < 1 || index > sz + 1)
   {
      return false;
   }
 
   NextNode<T>* node = new NextNode<T>(item);
   if (index == 1)
   {
      node->setNext(head);
      head = node;
   }
   else
   {
      NextNode<T>* prev = find(index - 1);
      NextNode<T>* curr = prev->getNext();
      prev->setNext(node);
      node->setNext(curr);
   }

   sz++;

   return true;
}

template < class T >
bool ListLinked<T>::remove(int index)
{
   if (index < 1 || index > sz)
   {
      return false;
   }

   if (index == 1)
   {
      NextNode<T>* node = head->getNext();
      delete head;
      head = node;
   }
   else
   {
      NextNode<T>* prev = find(index - 1);
      NextNode<T>* curr = prev->getNext();
      NextNode<T>* after = curr->getNext();
      prev->setNext(after);
      delete curr;
   }

   sz--;

   return true;
}

template < class T >
ListLinkedIterator<T>* ListLinked<T>::iterator()
{
   ListLinkedIterator<T>* iter = new ListLinkedIterator<T>(head);
   return iter;
}
}

#endif
