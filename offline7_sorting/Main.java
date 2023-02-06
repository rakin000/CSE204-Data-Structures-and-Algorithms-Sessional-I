import java.util.Scanner;
import java.util.Random;

class sort{
    private static void swap(int [] arr, int i, int j){
        int temp = arr[i] ;
        arr[i] = arr[j];
        arr[j] = temp;
    }
    public static boolean is_sorted_descending(int arr[]){
        for(int i=0;i<arr.length-1;i++)
            if( arr[i] < arr[i+1] )
                return false;
        return true;    
    }
    public static boolean is_sorted_ascending(int arr[]){
        for(int i=0;i<arr.length-1;i++){
            if(arr[i] > arr[i+1] )
                return false;
        }
        return true;
    }

    public static void merge_sort(int [] arr){
        int [] aux = new int[arr.length];
        merge_sort(arr,aux,0,arr.length-1);
        assert is_sorted_ascending(arr) == true ;
    }

    private static void merge_sort(int [] arr, int aux[], int st, int en){
        if( st>=en) 
            return ;
        if( en-st == 1 ){
            if( arr[st] > arr[en] ){
                swap(arr,st,en);
            }
            return ;
        }

        merge_sort(arr, aux, st,(st+en)>>1) ;
        merge_sort(arr, aux, ((st+en)>>1)+1,en);

        int i=st,I=(st+en)>>1;
        int j=I+1,J=en ;
        int id = st ;
        while( i<=I || j<=J ){
            if( i > I )
                aux[id++] = arr[j++];
            else if( j > J )
                aux[id++] = arr[i++];
            else if( arr[i] < arr[j] )
                aux[id++] = arr[i++];
            else aux[id++] = arr[j++];
        }

        for(int i2=st;i2<=en;i2++)
            arr[i2] = aux[i2] ;
    }

    public static void quick_sort(int [] arr){
        quick_sort(arr,0,arr.length-1);
        assert is_sorted_ascending(arr) == true ;
    }
    private static void quick_sort(int [] arr, int st, int en ){
        if( st >= en )
            return ;
        if( en-st == 1 ){
            if( arr[st] > arr[en] ){
                swap(arr,st,en);
            }
            return ;
        }

        int i = st;
        int j = st+1;
        int pivot_id = st;
        while( j<=en){
            if( arr[j] < arr[pivot_id] ){
                swap(arr,j,++i);
            }
            j++;
        }
        swap(arr,pivot_id,i);
        quick_sort(arr,st,i-1);
        quick_sort(arr,i+1,en);
    }
}


public class Main {
    static Scanner in = new Scanner(System.in);
    static final int RANGE = 1000;

    private static void swap(int [] arr, int i, int j){
        int temp = arr[i] ;
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static int[] generate_random_integers(int n,int order){
        int arr[] = new int[n];
        Random rand = new Random();
        int x = Integer.MIN_VALUE+(1+Math.abs(rand.nextInt()%RANGE));

        for(int i=0;i<n/2;i++){
            arr[i] = x;
            int inc = 1+Math.abs(rand.nextInt()%RANGE);
            x = x + inc ;
        }

        x = Integer.MAX_VALUE-(1+Math.abs(rand.nextInt()%RANGE));
        for(int i=n-1;i>=n/2;i--){
            arr[i] = x;
            int inc = 1+Math.abs(rand.nextInt()%RANGE);
            x = x - inc ;
        }

        assert sort.is_sorted_ascending(arr) == true ;

        if( order == 1){}
        else if( order == 2){
            for(int i=0,j=n-1;i<j;i++,j--){
                swap(arr,i,j);
            }
        }
        else if( order == 3){
            for(int i=0;i<arr.length;i++){
                int j = i+Math.abs(rand.nextInt()%(arr.length-i));
                swap(arr,i,j);
            }
        }
        return arr;
    }
    public static void main(String args[]){
        if( args.length >= 1 && args[0].equals("-s") ){
            while(true)
                simulate_for_results();
        }
        else 
        while(true){
            System.out.print("Number of integers to generate: ");
            int n = in.nextInt();
            System.out.println("1 -> Ascending Random Numbers");
            System.out.println("2 -> Descending Random Numbers");
            System.out.println("3 -> Random Numbers in Random Order");
            int m = in.nextInt();
            int array[] = generate_random_integers(n, m);
            int array2[] = new int[n];
            for(int i=0;i<n;i++) array2[i] = array[i];

            long clk = System.nanoTime();
            sort.quick_sort(array);
            System.out.println("Quick sort takes " + (double)(System.nanoTime()-clk)/1e6 + " ms");
            
            clk = System.nanoTime();
            sort.merge_sort(array2);
            System.out.println("Merge sort takes " + (double)(System.nanoTime()-clk)/1e6 + " ms");

            System.out.println("Print??(y/n) ");
            char c = in.next().charAt(0);
            
            if( c == 'y' || c == 'Y' ){
                System.out.println(" Quicksort\t\t\t Mergesort");
                System.out.println("================================================");
                for(int i=0;i<n;i++){
                    ///cout<<array[i]<<"\t\t"<<array2[i]<<endl;
                    System.out.println(array[i]+"\t\t\t"+array2[i]);
                }
            }
        }
    }

    public static void simulate_for_results(){
        int n = in.nextInt();
        int m = in.nextInt();
        int count = in.nextInt();
        double avg_quick = 0.0, avg_merge=0.0;
        for(int c=0;c<count;c++){
            int arr[] = generate_random_integers(n,m);
            int arr2[] = new int[n];
            for(int i=0;i<n;i++) arr2[i] = arr[i];

            long clk = System.nanoTime();
            sort.quick_sort(arr);
            avg_quick += (double)(System.nanoTime()-clk)/1e6;

            clk = System.nanoTime();
            sort.merge_sort(arr);
            avg_merge += (double)(System.nanoTime()-clk)/1e6;
        }

        System.out.println("QuickSort : "+ avg_quick/count );
        System.out.println("Mergesort : "+ avg_merge/count ); 
    }
}
