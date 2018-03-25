//
//  main.cpp
//  Barker Sleeping Problem
//
//  Created by Kshitiz Sharma on 24/03/18.
//  Copyright © 2018 Kshitiz Sharma. All rights reserved.
//

#include <iostream>
#include <thread>
// library "unistd.h for 3 seconds time delay"
#include <unistd.h>
#include <queue>
#include <chrono> // std::chrono::seconds
#include <mutex>
#include <shared_mutex>

using namespace std;

shared_timed_mutex mutex_;
class Activities{
private:
    
public:
    void sleeping(int id,int &seat, queue<int>& bench_queue){
        if(seat==0)
        {
            seat=id;
        }
    }

    void working(int id, queue<int>& bench_queue, int &seat){
        this_thread::sleep_for (chrono::seconds((rand() % 15) + 1));
        if(!bench_queue.empty()){
            seat=bench_queue.front();
            bench_queue.pop();
        }
    }
    
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

class Customer{
public:
    void new_threads(queue<int>& bench_queue,int &seat,int m){
        int id=0;
        int customer_leaving=0;
        thread sleeping_id_thread[1000];
        thread barber_working_thread[1000];
        thread add_customers_thread[1000];
        thread display_data[1000];
        for(int j=0;;j++){
                id=j;
                sleeping_id_thread[j]=thread(&Activities::sleeping,Activities(),id,ref(seat),ref(bench_queue));
                barber_working_thread[j]=thread(&Activities::working,Activities(),id,ref(bench_queue),ref(seat));
                add_customers_thread[j]=thread(&Activities::add_cusomter, Activities(),id,ref(bench_queue),ref(seat),m,ref(customer_leaving));
                display_data[j]=thread(&Activities::display_queue,Activities(),seat, bench_queue,ref(customer_leaving),id);
                // Time Delay for 3 seconds
                sleep(1);
        }
        
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
    
    thread create_new_thread(&Customer::new_threads,Customer(),ref(bench_queue),ref(seat),m);
    create_new_thread.join();
    
    return 0;
}



