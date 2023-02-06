#include <iostream>
#include <cmath>
using namespace std;

struct point{
    double x = 0.0;
    double y = 0.0;
    int index;
   
    friend ostream& operator<<(ostream &out,point &p){
        out<<p.x<<" "<<p.y<<endl;
        return out;
    }
};
bool cmp_ymajor(point &p1, point &p2){
    return p1.y<=p2.y;
}
bool cmp_xmajor(point &p1, point &p2){
    return p1.x<=p2.x;
}
double distance(point &p1,point &p2){
    return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) ) ;
}

struct distance_index{
    double dist = 0;
    int i = -1;
    int j = -1;
} ;

bool cmp_distance_index(distance_index &di1,distance_index &di2){
    return di1.dist <= di2.dist;
}

struct distance_index_pair{
    distance_index di[2] = {{0,-1,-1},{0,-1,-1}};
} ;

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

double inf = 1e18;
point *strip;
int *side;
int max_loop_cnt = 0;

distance_index_pair calculate_distance(point *points_x, point* points_y, int points_y_size, int st,int en){
    if( st >= en )
        return {inf,-1,-1,inf,-1,-1};
    if( en-st == 1 )
        return {distance(points_x[st],points_x[en]),points_x[st].index,points_x[en].index,inf,-1,-1}; 
    

    int mid = (st+en)/2;
    point *points_y_left = new point[ (mid-st+1)+ 10]; // +10 or malloc gives error;
    point *points_y_right = new point[ (en-mid)+ 10]; // +10 or malloc gives error
    int I=0,J=0;
    for(int i=0;i<points_y_size;i++)
        if(points_y[i].x<=points_x[mid].x)
            points_y_left[I++] = points_y[i];
        else 
            points_y_right[J++] = points_y[i];
    

    distance_index_pair left = calculate_distance(points_x,points_y_left, I, st, mid);
    distance_index_pair right = calculate_distance(points_x,points_y_right, J, mid+1, en);
    distance_index dist_ind[4] = {left.di[0],left.di[1],right.di[0],right.di[1]};

    delete [] points_y_left;
    delete [] points_y_right;
   
    merge_sort(dist_ind,4,cmp_distance_index);
    double k = dist_ind[1].dist;
    
    int n = 0;
    int i = 0,j=0;
    distance_index strip_min = {inf,-1,-1};
    while( i<points_y_size ){
        if( abs(points_y[i].x-points_x[mid].x) < k ){
            strip[n] = points_y[i];
            side[n] = (points_y[i].x<=points_x[mid].x) ;
            n++; 
        }
        i++;
    }
    
    int loop_count = 0;
    for(i=0;i<n;i++){
        for(j=i+1;j<n && (strip[j].y-strip[i].y) < k; j++ ){
            if( (side[i]^side[j]) == 1 ){
                double temp_distance = distance(strip[i],strip[j]);
                if( strip_min.dist > temp_distance){
                    strip_min.dist = temp_distance;
                    strip_min.i = strip[i].index;
                    strip_min.j = strip[j].index;
                }
            }
            loop_count++;
        }
    }
    max_loop_cnt = max(max_loop_cnt,loop_count);
    //cout<<n<<" " <<loop_count<<endl;

    if( strip_min.dist < dist_ind[3].dist ){
        dist_ind[3] = strip_min;
    }
 
    merge_sort(dist_ind,4,cmp_distance_index);

    return {dist_ind[0],dist_ind[1]};
}


distance_index_pair calculate_distance1(point *points, point *points_y,int st,int en){
    if( st > en )
        return {inf,-1,-1,inf,-1,-1};
    if( st == en )
        return {inf,-1,-1,inf,-1,-1};
    if( en-st == 1 ){
        return {distance(points[st],points[en]),points[st].index,points[en].index,inf,-1,-1}; 
    }
    if( en-st == 2 ){
        distance_index dist_ind[3] ;
        int id = 0;
        for(int i=st;i<=en;i++)
            for(int j=i+1;j<=en;j++)
                dist_ind[id++] = {distance(points[i],points[j]),points[i].index,points[j].index};
        merge_sort(dist_ind,3,cmp_distance_index);
        return {dist_ind[0],dist_ind[1]};
    }

    int mid = (st+en)>>1;
    distance_index_pair left = calculate_distance1(points,points_y,st,mid);
    distance_index_pair right = calculate_distance1(points,points_y,mid+1,en);
    distance_index dist_ind[4] = {left.di[0],left.di[1],right.di[0],right.di[1]};
    merge_sort(dist_ind,4,cmp_distance_index);

    double k = dist_ind[1].dist;
  //  point *points_y = new point[en-st+1];
    int id = 0;
    for(int i=st;i<=en;i++)
        points_y[id++] = points[i];
    merge_sort(points_y,id,cmp_ymajor);

    distance_index strip_min = {inf,-1,-1};
    int i = 0,j;
    int n= 0;
    while( i<id ){
        if( abs(points_y[i].x-points[mid].x) < k ){
            strip[n] = points_y[i];
            side[n] = (points_y[i].x<=points[mid].x) ;
            n++; 
        }
        i++;
    }


    int loop_count = 0;
    for(i=0;i<n;i++){
        for(j=i+1;j<n && (strip[j].y-strip[i].y) < k; j++ ){
            if( (side[i]^side[j]) == 1 ){
                double temp_distance = distance(strip[i],strip[j]);
                if( strip_min.dist > temp_distance){
                    strip_min.dist = temp_distance;
                    strip_min.i = strip[i].index;
                    strip_min.j = strip[j].index;
                }
            }
            loop_count = max(loop_count,j-i);
        }
    }
    max_loop_cnt = max(max_loop_cnt,loop_count);
    //cout<<n<<" " <<loop_count<<endl;

    if( strip_min.dist < dist_ind[3].dist ){
        dist_ind[3] = strip_min;
    }
 
    merge_sort(dist_ind,4,cmp_distance_index);

    return {dist_ind[0],dist_ind[1]};
}


point *points_y_aux;
distance_index_pair calculate_distance2(point *points_x, point* points_y,int st,int en){
    if( st > en )
        return {inf,-1,-1,inf,-1,-1};
    if( st == en ){
        points_y[st] = points_x[st];
        return {inf,-1,-1,inf,-1,-1};
    }
    if( en-st == 1 ){
        for(int i=st;i<=en;i++)
            points_y[i] = points_x[i];
        merge_sort(points_y+st,2,cmp_ymajor);
        return {distance(points_x[st],points_x[en]),points_x[st].index,points_x[en].index,inf,-1,-1}; 
    }
    if( en-st == 2){
        for(int i=st;i<=en;i++)
            points_y[i] = points_x[i];
        merge_sort(points_y+st,3,cmp_ymajor);

        distance_index dist_ind[3] ;
        int id = 0;
        for(int i=st;i<=en;i++)
            for(int j=i+1;j<=en;j++)
                dist_ind[id++] = {distance(points_x[i],points_x[j]),points_x[i].index,points_x[j].index};
        merge_sort(dist_ind,3,cmp_distance_index);
        return {dist_ind[0],dist_ind[1]};
    }

    int mid = (st+en)/2;
    distance_index_pair left = calculate_distance2(points_x,points_y, st, mid);
    distance_index_pair right = calculate_distance2(points_x,points_y, mid+1, en);
    distance_index dist_ind[4] = {left.di[0],left.di[1],right.di[0],right.di[1]};
   
    merge_sort(dist_ind,4,cmp_distance_index);
    double k = dist_ind[1].dist;
    
    int I = mid;
    int J = en;
    int i = st,j=mid+1;
    int id = st;
    int n = 0;
    while( i<=I || j<=J ){
        if( i>I )
            points_y_aux[id++] = points_y[j++];
        else if( j>J )
            points_y_aux[id++] = points_y[i++];
        else if( cmp_ymajor(points_y[i],points_y[j]))
            points_y_aux[id++] = points_y[i++];
        else points_y_aux[id++] = points_y[j++];
    }
    for(i=st;i<=en;i++)
        points_y[i] = points_y_aux[i];
    
    distance_index strip_min = {inf,-1,-1};
    i = st;
    while( i<=en ){
        if( abs(points_y[i].x-points_x[mid].x) < k ){
            strip[n] = points_y[i];
            side[n] = (points_y[i].x<=points_x[mid].x) ;
            n++; 
        }
        i++;
    }
    
    int loop_count = 0;
    for(i=0;i<n;i++){
        for(j=i+1;j<n && (strip[j].y-strip[i].y) < k; j++ ){
            if( (side[i]^side[j]) == 1 ){
                double temp_distance = distance(strip[i],strip[j]);
                if( strip_min.dist > temp_distance){
                    strip_min.dist = temp_distance;
                    strip_min.i = strip[i].index;
                    strip_min.j = strip[j].index;
                }
            }
            loop_count = max(loop_count,j-i);
        }
    }
    max_loop_cnt = max(max_loop_cnt,loop_count);
    //cout<<n<<" " <<loop_count<<endl;

    if( strip_min.dist < dist_ind[3].dist ){
        dist_ind[3] = strip_min;
    }
 
    merge_sort(dist_ind,4,cmp_distance_index);

    return {dist_ind[0],dist_ind[1]};
}


int main(){
   // freopen("input1","r",stdin);
    int n;
    cin>>n;
    point *points_x = new point[n];
    point *points_y = new point[n];
    
    for(int i=0;i<n;i++) {
        cin>>points_x[i].x>>points_x[i].y;
        points_x[i].index = i;
       // points_y[i] = points_x[i];
    }
    merge_sort(points_x,n,cmp_xmajor);
 //   merge_sort(points_y,n,cmp_ymajor);
    strip = new point[n];
    side = new int[n];
    points_y_aux = new point[n];

    clock_t clk = clock();
    distance_index_pair ans = calculate_distance1(points_x,points_y,0,n-1);// calculate_distance2(points_x,points_y,0,n-1);
    
    cout<<"Calculated second min_dist: "<<ans.di[1].dist<<endl;
    cout<<"Second min indices : "<<ans.di[1].i<<" "<<ans.di[1].j<<endl;
    cout<<"Time taken: "<<(double) (clock()-clk) / CLOCKS_PER_SEC <<endl;
    cout<<"Max Loop Count: "<<max_loop_cnt<<endl;
    delete [] points_x;
    delete [] points_y;
    delete [] points_y_aux;
    delete [] strip;
    delete [] side;
}