//
//  main.cpp
//  Barber Sleeping Problem
//
//  Created by Kshitiz Sharma on 24/03/18.
//  Copyright © 2018 Kshitiz Sharma. All rights reserved.

// If the code is generating issues on your machine while returning, please note below configuration

// The code has been built using Xcode on MAC OS X(UNIX)
// The compiler I am using is GNU ++ 14
// Two instance which might create problems

// 1. sleep() function on line 124; which works differntly on UNIX and windows
// 2. The use of shared_mutex library; since differnt compilers have differnet names and forms for this library.
// Rest all should work fine

// Note - I am generating new Cusomter every 1 seconds, instead of 3 seonds; you can change it on line 124
// I am also giving a larger time for barber to complete hair cut i.e [1:15] sec to show better functionality of the code; chnage it on line 46

#include <iostream>
#include <thread>
#include <queue>
#include <chrono> // std::chrono::seconds
#include <mutex>
#include <shared_mutex>
// library "unistd.h for 3 seconds time delay"
#include <unistd.h>

using namespace std;

shared_timed_mutex mutex_;
// This class manages all the activities of custimer and the baber
class Activities{
public:
    // To wake up the barber when customer arrivevs
    void sleeping(int id,int &seat, queue<int>& bench_queue){
        if(seat==0)
        {
            seat=id;
        }
    }

    // When barber is working, when finished the seat is taken by the next person in queue
    void working(int id, queue<int>& bench_queue, int &seat){
        this_thread::sleep_for (chrono::seconds((rand() % 15) + 1));
        if(!bench_queue.empty()){
            seat=bench_queue.front();
            bench_queue.pop();
        }
        else{
            seat=0;
        }
    }
    
    // To add customers to Queue; id the queue is full he/she leaves othewise they are added to queue
    void add_cusomter(int id, queue<int>& bench_queue, int &seat,int m, int &customer_leaving){
        if(id!=0 & id!=1){
            if(bench_queue.size()<m){
                bench_queue.push(id);
            }
            else{
                customer_leaving=id;
            }
        }
    }
    
    // To display the queue, chair and peson left
    //Mad use of shared mutex to print
    void display_queue(int seat,queue<int> bench_queue,int &customer_leaving, int id){
            unique_lock<std::shared_timed_mutex> lock(mutex_);
            cout<<"\n";
            if(seat==0){
                cout<<"Barber is sleeping \n";
                cout<<"Waiting room :"<<"\t";
                while(!bench_queue.empty()){
                    cout << bench_queue.front()<<"\t";
                    bench_queue.pop();
                }
                cout<<"\n";
            }
            else{
                cout<<"Barber cutting the hair of customer "<<seat;
                cout<<"\n";
                cout<<"Waiting room :"<<"\t";
                while(!bench_queue.empty()){
                    cout << bench_queue.front()<<"\t";
                    bench_queue.pop();
                }
                if(customer_leaving!=0){
                    cout<<"\n";
                    cout<<"Customer Leaving "<<customer_leaving<<"\n";
                    customer_leaving=0;
                }
                else{
                    cout<<"\n";
                }
            }
        }
    };

// This class takes care of the customers and threads
class Customer{
public:
    void new_threads(queue<int>& bench_queue,int &seat,int m){
        // ID for customer
        int id=0;
        // To store cusotmer who is leaving
        int customer_leaving=0;
        // Intialised lists of threads to build for the ID threads for each customer
        thread sleeping_id_thread[1000];
        thread barber_working_thread[1000];
        thread add_customers_thread[1000];
        thread display_data[1000];
        
        // Intializing and calling customer threads
        for(int j=0;;j++){
                id=j;
                sleeping_id_thread[j]=thread(&Activities::sleeping,Activities(),id,ref(seat),ref(bench_queue));
                barber_working_thread[j]=thread(&Activities::working,Activities(),id,ref(bench_queue),ref(seat));
                add_customers_thread[j]=thread(&Activities::add_cusomter, Activities(),id,ref(bench_queue),ref(seat),m,ref(customer_leaving));
                display_data[j]=thread(&Activities::display_queue,Activities(),seat, bench_queue,ref(customer_leaving),id);
                // Time Delay for 1 seconds
                sleep(1);
        }
        
        // Joining threads to destroy threads after completion
        for(int j=0;;j++){
            sleeping_id_thread[j].join();
            barber_working_thread[j].join();
            add_customers_thread[j].join();
            display_data[j].join();
        }
    }
};

int main(int argc, const char * argv[]) {
    // Nuber of Seats
    int m;
    cout<<"Enter the number of seats \n";
    cin>>m;
    
    // To implement the logic queue will be used - First in First Out logic
    queue<int> bench_queue;
    int seat=0;
    
    // The main thread responsible for creating the cusotmer threads
    thread create_new_thread(&Customer::new_threads,Customer(),ref(bench_queue),ref(seat),m);
    create_new_thread.join();
    
    return 0;
}



