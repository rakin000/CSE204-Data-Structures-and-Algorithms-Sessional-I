import java.util.NoSuchElementException;

public class stack<Type>{
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
    node _top;
    node _bottom;
    int N =0;

    public stack(){
        _top = null;
        _bottom = null;
        N = 0;
    }
    public int size(){
        return N;
    }
    public boolean empty(){
        return (_top == null);
    }
    public void push(Type value){
        node n_top = new node(value);
        if( _top == null ){
            _bottom = n_top ;
        }
        n_top.next = _top;
        _top = n_top;
        ++N;
    }
    public Type pop() throws NoSuchElementException{
        if(_top == null ) throw new NoSuchElementException("empty stack!!");
        // node old = _top ;
        Type val = _top.value;

        _top = _top.next;
        if( _top == null )
            _bottom = null;
        --N;
        return val;
    }
    public Type top() throws NoSuchElementException{
        if(_top == null) throw new NoSuchElementException("empty stack!!");
        return _top.value;
    }
    public Type bottom() throws NoSuchElementException{
        if( _bottom == null ) throw new NoSuchElementException("empty stack!!");
        return _bottom.value;
    }
}
/*

public class<Type> array_stack{

} */