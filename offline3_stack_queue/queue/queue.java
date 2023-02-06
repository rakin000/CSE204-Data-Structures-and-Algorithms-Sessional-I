import java.util.NoSuchElementException;

public class queue<Type>{
    public class node{
        Type value;
        node next;

        public node(Type value){
            this.value = value;
            next = null;
        }
        public node(){
            next = null;
        }
    }
    node _front;
    node _back;
    int N;
    public queue(){
        _front = null;
        _back = null;
        N = 0;
    }
    public int size(){
        return N;
    }
    public boolean empty(){
        return (_front == null);
    }
    public void push(Type value){
        if( _front == null ){
            _front = new node(value);
            _back = _front ;
        }
        else {
            _back.next = new node(value);
            _back = _back.next;
        }
        ++N;
    }
    public Type pop() throws NoSuchElementException {
        if(_front == null) throw new NoSuchElementException("empty queue");
        Type temp = _front.value;
        _front = _front.next;
        --N;

        return temp;
    }
    public Type front() throws NoSuchElementException {
        if(_front == null) throw new NoSuchElementException("empty queue");
        return _front.value;
    }
    public Type back() throws NoSuchElementException {
        if( _back == null ) throw new NoSuchElementException("empty queue");
        return _back.value;
    }
}
