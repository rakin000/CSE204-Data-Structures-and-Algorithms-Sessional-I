import java.util.Scanner;

public class queue_old_new {
    public String s_new;

    public queue_old_new(String s){

        queue<Character> qq = new queue<>();
        final int N = 26 ;
        int occur[] = new int[N];
        StringBuffer s_n = new StringBuffer();
        for(int i=0;i<N;i++) occur[i] = 0;

        for(int i=0;i<s.length();i++){
            occur[s.charAt(i)-'a']++;
            
            if( occur[s.charAt(i)-'a'] == 1)
                qq.push(s.charAt(i));

            
            while( !qq.empty() && occur[qq.front()-'a'] > 1 ){
                qq.pop();
            }

            if( qq.empty() ) s_n.append('#');
            else             s_n.append(qq.front());
        }

        s_new = s_n.toString();
    }
    
    public static void main(String [] args){
        String s_old ;
        
        Scanner scn = new Scanner(System.in);

        while( scn.hasNextLine() ){
            s_old = scn.nextLine();
            queue_old_new q = new queue_old_new(s_old);
            System.out.println(q.s_new);
        }
        
    }
}
