#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

template<class item> class array_list{
    static const int INITIAL_CAPACITY = 4;
    item *array;
    int N;
    int capacity = INITIAL_CAPACITY;

    void validate(int id){
        if( id < 0 || id >= N )
            throw invalid_argument(to_string(id)+" index out of bound");
    }
    void resize(int new_size) {
        if( new_size < N ) 
            throw invalid_argument("resize("+to_string(N)+")"+" : invalid capacity for resizing");

        item *temp = new item[new_size];

        for(int i=0;i<N;i++)
            temp[i] = array[i];
        
        delete [] array;
        array = temp;
        capacity = new_size;
    }
    public :
    array_list(int capacity){
        if( capacity<=0 )
            throw invalid_argument(to_string(capacity)+": invalid value for capacity");
        N = 0;
        this->capacity = capacity ;
        array = new item[capacity];       
    }
    array_list():
        array_list(INITIAL_CAPACITY)
    {}

    array_list(item A[],int len){
        capacity = len;
        array = new item[capacity]; 
        N = 0;
        for(int i=0;i<capacity;i++){
            array[N++] = A[i];
        }
    }
    ~array_list(){
        delete [] array;
    }
    int size(){
        return N;
    }
    bool empty(){
        return (N == 0);
    }
    void clear(){
        N = 0;
    }
    item get(int i){
        validate(i);
        return array[i];
    }
    item operator[](int i){
        return get(i);
    }
    item get_last(){
        if( empty() ) throw underflow_error("empty arraylist");
        return array[N-1];
    }
    void add(item e){
        if( N == capacity )
            resize(capacity*2);
        
        array[N++] = e;
    }
    void add(int i,item e){
        add(e);

        for(int j=N-1;j>i;j--){
            item temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
        }
    }
    item pop_back(){
        if( empty() ) throw underflow_error("empty arraylist!!");
        item t = array[--N];
        if( capacity/2 > INITIAL_CAPACITY && N <= capacity/4 ){
            int n_capacity = (capacity/2>0)?capacity/2:INITIAL_CAPACITY;
            resize(n_capacity);
        }
        return t;
    }
};