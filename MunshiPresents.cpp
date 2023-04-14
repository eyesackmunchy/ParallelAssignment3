// Assignemnt 3 - isaac munshi

#include <iostream>

// For queueueue
#include <queue>

// for square root
#include <cmath>

// For Input/output files
#include <fstream>

// for sleep
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// for threads
#include <thread>

#include <vector>
using namespace std;



class node {
    public:
        int ID;
        struct node *next;
};



int countedGuests = 0;
const int numThreads = 100;
bool everyoneSeen = false;
//bool inRoom = false;
bool invited[numThreads] = {0}; // a value of 1 means that guest is invited and currently in the labyrinth
bool seenVase[numThreads] = {0}; // if all 1's, that means everyone invited at least once and we won
queue<int> vaseQueue;
int presentIDs[500000] = {};
node* head = nullptr;
node* tail = nullptr;
int listlength = 0;

// batch used for the add100k funciton
int batchNum = 0;




    // Tasks for Presents //
    // 1. add present to list (will be faked with sleeping)
    // 2. grab present and write letter (writing letter will be faked with sleeping)
    // 3. search when the Minotaur asks (will be faked with sleeping)


void doTasks(int threadID) {
    bool didISeeVase = false;
    while (!everyoneSeen) {
        // simulates adding to queue
        float enqueueTime = (rand() % 20 + 1)/ 20; 
        Sleep(enqueueTime);
        
        // 1 in 10 chance that the minotaur asks to search
        int toSearch = (rand() % 10 + 1);
        if (toSearch == 10) {
            float searchTime = (rand() % 20 + 1)/ 20; 
            Sleep(searchTime);
        }


        // if queue is empty and ready to join:
        if (vaseQueue.size() == 1) {
            //cout << "\nHEY THIS IS EMPTY IM COMING IN:";
            //cout << threadID;

            // add self to queue
            invited[threadID] = true;
        }

        /*else {
            //cout << "\n";
            //cout << "I'm sad I have to wait in queue :(";
            //cout << threadID;
    
            //add self to queue
            vaseQueue.push(threadID);
        }*/



        while (!invited[threadID])// waits until invited
            Sleep(0.1); // VERY IMPORTANT to release the CPU
            if (everyoneSeen) // kills thread ( i can probably go without this but idk)
                return; 
         
        ////cout << "\nIm in the lab and my ID is ";
        ////cout << threadID;
        
        // WHEN FINALLY INVITED IN:
    // simulates the guest looking at the vase
        float viewingTime = (rand() % 20 + 1)/ 20; 
        Sleep(viewingTime);  


        // add self to list who have seen vase:
        if (!didISeeVase) {
            //cout << "\nthis vase sucks";
            //cout << threadID;
            //cout << " man.";
            
            countedGuests++;
            seenVase[threadID] = true;
            didISeeVase = true;
            //cout << boolalpha;
            //cout << didISeeVase;
        }
            

        // notify next guest:
        invited[threadID] = false;
        //cout << "\n\n AM I CURRENTLY INVITED??? ";
        //cout << threadID;
        //cout << boolalpha;
        //cout << invited[threadID];
        //cout << "\n";

        while (vaseQueue.size() <= 3) // waits for the queue to have other guests
            Sleep(1);
            
        // when 2 or more in queue:
        vaseQueue.pop(); // deletes front element (this thread)
        Sleep(10);
        int nextGuest = vaseQueue.front();
        //cout << "\n\nguest ";
        //cout << threadID;
        //cout << " is OUTTT, next up is ";
        //cout << nextGuest;
        invited[nextGuest] = true;

        //party more before queuing up again
        //partyingTime = (rand() % 20 + 1)/ 20; 
        //Sleep(partyingTime);
    }
}

void add100k() {
    int start = batchNum * 100000;
    int end = (batchNum + 1) * 100000;

    node* p1;
    node* p2;

    p1 = new node;

    if (head == nullptr)
        head = p1;
    else if (tail != nullptr)
        tail->next = p1;

    
    for (int i = start; i < end-1; i++) {
        int randID = rand() % 10 + (10 * i);
        p1->ID = randID;

        p2 = new node;
        p1->next = p2;

        p1 = p1->next;
    }

    //finish last node
    int randID = rand() % 10 + (10 * end);
    p1->ID = randID;
    p1->next = nullptr;

    tail = p1;

    batchNum += 1;
    listlength += 100000;
}


int main() {
    cout << "Im about to start (I hard coded 100 guests btw it should take only 3.1 sec)\n\n";

    //int presentIDs[10] = {};
    int presents_length = sizeof(presentIDs)/sizeof(presentIDs[0]);

    cout << "length is " << presents_length;

    for (int i = 0; i < 2; i++) {
        add100k();
        cout << "\nLIST length = " << listlength;
    }

    /*while (head->next != nullptr) {
        cout << head->ID << "\n";
        head = head->next;
    }*/

    cout << "\nHEAD ID: " << head->ID;
    cout << "\nHEAD next: " << head->next;
    cout << "\nTAIL ID: " << tail->ID;
    cout << "\nTAIL next: " << tail->next;
    cout << "\nlistlength: " << listlength;




    // initialize a random serial number for each present, also make sure the next present is guarunteed higher than the last one by adding (10*i)
    //for (int i = 0; i < presents_length; i++) {
    //    presentIDs[i] = (rand() % 10 + 1 + (10 * i));
    //}
    /*
    node* p1;
    node* p2;
    node* start;

    p1 = new node;
    start = p1;
    for (int i = 0; i < 25; i++) {
        int randID = rand() % 10 + (10 * i);
        p2 = new node;
        p1->ID = randID;
        p1->next = p2;
        p1 = p1->next;
    }
    p1->next = nullptr;


    cout << '\n';
    while (start->next != nullptr) {
        cout << start->ID << "\n";
        start = start->next;
    }*/

    

    /*node n;
    n.data = 12345;
    cout << n.data;*/

    // unfortunately I need to break up the 500,000 into batches of 100,000 or else the program will crash
    //for (int i = 10000)


    /*
    thread threadArray[numThreads];
    vector<thread> threads; 
    for (int i = 0; i < numThreads; i++) {
        //vector <int> &primes, int start, int end
        threads.emplace_back(doTasks, i);
        //Sleep(0.05);
    }

    vector<thread> detachThreads = move(threads);
    for (thread &th : detachThreads) {
        th.detach();
        //Sleep(0.05);
    }*/

    //for (int i = 0; i < 20; i++) {
    //    cout << "\n\nrand: " << (rand() % 10 + 1 + (10 * i));
    //}


    //bool win = startVase();
    //if (win)
    //    cout << "\n\n WE WONNN BABYYYY";
    //else
    //    cout << "\n\n:(";
    return(0);
}