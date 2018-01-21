/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
using namespace std;
	

void print(Queue q)
{ q.display(cout); }

int main(void)
{
   Queue q1;
    
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++) 
      q1.enqueue(100*i);

   cout << "Contents of queue q1 (via  print):\n";
   print(q1); 
   cout << endl;

   Queue q2;
   q2 = q1;
   cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
   print(q2); 
   cout << endl;

   cout << "Queue q2 empty? " << q2.empty() << endl;

   cout << "Front value in q2: " << q2.front() << endl;

   while (!q2.empty())
   {
     cout << "Remove front -- Queue contents: ";
     q2.dequeue();
     q2.display(cout);
   }
   cout << "Queue q2 empty? " << q2.empty() << endl;
   cout << "Front value in q2?" << endl << q2.front() << endl;
    q1.move_to_front(200);
    cout << "Queue q1, front = 200?" << endl;
    q1.display(cout);
    q1.move_to_front(100);
    cout << "Queue q1, front = 100?" << endl;
    q1.display(cout);
    q1.move_to_front(500);
    cout << "Queue q1, front = 500?" << endl;
    q1.display(cout);
    q1.move_to_front(800);
    cout << "Queue q1, front = 800?" << endl;
    q1.display(cout);
    q1.move_to_front(1000);
    cout << "Queue q1, front = 1000?" << endl;
    q1.display(cout);
    q2.enqueue(1);
    q2.enqueue(150);
    q2.enqueue(100);
    q2.enqueue(301);
    q2.enqueue(1000);
    q2.enqueue(2000);
    q2.enqueue(3000);
    cout << "q2:" << endl;
    print(q2);
    cout << "q1:" << endl;
    print(q1);
    q1.merge_two_queues(q2);
    cout << "q1 and q2 merged:" << endl;
    print(q1);

    Queue q3;
    Queue q4;
    q3.enqueue(1);
    q3.enqueue(3);
    q3.enqueue(5);
    q4.enqueue(2);
    q4.enqueue(4);
    q4.enqueue(6);
    cout << "q3:" << endl;
    print(q3);
    cout << "q4" << endl;
    print(q4);
    q3.merge_two_queues(q4);
    cout << "q3 and q4 merged:" << endl;
    print(q3);

    return 0;
}

//test