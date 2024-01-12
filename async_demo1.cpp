#include <future>
#include <iostream>

/*
    A   B   C = 3 functions

    1) single thread technique

    op 1 = one after other (Always complete 1 thing before start other).  = easy, not optimize.
    -------------------------------------------------------------------

    2) multi thread thechnique

    op 2 = I will complete all task in such way that I "paractically start all of them at the same time"
    but keep juggling them based on some criteria
    -------------------------------------------------------------------

    3) parallel execution

    op 3 = map number of task among number available "workers"  (not overlapping a on depend on b, 2 not in same task)
    -------------------------------------------------------------------

    4) Asynchronous execution

    op 4 = start a task. Either delegate it to another or do it your self after some time
    (manager like)
    if someone else doing a task, monitor it, wait for their work to be done, take follow up actions accordingly
    --------------------------------------------------------------------

*/
/*
    2 tasks
    calculate factorial of 5
    calculate square of a number given by ther user
*/

int square( std::future<int>& ft){

    std::this_thread::sleep_for(std::chrono::seconds(1));       //delay 

    std::cout << "\nHello form square, I have starting my work \n";   
    int number = ft.get();                                              //stop here and return and comeback after value get

    return number*number;
}
int factorial (int number){

    std::this_thread::sleep_for(std::chrono::seconds(2));

    if(number < 0){
        throw std::runtime_error( "negative number error! \n");
    }
    else if( number == 1 || number == 0){
        return 1;
    }

    else{
        return number * factorial(number-1);
    }
}

int main(){

   // step 1 : make a promise
    std::promise<int> pr;

    // step 2 : A funture link to the promise
    std::future<int> ft = pr.get_future();

    /*
        OS : launch square (if possible as a new thread)  
        1 - parameter launch a policy
        2 - functionalities
        3 on = parameter of function
    */
   /*
        role change 
        square = producer not promising ( no promise in return time )
        main = consumer ( main taking a future )
   */

    std::future<int> result_ft = std::async(std::launch::async, &square, std::ref(ft));

    int val=0;
    std::cin>>val;
    std::cout << factorial(5);

    // fulfuling a promise 
    pr.set_value(val);

    std::cout << "Result of square is : "<<result_ft.get()<<"\n";
}

/*
    client server architecture


    future promise model = way in which 2 entities can talk to each other 

    producer / sender = promise 

    consumer / reciver = future

    square calculation 
    Main needs to delegate the task of square calculation

    ----------> new thread for square will be registered with OS
*/