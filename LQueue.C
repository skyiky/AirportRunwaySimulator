/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
   Queue::NodePointer newptr = new Queue::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

//--- Definition of back()
QueueElement Queue::back() const
{
   if (!empty())
      return (myBack->data);
   else
   {
  return 0;
   }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

void Queue::move_to_front(QueueElement data)
{
    if (!empty()) {
        Queue::NodePointer current = myFront->next, //pointers to keep track of current and previous node
                previous = myFront;
        if (myFront->data == data) {
          return;
        }
        while (current != 0) { //loop through queue
            if (current->data == data) { //data are equal?
                previous->next = current->next; //remove current node reference from linked list
                current->next = myFront; //set current nodes next to myFront (the current front)
                myFront = current; //set myFront = current (front is now current)
                return;
            } else {
                previous = current;       //point pointers to the next node
                current = current->next;
            }
        } //end of loop
    }
    return;
}

void Queue::merge_two_queues(Queue q2)
{
    if (!q2.empty()) { 

        while (q2.myFront != 0) //iterate through q2, grabbing the first entry
        {
            Queue::NodePointer q1current = myFront, q1previous = myFront, q2front = q2.myFront;
            Queue::NodePointer ptrToInsert = new Queue::Node(q2.myFront->data);
            while (q1current != 0) //iterate through q1, comparing ptrToInsert with every node in q1
            {
                if (ptrToInsert->data < q1current->data) //insert?
                {
                    if (q1current == myFront) //inserting at very front of q1?
                    {
                        myFront = ptrToInsert;
                        myFront->next = q1current;
                    }
                    else //inserting elsewhere
                    {
                        q1previous->next = ptrToInsert;
                        ptrToInsert->next = q1current;
                    }

                    q2.myFront = q2.myFront->next;
                    delete q2front; //delete front node of q2 (was "moved" into q1)

                    break;
                }
                else if (q1current == myBack) //inserting at very back of q1?
                {
                    myBack->next = ptrToInsert;
                    myBack = myBack->next;
                    q2.myFront = q2.myFront->next;
                    delete q2front;
                    break;
                }
                else //don't insert
                {
                    q1previous = q1current;
                    q1current = q1current->next;
                }
            } //end of inner loop (q1)
        } // end of outer loop (q2)
    }
    return;
}

int Queue::size() { //helper function for returning queue size
    int counter = 0;
    Node* curr = this->myFront;
    while (curr != NULL) {
        counter++;
        curr = curr->next;
    }
    return counter;
}


//test