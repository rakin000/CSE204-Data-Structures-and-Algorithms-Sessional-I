#include <iostream>
using namespace std;


class PillowPassing{
    static const int R = 1, L = -1; 
    int pCount;
    int dir; // {R,L}
    int T;
    int N = 0;
    struct Node{
        int rflxTime;
        int id;
        Node *left;
        Node *right;

        Node(int rT=0,int id=-1){
            this->rflxTime = rT;
            this->id = id;
        }
    };
    Node* cur = NULL;

    public:

    PillowPassing(int A[],int n){
        pCount = n; //sizeof(A)/sizeof(int);
        dir = R;
        T = 0;         
        cur = new Node(A[0],++N);

        if( pCount > 1){
            Node* last = cur;
            for(int i=1;i<pCount;i++){
                last->right = new Node(A[i],++N);
                last->right->left = last ;
                last = last->right;
            }
            last->right = cur;
            cur->left = last;
        }
    }

    ~PillowPassing(){
        if( pCount == 1 ) 
            delete cur;
        else {
            Node* last = cur;

            while( last->right != cur ){
                Node* tmp = last->right;
               // cout<<last->id<<",";
                delete last;
                last = tmp;
            }
          //  cout<<last->id<<endl;
            delete last;
        }
    }
    void start(){
        int time ;
        char command;
        int rt ;
        
        bool gameover = 0;

        while( 1 ){
            cin>>time;
            cin>>command;
            if( command == 'I')
                cin>>rt;
                
            if( !gameover )
                update(time);

            if( command == 'F' ){
                if( !gameover ){
                    printf("Game over: ");
                    printf("Player %d is holding the pillow at t=%d",idCur(),time);
                    printf(", pillow passing sequence = Player ");

                    Node* last = cur;

                    while( (dir == R && last->right != cur) || (dir == L && last->left != cur) ){
                        cout<<last->id<<",";
                        last = (dir == R) ? last->right: last->left;
                    }
                    cout<<last->id<<endl;
                }
                break;
            }

            if( playerCount() == 1){
                if( !gameover )
                    printf("Game over : Player %d wins!!\n",idCur());
                gameover = 1;
            }

            if( gameover )
                continue;

            if( command == 'P')
                printf("Player %d is holding the pillow at t=%d\n",idCur(),time);
            else if( command == 'M' ){
                printf("Player %d has been eliminated at t=%d\n",idCur(),time);
                eliminatePlayer(time);
            }
            else if( command == 'R' ){
                reverseDirection();
            }
            else if( command == 'I'){
                addPlayer(rt);
            }
        }
    }

    void reverseDirection(){
        dir = (dir == L) ? R: L;
    }

    void addPlayer(int rT){
        if(pCount == 1){
            return ;
        }

        Node *l,*r;
        if( dir == L )
            l = cur, r = cur->right;
        else 
            r = cur, l = cur->left;

        Node* n = new Node(rT,++N);
        n->right = r;
        n->left = l;
        r->left = n;
        l->right = n;

        pCount++;
    }

    void eliminatePlayer(int time){
        if( pCount == 1 ) return ;

        cur->left->right = cur->right ;
        cur->right->left = cur->left;

        Node* t = cur;

        cur = (dir == L) ? cur->left : cur->right;
        delete t;
        --pCount;
        T = time;
    }

    void update(int t){

        while( t > T+cur->rflxTime ){
            T += cur->rflxTime;  
            if( dir == L ) cur = cur->left;
            else cur = cur->right;
        }
    }

    int idCur(){
        return cur->id;
    }

    int playerCount(){
        return pCount;
    }
};



int main(){
    char c;
    int t;
    int n;
    cin>>n;
    int a[n];
   // cout<<sizeof(a)/sizeof(int)<<endl;
    for(int i=0;i<n;i++)
        cin>>a[i];
    PillowPassing game(a,n);
    game.start();
}