import java.util.NoSuchElementException;

public class array_list<Item>{
    static final int CAP = 4;
    Item [] a;
    int sz;
    int cap = CAP;
  
    public array_list(int n){
        sz = 0;
        cap = n;
        a = (Item[])new Object[cap];       
    }
    public array_list(){
        this(CAP);
    }
    public array_list(Item A[]){
        cap = A.length;
        a = (Item[])new Object[cap]; 
        sz = 0;

        for(int i=0;i<cap;i++){
            a[sz++] = A[i];
        }
    }

    private void resize(int size) {
        if( size < 1 || size < sz ) throw new IllegalArgumentException();

        Item [] temp = (Item[]) new Object[size];

        for(int i=0;i<sz;i++)
            temp[i] = a[i];
        a = temp;
        cap = size;
    }
    public int length(){
        return sz;
    }
    public boolean empty(){
        return (sz == 0);
    }

    public Item[] getarray_list(){
        return a;
    }

    public Item get(int i) throws NoSuchElementException {
        if( i < 0 || i >= sz )
            throw new NoSuchElementException("Invalid index");
        return a[i];
    }
    public Item getLast() throws NoSuchElementException {
        if( empty() ) throw new NoSuchElementException("empty arraylist");
        return a[sz-1];
    }
    public void add(Item e){
        if( sz == cap )
            resize(cap*2);
        
        a[sz++] = e;
    }

    public void add(int i,Item e){
        add(e);

        for(int j=sz-1;j>i;j--){
            Item temp = a[j];
            a[j] = a[j-1];
            a[j-1] = temp;
        }
    }

    public Item pop_back(){
        if( empty() ) throw new NoSuchElementException("Empty arraylist!!");

        Item t = a[--sz];

        if( sz <= cap/4 ){
            cap = (cap/2>0)?cap/2:CAP;
            resize(cap);
        }

        return t;
    }

    public array_list<Integer> findIndex(Item e){
        array_list<Integer> id = new array_list<>();

        for(int i=0;i<sz;i++)
            if( a[i].equals(e) )
                id.add(i);
        return id;
    }
   
}