#include<iostream>
using namespace std;

int main(){
    freopen("input4","w",stdout);
    cout<<100000<<endl;
    for(int i=0;i<100000;i++){
        int x = rand()%(int)(1e6)-50000;
        int y = rand()%(int)(1e6)-50000;
        cout<<x<<" "<<y<<endl;
    }
}