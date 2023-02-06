import java.util.Scanner;
import java.util.NoSuchElementException;

public class BSTint{
    class Node{
        int value;
        Node right;
        Node left;
        int size;

        public Node(int value){
            this.value = value;
            right = null;
            left = null;
            size = 1;
        }
    }
    Node root;

    public BSTint(){
        root = null;
    }

    private int getSize(Node x){
        return (x == null) ? 0: x.size;
    }
    public int getSize(){
        return getSize(root);
    }

    private Node getMinItem(Node x){
        if( x == null) throw new NullPointerException("getMinItem(x): ");

        while( x.left != null ){
            x = x.left;
        }
        return x;
    }
    public int getMinItem(){
        if( root == null ) throw new NoSuchElementException("Empty Tree");

        return getMinItem(root).value;
    }

    private Node getMaxItem(Node x){
        if( x == null) throw new NullPointerException("getMaxItem(x): ");

        while( x.right != null ){
            x = x.right;
        }
        return x;
    }
    public int getMaxItem(){
        if( root == null ) throw new NoSuchElementException("Empty Tree");

        return getMaxItem(root).value;
    }
    
    private Node insertItem(Node x, int val){
        if( x == null){
            x = new Node(val);
            return x;
        }
        
        if( val < x.value)
            x.left = insertItem(x.left,val);
        else if( val > x.value)
            x.right = insertItem(x.right,val);
        
        x.size = 1+getSize(x.left) + getSize(x.right);
        return x;
    }
    public void insertItem(int val){
        root = insertItem(root,val);
    }
    
    private Node searchItem(Node x,int val){
        if( x == null) 
            return x;

        if( val < x.value )
            return searchItem(x.left, val);
        else if( val > x.value)
            return searchItem(x.right,val);
        return x;
    }
    public void searchItem(int val){
        Node found = searchItem(root,val);

        if( found == null) 
            System.out.println(val+" has not been found!!");
        else System.out.println(val+" has been found!!");
    }

    private Node deleteItem(Node x,int val){
        if( x == null) return null;

        if( x.value == val ){
            if( x.right == null && x.left == null) // leaf
                return null;
            else if( x.right != null && x.left != null){  // full 
                Node rightMin = getMinItem(x.right);
                x.value = rightMin.value;
                x.right = deleteItem(x.right,rightMin.value);
            }
            else if( x.right != null)  // one child
                x = x.right ;
            else if( x.left != null)    // one child
                x = x.left ;

            x.size = 1 + getSize(x.left) + getSize(x.right);
            return x;
        }

        if( val < x.value ){
            x.left = deleteItem(x.left,val);
        }
        else if( val > x.value) 
            x.right = deleteItem(x.right,val);
        
        x.size = 1 + getSize(x.left) + getSize(x.right);
        return x;
    }
    public void deleteItem(int val){
        root = deleteItem(root,val);
    }   

    private int getItemDepth(Node x,int val){
        if( x == null ) return 0;

        if( val > x.value ) 
            return 1 + getItemDepth(x.right,val);
        else if( val < x.value)
            return 1 + getItemDepth(x.left,val);
        else return 0;
    }
    public int getItemDepth(int val){
        if( searchItem(root, val) == null ) return -1;
        else return getItemDepth(root,val);
    }

    public int getInOrderSuccessor(int val){
        Node x = searchItem(root, val);

        if( x == null ) return -1;
  
        x = root;
        Integer sc = null;
        while( x != null){
            if( x.value <= val )
                x=x.right ;
            else{
                sc = (sc == null || sc > x.value) ? x.value : sc ;
                x=x.left;
            }
        }
        return (sc == null) ? -1 : sc;
    }
    public int getInOrderPredecessor(int val){
        Node x = searchItem(root, val);

        if( x == null ) return -1;
  
        x = root;
        Integer pd = null;
        while( x != null){
            if( x.value >= val )
                x=x.left ;
            else{
                pd = (pd == null || pd < x.value ) ? x.value : pd ;
                x=x.right;
            }
        }
        return (pd == null) ? -1 : pd;
    }
    private void printInOrder(Node x){
        if( x == null ) return;

        printInOrder(x.left);
        System.out.print(x.value+" ");
        printInOrder(x.right);
    }
    public void printInOrder(){
        printInOrder(root);
        System.out.println();
    }

    private void printPreOrder(Node x){
        if( x == null ) return ;

        System.out.print(x.value+" ");

        printPreOrder(x.left);
        printPreOrder(x.right);
    }
    public void printPreOrder(){
        printPreOrder(root);
        System.out.println();
    }

    private void printPostOrder(Node x){
        if( x == null ) return ;

        printPostOrder(x.left);
        printPostOrder(x.right);
        System.out.print(x.value+" ");
    }
    public void printPostOrder(){   
        printPostOrder(root);
        System.out.println();
    }

    private int getHeight(Node x){
        if( x == null ) return 0;
        if( x.right == null && x.left == null) return 0;

        int leftHeight = getHeight(x.left);
        int rightHeight = getHeight(x.right);

        return 1+ ((leftHeight>rightHeight) ? leftHeight : rightHeight);
    }
    public int getHeight(){
        return getHeight(root);
    }


    public static void main(String args[]){

        BSTint bst = new BSTint();
        Scanner scn = new Scanner(System.in);
        System.out.println("1. insertItem\n2. searchItem\n3. getInOrderSuccessor\n4. getInOrderPredecessor\n5. deleteItem\n6. getItemDepth\n7. getMaxItem\n8. getMinItem\n9. getHeight\n10. printInOrder\n11. printPreOrder\n12. printPostOrder\n13. getSize\n");
        
        while( true ){
            int c = scn.nextInt();
            int val;
            int tmp ;
            switch(c){
                case 1: 
                    System.out.println("[Insert]: ");
                    val = scn.nextInt();
                    bst.insertItem(val);
                    break;
                case 2:
                    System.out.println("[Search]: ");
                    val = scn.nextInt();
                    bst.searchItem(val);
                    break;
                case 3: 
                    System.out.println("[Successor of]: ");
                    val = scn.nextInt();
                    System.out.println(bst.getInOrderSuccessor(val));
            
                    break;
                case 4:
                    System.out.println("[Predecessor of]: ");
                    val = scn.nextInt();
                    System.out.println(bst.getInOrderPredecessor(val));
         
                    break;
                case 5:
                    System.out.println("[Delete]:");
                    val = scn.nextInt();
                    bst.deleteItem(val);
                    break;
                case 6: 
                    System.out.println("[getDepth]: ");
                    val = scn.nextInt();
                    System.out.println(bst.getItemDepth(val));
                    break;
                case 7:
                    System.out.println("MaxItem: "+bst.getMaxItem());
                    break;
                case 8:
                    System.out.println("MinItem: "+bst.getMinItem());
                    break;
                case 9:
                    System.out.println("Height: "+bst.getHeight());
                    break;
                case 10:
                    System.out.println("InOrder:");
                    bst.printInOrder();
                    break;
                case 11:
                    System.out.println("PreOrder:");
                    bst.printPreOrder();
                    break;
                case 12:
                    System.out.println("PostOrder:");
                    bst.printPostOrder();;
                    break;
                case 13:
                    System.out.println("Size:"+bst.getSize());
                    break;
                default:
                System.out.println("1. insertItem\n2. searchItem\n3. getInOrderSuccessor\n4. getInOrderPredecessor\n5. deleteItem\n6. getItemDepth\n7. getMaxItem\n8. getMinItem\n9. getHeight\n10. printInOrder\n11. printPreOrder\n12. printPostOrder\n13. getSize\n");
                    break;
            }
        }
    }
}