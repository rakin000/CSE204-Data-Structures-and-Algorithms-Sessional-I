#include <iostream>
#include <exception>
using namespace std;

template<class Type> class queue{
    class node{
        public:
        Type value;
        node *next;

        node(Type value){
            this->value = value;
            next = NULL;
        }
        node(){
            next = NULL;
        }
        ~node(){
          // cout<<"called "<<value<<endl;
            delete next;
        }
    };
    node *_front;
    node *_back;
    int N;
    public:
    queue(){
        _front = NULL;
        _back = NULL;
        N = 0;
    }
    ~queue(){
        delete _front;
    }

    int size(){
        return N;
    }
    bool empty(){
        return (_front == NULL);
    }
    void push(Type value){
        if( _front == NULL ){
            _front = new node(value);
            _back = _front ;
        }
        else {
            _back->next = new node(value);
            _back = _back->next;
        }
        ++N;
    }
    Type pop(){
        if(_front == NULL) throw underflow_error("empty queue");
        Type temp = _front->value;
        node *t = _front;
        _front = _front->next;
        --N;
        
        t->next = NULL;
        delete t;

        return temp;
    }
    Type& front(){
        if(_front == NULL) throw underflow_error("empty queue");
        return _front->value;
    }
    Type& back(){
        if( _back == NULL ) throw underflow_error("empty queue");
        return _back->value;
    }
};

template<class Type> class array_queue{
    static int const CAPACITY = 4;
    int _front;
    int _back;
    int cap ;
    int N ;
    Type *a;
    public:
    array_queue(int cap=CAPACITY){
        this->cap = cap;
        N = 0;
        a = new Type[cap];
        _front = 0;
        _back = 0;
    }
    ~array_queue(){
        delete [] a;
    }

    int size(){
        return N;
    }
    bool empty(){
        return (N==0);
    }
    void push(Type value){
        if( size() == cap ){
            int nCap = 2*cap;
            Type* temp = new Type[nCap];
            int i=0;
            temp[i++] = a[_front]; // when full, front == back... 
            _front = (_front+1)%cap;
            while( _front != _back ){
                temp[i++] = a[_front];
                _front=(_front+1)%cap;
            }

            delete [] a;
            a = temp;
            cap = nCap;
            _front = 0;
            _back = i;
        }

        a[_back] = value;
        _back = (_back+1)%cap;
        ++N;
    }
    Type pop(){
        if( empty() ) throw underflow_error("empty queue");

        if( size() > CAPACITY && size() == cap/4 ){            
            int nCap = (cap/2 > CAPACITY) ? cap/2: CAPACITY;
            Type* temp = new Type[nCap] ;
            int i=0;
            while( _front != _back ){
                temp[i++] = a[_front];
                _front = (_front+1)%cap;
            }

            delete [] a;
            a = temp;
            cap = nCap;
            _front = 0;
            _back = i;
        }

        Type t = a[_front];
        _front = (_front+1)%cap;
        --N;
        return t;
    }
    Type& front(){
        cout<<_front<<endl;
        if( empty() ) throw underflow_error("empty queue");
        return a[_front];
    }
    Type& back(){
        cout<<_back<<endl;
        if( empty() ) throw underflow_error("empty queue");
        return a[_back] ;
    }
};


void test(){
    queue<int> qq;
    array_queue<int> q;

    qq.push(1);
    qq.push(2);
    qq.push(3);
    qq.push(3);
    qq.push(434);
    qq.push(21);
    qq.push(234);
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl; 
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
    cout<<qq.pop()<<endl;
}