#include <iostream>
using namespace std;

template<class T> void merge_sort(T *array,T *aux,int st, int en, bool (*cmp)(T &p1,T &p2)){
    if( st>=en ) return ;
    if( en-st == 1 ){
        if( cmp(array[st],array[en]) ){}
        else 
            swap(array[st],array[en]);
        return ;
    }

    merge_sort(array,aux,st,(st+en)/2,cmp);
    merge_sort(array,aux,(st+en)/2+1,en,cmp);

    int i=st,I=(st+en)/2;
    int j=I+1,J=en;
    int id = st;
    while( i<=I || j<=J ){
        if( i>I )
            aux[id++] = array[j++];
        else if( j>J )
            aux[id++] = array[i++];
        else if( cmp(array[i],array[j]) )
            aux[id++] = array[i++];
        else aux[id++] = array[j++];
    }

    for(int i=st;i<=en;i++)
        array[i] = aux[i];
}
template<class T> void merge_sort(T array[],int n, bool (*cmp)(T &p1,T &p2) ){
    T *aux = new T[n];
    merge_sort(array,aux,0,n-1,cmp);
    delete [] aux;
    return;
}

bool less_int(int &a,int &b){
    return a<=b;
}

int main(){
    int n,k;
    cin>>n>>k;

    int a[n];
    for(int i=0;i<n;i++) 
        cin>>a[i];
    merge_sort(a,n,less_int);
    int ans = 0;
    int cnt = 0;
    int i = n-1;

    while( i>= 0 ){
        int m = (cnt/k) + 1;
        ans += a[i]*m;
        cnt++;
        i--;
    }
    cout<<ans<<endl;
}