#include <iostream>
#include <fstream>
#include "array_list.hpp"
#include "queue.hpp" 
using namespace std;

const int MAX_C = 2000+5;
const int MAX_F = 100 + 5;
array_list<int> adj[MAX_C];
int visited[MAX_C] ;
int hidden_value_location[MAX_C] ;
int starting_loc_id[MAX_F] ;
int collected[MAX_F];
int C,R,L,F;

int current_id ;

int total_collected ;
int possible_collection;

void bfs(int);
void dfs(int);

void solve(void (*traverse_func)(int u) ){
    total_collected = 0;
    possible_collection = 0;
    for(int i=0;i<=C;i++){
        visited[i] = 0;
        possible_collection += hidden_value_location[i];
    }
    for(int i=0;i<=F;i++)
        collected[i] = 0;

    for(int i=0;i<F;i++){
        if( starting_loc_id[i] != -1 && !visited[ starting_loc_id[i] ] ){
            current_id = i;
            traverse_func(starting_loc_id[i]);
            total_collected += collected[i];
        }
    }
}


void dfs(int u){
    visited[u] = 1;
    collected[current_id] += hidden_value_location[u] ;
    
    for(int i=0;i<adj[u].size();i++){
        int v = adj[u][i];
        if( !visited[v] )
            dfs(v);
    }
}

void bfs(int u){
    queue<int> qq;

    qq.push(u);
    visited[u] = 1;
    collected[current_id] += hidden_value_location[u];
    while( !qq.empty() ){
        int u_ = qq.pop();
        for(int i=0;i<adj[u_].size();i++){
            int v = adj[u_][i];

            if( !visited[v] ){
                visited[v] = 1;
                collected[current_id] += hidden_value_location[v];
                qq.push(v);
            }
        }
    }
}

int main(){
    cin>>C>>R>>L>>F;

    for(int i=0;i<=C;i++){
        adj[i].clear();
        hidden_value_location[i] = 0;
    }
    for(int i=0;i<=F;i++){
        starting_loc_id[i] = -1;
    }

    for(int i=0;i<R;i++){
        int u,v;
        cin>>u>>v;
        adj[u].add(v);
        adj[v].add(u);
    }

    for(int i=0;i<L;i++){
        int cx,px;
        cin>>cx>>px;
        hidden_value_location[cx] = px;
    }
    for(int i=0;i<F;i++){
        int cy,fy;
        cin>>cy>>fy;
        starting_loc_id[fy] = cy;
    }

    solve(dfs);
   // cout<<"called solve successfully \n";

    fstream output;
    output.open("out.txt",ios::out);
    if( total_collected == possible_collection )
        output<<"Mission Accomplished\n";
    else
        output<<"Mission Impossible\n";

    output<<total_collected<<" out of "<<possible_collection<<" pieces are collected\n";
    for(int i=0;i<F;i++)
        output<<i<<" collected "<<collected[i]<<" pieces"<<endl;
    output.close();
}
