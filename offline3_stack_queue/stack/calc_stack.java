import java.util.Scanner;


public class calc_stack {
    class Token{
        public static final int NUMBER = 0;
        public static final int ADD = 1;
        public static final int SUB = 2;
        public static final int MUL = 3;
        public static final int DIV = 4;
        public static final int LEFT_BRACE = 5;
        public static final int RIGHT_BRACE = 6;

        public double value;
        public int type;
        
        public Token(String s){
            if( s.length() > 1)             {   value = toNumber(s);    type = NUMBER; }
            else if( s.charAt(0) == '+' )   {   value = 0.0;    type = ADD;}
            else if( s.charAt(0) == '*' )   {   value = 0.0;    type = MUL;}
            else if( s.charAt(0) == '/' )   {   value = 0.0;    type = DIV;}
            else if( s.charAt(0) == '(')    {   value = 0.0;    type = LEFT_BRACE;}
            else if( s.charAt(0) == ')')    {   value = 0.0;    type = RIGHT_BRACE;}
            else if( s.charAt(0) == '-' )   {   value = 0.0;    type = SUB; }
            else if( Character.isDigit(s.charAt(0)) ){ value = toNumber(s);  type = NUMBER; }
        }

        private double toNumber(String s){
            double num = 0.0;
            int i = 0;
            double mul = 1.0;
            
            if( s.charAt(i) == '-'){
                mul = -1.0;
                i++;
            }
            while( i < s.length() && Character.isDigit(s.charAt(i)))
                num = num*10.0 + s.charAt(i++)-'0' ;
    
            if( i < s.length() && s.charAt(i) == '.' )
                i++;
            
            double div = 1.0;
    
            while( i < s.length() && Character.isDigit(s.charAt(i))){
                num = num*10.0 + s.charAt(i++)-'0' ;
                div *= 10.0;
            }        
            num = mul*num/div;
            //System.out.println(num);
            return num;
        }
        public String toString(){
            if( type == NUMBER )    return Double.toString(value);
            else if( type == ADD )  return "+";
            else if( type == SUB )  return "-";
            else if( type == MUL )  return "*";
            else if( type == DIV)   return "/";
            else if( type == LEFT_BRACE) return "(";
            else if( type == RIGHT_BRACE) return ")";
            return "";
        }
    }

    stack<Double> value;
    stack<Character> op;
    array_list<Token> tokens;
    
    double result;
    boolean valid = true;
    StringBuffer validityLog = new StringBuffer(); 
    

    public calc_stack(String s){
        tokens = new array_list<Token>();
        valid = true;
        
        checkRetardedValidity(s);
        tokenize(s);    
        checkValidity();

        if( valid ){
            System.out.println("Valid expression"); 
            value = new stack<>();
            op = new stack<>();
            calculate();
            System.out.println(result);  
        }
        else{
            System.out.println("Invalid expression");
            System.out.print(validityLog);
        }
    }   

    
    private void tokenize(String s){
        int i = 0;
        StringBuffer num;// = new StringBuffer();
        while( i < s.length() ){
            if( Character.isWhitespace(s.charAt(i)) ) {i++; continue; }
            
            if( s.charAt(i) == '(' ||
                s.charAt(i) == ')' || 
                s.charAt(i) == '+' || 
                s.charAt(i) == '-' ||
                s.charAt(i) == '*' ||
                s.charAt(i) == '/'      )
                tokens.add( new Token(s.charAt(i++)+"") ) ;   
            else if(   Character.isDigit( s.charAt(i) ) ){
                int mul = 1;
                int minus_plus_cnt = 0;
                while( !tokens.empty() && (tokens.getLast().type == Token.ADD || tokens.getLast().type == Token.SUB ) ){ // gobbles up strings like '-+++--+-++--+'
                    ++minus_plus_cnt;
                    if( tokens.pop_back().type == Token.SUB ) 
                        mul *= -1;
                }

                if( !tokens.empty() && minus_plus_cnt != 0 && (tokens.getLast().type == Token.NUMBER || tokens.getLast().type == Token.RIGHT_BRACE ) )
                    tokens.add(new Token("+") ); 

                num = new StringBuffer();
                if( mul == -1) num.append('-');
                while( i < s.length() && Character.isDigit( s.charAt(i) ) )
                    num.append(s.charAt(i++));
                
                if( i < s.length() && s.charAt(i) == '.' )
                    num.append(s.charAt(i++));
                
                while( i < s.length() && Character.isDigit( s.charAt(i) ) )
                    num.append(s.charAt(i++) );
                tokens.add(new Token(num.toString()) );
            }
            else { 
                valid = false; 
                validityLog.append("Invalid Operator: "+s.charAt(i)+"\n");
                i++; 
            }
        }
	/*
        for(int j=0;j<tokens.length();j++)
            System.out.print(tokens.get(j)+" ");
        System.out.println(); */
    }

    private boolean checkRetardedValidity(String s){ 
        StringBuffer sb = new StringBuffer();

        for(int i=0;i<s.length();i++){
            if( Character.isWhitespace(s.charAt(i)) ) continue;

            sb.append(s.charAt(i));
        }

        int i = 0;
        while(i < sb.length()) {
            if( sb.charAt(i) == '-'){
                if( (i-1>=0 && ( Character.isDigit(sb.charAt(i-1)) || sb.charAt(i-1) == ')' )) &&
                    (i+1<sb.length() && (Character.isDigit(sb.charAt(i+1)) || sb.charAt(i+1) == '(')) )  
                {}  // normal binary operator checking: 4+3, 4-3, (...)-(....)
                else if( (i-1>=0 && sb.charAt(i-1) == '(') && (i+1<sb.length() && sb.charAt(i+1) == '(' ) )
                {}      // checks expr like (-( .... )) 
                else if(    (i-1>=0 && sb.charAt(i-1) == '(') && 
                            (i+1<sb.length() && Character.isDigit(sb.charAt(i+1)) ) )
                {
                    int j = i;
                    ++i;
                    while( i<sb.length() && Character.isDigit(sb.charAt(i))){
                        i++;
                    }
                    if( i<sb.length() && sb.charAt(i) == '.') i++;
                    while( i<sb.length() && Character.isDigit(sb.charAt(i))){
                        i++;
                    }
                    
                    if( i<sb.length() && sb.charAt(i) == ')' ){}
                    else{
                        valid = false;
                        validityLog.append("[retarded invalidity] Binary operater: "+sb.charAt(j)+", invalid operands\n") ;
                    }

                    --i;
                } // checks expr like : (-43)
                else{ 
                    valid = false;
                    validityLog.append("[retarded invalidity] Binary operater: "+sb.charAt(i)+", invalid operands\n") ;
                }

            }
            else if( sb.charAt(i) == '+' ){
                if( (i-1>=0 && (Character.isDigit(sb.charAt(i-1)) || sb.charAt(i-1) == ')' )) &&
                    (i+1<sb.length() && (Character.isDigit(sb.charAt(i+1)) || sb.charAt(i+1) == '(')) )  
                {}
                else {
                    valid = false;
                    validityLog.append("[retarded invalidity] Binary operater: "+sb.charAt(i)+", invalid operands\n") ;
                }
            }

            i++;
        }
        return valid;
    }

    private boolean checkValidity(){
        if( valid == false ) return valid;
        int bracket = 0;
        for(int i=0;i<tokens.length();i++){
            if( tokens.get(i).type == Token.LEFT_BRACE ) 
                bracket++;
            else if( tokens.get(i).type == Token.RIGHT_BRACE )
                bracket--;
            if( bracket < 0 ){ // ))(, )(), ()()) etc;
                valid = false; 
                validityLog.append("Invalid bracket sequence: No opening brace for a closing brace\n"); 
            } 
            
            if( tokens.get(i).type == Token.LEFT_BRACE && i+1<tokens.length() && tokens.get(i+1).type == Token.RIGHT_BRACE ){  // () is not valid
                valid = false; 
                validityLog.append("Invalid bracket sequence: ()\n") ;
            }
            else if( tokens.get(i).type == Token.RIGHT_BRACE && i+1<tokens.length() && tokens.get(i+1).type == Token.LEFT_BRACE ){  // )( is not valid, why??? please explain.. could sub with * 
                valid = false; 
                validityLog.append("Invalid bracket sequence: )(\n") ;
            }
            else if(    tokens.get(i).type == Token.ADD ||
                        tokens.get(i).type == Token.MUL ||
                        tokens.get(i).type == Token.DIV ||
                        tokens.get(i).type == Token.SUB )  // right and left operand should be numbers or right = '(' and left = ')' 
            {
                if( (i-1>=0 && ( tokens.get(i-1).type == Token.NUMBER || tokens.get(i-1).type == Token.RIGHT_BRACE )) &&
                    (i+1<tokens.length() && (tokens.get(i+1).type == Token.NUMBER || tokens.get(i+1).type == Token.LEFT_BRACE )) )    
                {}
                else{ 
                    valid = false;
                    validityLog.append("Binary operater: "+tokens.get(i)+", invalid operands\n") ;
                }

                if( tokens.get(i).type == Token.DIV &&
                    i+1 < tokens.length() && tokens.get(i+1).type == Token.NUMBER && 
                    tokens.get(i+1).value == 0.0 
                ){ // division by 0 
                    valid = false; validityLog.append("divison by zero\n") ;
                }
            }
            else if( tokens.get(i).type == Token.NUMBER && (i+1<tokens.length()) && tokens.get(i+1).type == Token.NUMBER ){
                valid = false;
                validityLog.append("Two consecutive numbers without operator\n");
            }
        }

        if( bracket != 0 ){ 
            valid = false; 
            validityLog.append("Invalid bracket sequence: number of opening brace != number of closing brace\n"); 
        }

        return valid;
    }
    private double compute(double v1,double v2,char op){
        if( op == '+' ) return v1+v2;
        if( op == '*') return v2*v1;
        if( op == '/') return v2/v1;
        if( op == '-' ) return v2-v1;
        throw new RuntimeException("Invalid Operator");
    }
    private int priority(char op){
        if( op == ')' || op == '(' ) return 0;
        if( op == '+' || op == '-' ) return 1;
        if( op == '*' || op == '/' ) return 2;
        throw new RuntimeException("Invalid operator");
    }
    private void calculate(){
        int i = 0;

        while( i < tokens.length() ){
            if( tokens.get(i).type == Token.NUMBER ){
                value.push(tokens.get(i).value) ;
            }
            else if( tokens.get(i).type == Token.LEFT_BRACE )
                op.push('(');
            else if( tokens.get(i).type == Token.RIGHT_BRACE ){
                char operator ;
                double v1,v2;
                while( !op.empty() && op.top() != '(' ){
                    operator = op.pop();
                    
                    v1 = value.pop();
                    v2 = value.pop();
                    value.push(compute(v1,v2,operator));
                }

                if( !op.empty() )
                    op.pop();
            }
            else { // an operator , not () 
                char operator ;
                double v1,v2;
                while( !op.empty() && priority(tokens.get(i).toString().charAt(0)) <= priority(op.top()) ) {
                    operator = op.pop();
                    v1 = value.pop();
                    v2 = value.pop();

                    value.push(compute(v1,v2,operator));
                }

                op.push(tokens.get(i).toString().charAt(0));
            }
            
            i++;
        }
        
        char operator ;
        double v1,v2;
        while( !op.empty() ) {
            operator = op.pop();
            v1 = value.pop();
            v2 = value.pop();
            value.push(compute(v1,v2,operator));
        }
        
        result = (!value.empty()) ? value.pop():0.0;
    }
    public static void main(String[] args){
        String s ;//= "12*(-1)";// =  ;

        calc_stack cs ;//= new calc_stack(s);

        Scanner scn = new Scanner(System.in);
        while( scn.hasNextLine() ){
            s = scn.nextLine();
            //System.out.println(s);
            cs = new calc_stack(s);
        }
    }
}
