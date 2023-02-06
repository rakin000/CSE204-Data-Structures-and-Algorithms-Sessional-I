#include <vector>
#include <exception>
#include <stdexcept>
#include <assert.h>
#include <iostream>
#include <ctime>
using namespace std;

class Heap{
    static const int INITIAL_CAPACITY = 16;
    int *array;
    int N;
    int capacity;

    void validate(int id){
        if( id < 0 || id >= N )
            throw invalid_argument(to_string(id)+" index out of bound");
    }
    void swap(int i,int j){
        validate(i);
        validate(j);

        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    void resize(int new_capacity){
        if( new_capacity < N ) 
            throw invalid_argument("resize(new_capacity): new capacity less than current array size");
        
        int *temp = new int[new_capacity];
        for(int i=0;i<N;i++)
            temp[i] = array[i];
        delete [] array;

        array = temp;
        capacity = new_capacity;
    }
    void bubble_up(int id){
        validate(id);
        int parent_id = (id+1)/2-1;
        while( id > 0 && array[parent_id] < array[id] ){
            swap(parent_id,id);
            id = parent_id;
            parent_id = (id+1)/2-1;
        }
    }
    void bubble_down(int id){
        validate(id);
        int child_1 = 2*(id+1)-1;
        int mx_child ;
        while( child_1 < N ){
            mx_child = child_1;
            if( child_1+1<N){
                mx_child = (array[child_1] > array[child_1+1]) ? child_1: child_1+1;
            }
            if( array[mx_child] > array[id] ){
                swap(id,mx_child);
                id = mx_child;
                child_1 = 2*(id+1)-1;
            }
            else break;
        }
    }
    public:
    Heap(int capacity=INITIAL_CAPACITY){
        if( capacity<=0 )
            throw invalid_argument(to_string(capacity)+": invalid value for capacity");
        this->capacity = capacity;
        N = 0;
        array = new int[capacity];        
    }
    Heap(int *a,int n){
        if( n<=0 )
            throw invalid_argument(to_string(n)+": invalid value for capacity");
        capacity = n;
        N = n;
        this->array = new int[capacity];
        for(int i=0;i<n;i++)
            array[i] = *(a+i);
        
        for(int i=n/2;i>=0;i--)
            bubble_down(i);
    }
    ~Heap(){
        delete [] array;
    }

    int size(){     return N; }
    bool empty(){   return N==0; }

    void insert(int value){
        if( N == capacity )
            resize(capacity*2);
        array[N++] = value;

        bubble_up(N-1);   
    }
    void deleteKey(){
        if( empty() ) throw underflow_error("empty heap");

        swap(0,N-1);
        N--;
        if( !empty() ) bubble_down(0);

        if(N <= capacity/4 && capacity/2 > INITIAL_CAPACITY ){
            int new_capacity = (capacity/2 > INITIAL_CAPACITY) ? capacity/2: INITIAL_CAPACITY;
            resize(new_capacity);
        }
    }
    int getMax(){
        if( empty() ) throw underflow_error("empty heap");

        return array[0];
    }
};


bool is_sorted_descending(vector<int> &v){
    for(int i=0;i<v.size()-1;i++)
        if( v[i] < v[i+1] )
            return false;
    return true;
}

void heapsort(vector<int> &v){
    Heap hh(v.data(),v.size());
    
    for(int i=0;i<v.size();i++){
        v[i] = hh.getMax();
        hh.deleteKey();
    }
    assert(is_sorted_descending(v));
}


int check(){
    const int N=1e7; 
    vector<int> arr;

    while(1){
        arr.clear();
        int n = rand()%N+1;
        cout<<"Array size = "<<n<<endl;
        for(int i=0;i<n;i++)
            arr.push_back(rand());

        clock_t time_of_directly_making_heap_from_array = clock();
        Heap hh(arr.data(),arr.size());
        cout<<"Making heap directly takes "<< float(clock()-time_of_directly_making_heap_from_array)/CLOCKS_PER_SEC<< " seconds"<<endl;

        clock_t time_of_insertion = clock();
        Heap h2;
        for(int i=0;i<n;i++)
            h2.insert(arr[i]);
        cout<<"Insertion of all numbers take " << float(clock()-time_of_insertion)/CLOCKS_PER_SEC <<" seconds\n";

        clock_t time_of_deletion = clock();
        int last1 = hh.getMax(); 
        hh.deleteKey();
        while( !hh.empty() ){
            if( hh.getMax() > last1 ){
                cout<<"Failed\n..aborting..";
                return -1;
            }
            last1 = hh.getMax();
            hh.deleteKey();
        }
        cout<<"Deletion from first heap takes " << float(clock()-time_of_deletion)/CLOCKS_PER_SEC<<" seconds\n";
        
        time_of_deletion = clock();
        int last2 = h2.getMax();
        h2.deleteKey();
        while( !h2.empty() ){
            if( h2.getMax() > last2 ){
                cout<<"Failed\n...aborting.";
                return -1;
            }
            last2 = h2.getMax();
            h2.deleteKey();

        }
        cout<<"Deletion from second heap takes " << float(clock()-time_of_deletion)/CLOCKS_PER_SEC<<" seconds\n";
        clock_t  time_of_heapsort = clock();
        heapsort(arr);
        cout<<"Heapsorting the array takes " << float(clock()-time_of_heapsort)/CLOCKS_PER_SEC<<" seconds\n";
        cout<<"Success\n\n\n";
    }
}
