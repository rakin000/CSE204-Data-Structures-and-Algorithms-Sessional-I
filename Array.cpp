#include <iostream>
using namespace std;



template<class item> class Array{
    static const int CAP = 4;
    item *a;
    int sz;
    int cap = CAP;
    public :
    Array(int n=CAP){
        sz = 0;
        cap = n;
        a = new item[cap];       
    }
    Array(item A[], int n){
        cap = n;
        a = new item[cap];
        sz = 0;

        for(int i=0;i<n;i++){
            a[sz++] = A[i];
        }
    }
    Array(const Array<item> &A){
        cap = A.cap;
        sz = A.sz;
        a = new item[cap];
        for(int i=0;i<sz;i++)
            a[i] = A.a[i];
    }
    ~Array(){
        delete [] a;
    }

    item* getArray(){
        return a;
    }

    item getAnElement(int i){
        if( i < sz )
            return a[i];
        else throw "ERROR";
    }

    void add(item e){
        if( sz < cap ){
            a[sz++] = e;
        }
        else {
            item *temp = new item[cap*2];
            cap = cap*2;
            for(int i=0;i<sz;i++)
                temp[i] = a[i];
            temp[sz++] = e;

            delete [] a;
            a = temp;
        }
    }

    void add(int i,item e){
        add(e);

        for(int j=sz-1;j>i;j--){
            item temp = a[j];
            a[j] = a[j-1];
            a[j-1] = temp;
        }
    }

    void remove(item e){
        int nsz = 0;
        for(int i=0;i<sz;i++){
            nsz += (a[i] != e);
        }

        item *temp;

        if( nsz <= cap/4 )
            cap = (cap/2 > 0 ) ? cap/2 : CAP;
        temp = new item[cap];

        nsz = 0;
        for(int i=0;i<sz;i++)
            if( a[i] != e )
                temp[nsz++] = a[i] ;
        sz = nsz;
        delete [] a;
        a = temp;
    }

    Array<int> findIndex(item e){
        Array<int> id;

        for(int i=0;i<sz;i++)
            if( a[i] == e )
                id.add(i);
        return id;
    }

    Array<item> subArray(int st,int en){
        if( st < 0 || en >= sz )
            throw "ERROR";
        if( st > en )
            throw "ERROR";
        
        Array<item> t(en-st+1);

        for(int i=st;i<=en;i++)
            t.add(a[i]) ;
        return t;
    }

    void merge(item A1[], int n1, item A2[], int n2){
        int i=0,j=0;

        while( i < n1 || j < n2 ){
            if( i >= n1 )
                add(A2[j++]);
            else if( j >= n2 )
                add(A1[i++]);
            else if( A1[i] < A2[j] )
                add( A1[i++] );
            else add( A2[j++] );
        }
    }

    int length(){
        return sz;
    }

    int isEmpty(){
        return (sz == 0);
    }

    void print(){
        for(int i=0;i<sz;i++){
            cout<<a[i]<<endl;
        }   
        cout<<endl;
    }

};


int main(){
    Array<string> b(30);
    
    b.add("perseverance");
    b.add("polyphia");
    b.add("jargon");
    b.add("social dilemma");
    b.add("return 0");
    b.add("slither");
    
    b.print();

    b.add(2,"joe satriani");
    b.add(0,"bujheso vai??");
    b.remove((string)"jargon");

    b.add("jalaton ibarahomovic");


    b.print();

    Array<string> c(b.subArray(1,3)) ;
    c.print();

    b.add("joe satriani");
    b.findIndex("joe satriani").print();


    string a1[] = {"a","b","c","e"} ;
    string a2[] = {"ab","b","d","f","g"};

    b.merge(a1,4,a2,5);


    b.print();

    b.findIndex("b").print();
    b.remove("b");

    b.print();
}