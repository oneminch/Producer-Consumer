#if !defined QUEUE_ARRAY
#define QUEUE_ARRAY

namespace CSC1310
{
template < class T >
class QueueArray
{

   private:
      int max_queue;
      T** items;
      int front;
      int back;
      int sz;

      void arrayResize(int new_size);

   public:
      QueueArray();
      ~QueueArray();

      bool isEmpty();
      int size();
      void dequeueAll();

      T* peek();
      void enqueue(T* item);
      T* dequeue();

};

template < class T >
QueueArray<T>::QueueArray() 
{
   max_queue = 2;
   items = new T*[max_queue];  
   front = 0;
   back = max_queue - 1;
   sz = 0;
}  

template < class T >
QueueArray<T>::~QueueArray() 
{
   delete[] items;
} 

template < class T >
bool QueueArray<T>::isEmpty() 
{
   return sz == 0;
}  

template < class T >
int QueueArray<T>::size()
{
   return sz;
}

template < class T >
T* QueueArray<T>::peek()
{
   T* item = NULL;
   if (!isEmpty()) 
   {  
      item = items[front];
   }
   return item; 
} 

template < class T >
void QueueArray<T>::enqueue(T* item)
{
   if (sz == max_queue)
   {
      arrayResize(2*max_queue);
   }

   //back = (back + 1) % (max_queue);
   back = back + 1;
   if (back == max_queue) back = 0;
   items[back] = item;
   sz++;
} 

template < class T >
T* QueueArray<T>::dequeue() 
{
   T* item = NULL;

   if (!isEmpty()) 
   {
      item = items[front];
      items[front] = NULL;
      //front = (front + 1) % (max_queue);
      front = front + 1;
      if (front == max_queue) front = 0;
      sz--;
   }

   return item; 
}

template < class T >
void QueueArray<T>::arrayResize(int new_size)
{
   T** temp = new T*[new_size];
   int j = front;

   for (int i = 0; i < sz; i++)
   {
      temp[i] = items[j];
      j++;
      if (j == max_queue) j = 0;
   }

   front = 0;
   back = sz - 1;
   max_queue = new_size;

   delete[] items;
   items = temp;
}

template < class T >
void QueueArray<T>::dequeueAll() 
{
   delete[] items;

   max_queue = 2;
   items = new T*[max_queue];  
   front = 0;
   back = max_queue - 1;
   sz = 0;
} 
}

#endif
