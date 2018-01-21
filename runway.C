#include <iostream>
#include "LQueue.h"
using namespace std;
	

void print(Queue q)
{ q.display(cout); }

int main(void)
{
	cout << "Time for a plane to land (in minutes): ";
    int TIMETOLAND;
    cin >> TIMETOLAND;

    cout << "Time for a plane to takeOff (in minutes): ";
    int TIMETOTAKEOFF;
    cin >> TIMETOTAKEOFF;

    cout << "Landing rate (planes per hour): ";
    int LRATE;
    cin >> LRATE;

    cout << "Takeoff rate (planes per hour): ";
    int TRATE;
    cin >> TRATE;

    cout << "How long to run the simulation (in minutes): ";
    int RUNTIME;
    cin >> RUNTIME;

    Queue landingQ;                         //landing queue
    Queue takeoffQ;                         //takeoff queue
    Queue runwayQ;                          //holds the plane currently landing/taking off (holds ONLY 1 plane at a time)
    bool planeLanding = false;              //tracks if a plane is currently landing
    bool planeTakingOff = false;            //tracks if a plane is currently taking off
    bool runtimeLimitReached = false;       //boolean for if the loop has reached upper bound defined by RUNTIME
    int planeID = 1000;                     //sequential plane ID's beginning at 1000
    int timeTillTakeOff = 0;                //time until take off for current plane (in runway)
    int timeTillLanding = 0;                //time until landing for current plane (in runway)
    int extendTime = RUNTIME;               //additional time reference for when program reaches RUNTIME
    //variables for statistics (LQ = landing queue, TQ = takeoff queue)
    int maxLQ = 0;                          //max # planes in landing queue
    int maxTQ = 0;                          //max # planes in takeoff queue
    float totalLQTime = 0;                  //total minutes spent in landing queue (all planes)
    float totalTQTime = 0;                  //total minutes spent in takeoff queue (all planes)
    float planesLanded = 0;                 //# of planes landed
    float planesTakenOff = 0;               //# of planes taken off


    srand(time(NULL));                      //randomizer for rand() calls
    for(int i = 0; i < RUNTIME; i++) {
        // generate two random numbers n1, n2
        int n1 = rand();
        int n2 = rand();
        cout << "Time = " << i << endl;     //cout current time (minutes)
        // add plane to landing queue?
        if (LRATE > (n1 % 60)) {
            landingQ.enqueue(planeID);      //add a plane to landing queue
            cout << "Plane " << landingQ.back() << " wants to land; added to landing queue; "
                 << landingQ.size() << " in queue" << endl; 
            // If when you run the program and in the chance it freezes please try commenting out this "if" statement below
            if (planeID % 9 == 0) {
                landingQ.move_to_front(landingQ.back());
                cout << "Plane " << landingQ.front() << " is emergency plane, added to front of landing queue" << endl;
            } 
            planeID++;                      //increment plane ID
            if (landingQ.size() > maxLQ) {
                maxLQ = landingQ.size();
            }
        }
        // add plane to takeoff queue?
        if (TRATE > (n2 % 60)) {
            takeoffQ.enqueue(planeID);      //add a plane to takeoff queue
            cout << "Plane " << takeoffQ.back() << " wants to takeoff; added to takeoff queue; "
                 << takeoffQ.size() << " in queue" << endl; 
            // If when you run the program and in the chance it freezes please try commenting out this "if" statement
            if (planeID % 9 == 0) {
                takeoffQ.move_to_front(takeoffQ.back());
                cout << "Plane " << takeoffQ.front() << " is emergency plane, added to front of takeoff queue" << endl;
            } 
            planeID++;                      //increment plane ID
            if (takeoffQ.size() > maxTQ) {
                maxTQ = takeoffQ.size();
            }
        }

        CHECKRUNWAY:                        //label for goto statement
        // runway empty?
        if (runwayQ.empty()) {
            // plane waiting to land? (note we check for landing planes before takeoff planes (specification))
            if (!landingQ.empty()) {
                runwayQ.enqueue(landingQ.front());      //add plane at front of landing queue into runway queue
                landingQ.dequeue();                     //remove the plane from landing queue
                timeTillLanding = TIMETOLAND;           //reset landing time counter
                planeLanding = true;
                cout << "Landing; Plane " << runwayQ.front() << endl;
            }
            // plane waiting to take off?
            else if (!takeoffQ.empty()) {
                runwayQ.enqueue(takeoffQ.front());      //add plane at front of takeoff queue into runway queue
                takeoffQ.dequeue();                     //remove the plane from takeoff queue
                timeTillTakeOff = TIMETOTAKEOFF;        //reset takeoff time counter
                planeTakingOff = true;
                cout << "Taking Off; Plane " << runwayQ.front() << endl;
            }
        }
        // runway is in use (not empty)
        else {
            // is a plane currently landing?
            if (planeLanding) {
                timeTillLanding--;          //decrement time till landing (keeps track of passed time since queueing into runway)
                // plane finished landing?
                if (timeTillLanding == 0) {
                    cout << "Landing complete; " << landingQ.size() << " in queue" << endl;
                    runwayQ.dequeue();      //remove plane from runway queue
                    planeLanding = false;
                    planesLanded++;
                    goto CHECKRUNWAY;       //in same clock tick, queue up another plane for landing/takeoff (if it exists)
                }
            }
            // is a plane currently taking off?
            else if (planeTakingOff) {
                timeTillTakeOff--;          //decrement time till takeoff (keeps track of passed time since queueing into runway)
                // plane finished taking off?
                if (timeTillTakeOff == 0) {
                    cout << "Takeoff complete; " << takeoffQ.size() << " in queue" << endl;
                    runwayQ.dequeue();      //remove plane from runway queue
                    planeTakingOff = false;
                    planesTakenOff++;
                    goto CHECKRUNWAY;       //in same clock tick, queue up another plane for landing/takeoff (if it exists)
                }
            }
        }

        totalTQTime = totalTQTime + takeoffQ.size();    //end of "minute cycle" reached, add # planes into total queue time (since each cycle is 1 minute)
        totalLQTime = totalLQTime + landingQ.size();
        //code below runs when RUNTIME limit reached -> check if planes still need to be dequeued
        if (i+1 == RUNTIME) { //next cycle will reach RUNTIME limit?
            if (!runtimeLimitReached) { //This code block runs once (to avoid printing "No new takeoffs..." each time)
                cout << "No new takeoffs or landings will be generated." << endl;
                runtimeLimitReached = true;
            }
            //are there still planes in queue after runtime limit reached?
            while (!runwayQ.empty() || !landingQ.empty() || !takeoffQ.empty()) {
                //Iterate through queues until empty
                cout << "Time = " << extendTime << endl; //continue to track time
                extendTime++; //time reference
                goto CHECKRUNWAY;
            }
        }
	} //end of Loop

    cout << "End of program.\n" << endl; //End of program reached
    cout << "STATISTICS\n" << "AVERAGE MINUTES SPENT WAITING TO LAND: " << totalLQTime/planesLanded << endl;
    cout << "MAXIMUM NUMBER OF PLANES IN LANDING QUEUE WAS: " << maxLQ << endl;
    cout << "AVERAGE MINUTES SPENT WAITING TO TAKEOFF: " << totalTQTime/planesTakenOff << endl;
    cout << "MAXIMUM NUMBER OF PLANES IN TAKEOFF QUEUE WAS: " << maxTQ << endl;
    return 0;
}

