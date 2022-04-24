#include<stdio.h>
#include<conio.h>
int s_stack[50];
int s_top = -1;
char p_stack[50];
int p_top = -1;
void s_push (int item){
    if(s_top>=49){
        printf("stack overflow");
        return;
    }
    else{
        s_top = s_top +1;
        s_stack[s_top]=item;
    }
}
void p_push (char item){
    if(p_top>=49){
        printf("stack overflow");
        return;
    }
    else{
        p_top = p_top +1;
        p_stack[p_top]=item;
    }
}
int s_pop (){
    int item;
    if(s_top<0){
        printf("stack underflow");    
    }
    else{
    item= s_stack[s_top];
    s_top= s_top - 1;
    return item;
    }
}
char p_pop (){
    char item;
    if(p_top<0){
        printf("stack underflow");    
    }
    else{
    item= p_stack[p_top];
    p_top= p_top - 1;
    return item;
    }
}
void evaluate(char postfix[]){
    char elem;
    int i=0,j,k,a,b,ans;
    float temp,sqrt;
    while (postfix[i]!='\0'){
        elem = postfix[i];
        if (elem == '+'||elem == '-'||elem == '*'||elem == '/'||elem == '%'||elem == '^'||elem == '!'||elem == '|'||elem == 'v'){
            switch (elem){
                case '+': {
                	a= s_pop();
            		b= s_pop();
                	ans = b+a;
					break;
				}
                case '-': {
                	a= s_pop();
            		b= s_pop();
                	ans = b-a;
					break;
				}
                case '*': {
                	a= s_pop();
            		b= s_pop();
                	ans = b*a;
					break;
				}
                case '/': {
                	a= s_pop();
            		b= s_pop();
                	ans = b/a;
					break;
				}
                case '%': {
                	a= s_pop();
            		b= s_pop();
                	ans = b%a;
					break;
				}
                case '^': {
                	a= s_pop();
            		b= s_pop();
                    ans=1;
                    for (j=0; j<a; j++)
                    	ans *= b;
                    break;
                }
                case '!': {
                	a= s_pop();
            		ans=1;
            		for (k=1; k<=a; k++)
            			ans = ans*k;
					break;
				}
				case '|': {
					a= s_pop();
            		if (a<0)
            			ans = a*-1;
            		else
            			ans = a;
					break;
				}
				case 'v': {
					a= s_pop();
            		sqrt=a/2;
           			temp=0;
           			while (sqrt!=temp){
    					temp=sqrt;
    					sqrt=(a/temp+temp)/2;
						}
					ans=(int)sqrt;
					break;
				}
            }
            s_push(ans);
        }
        else{
            s_push(elem-'0');
        }    
        i++;
    }
}
int main(){
    char infix[50], postfix[50];
    char elem;
    int i=0, j=0;
    printf("Infix to Postfix Evaluator\nSupported operations: +, -, *, /, %%, ^, !, |, v");
    printf("\nPlease enter (without spaces) the Infix Expression\n: ");
    scanf("%s",infix);    
    while (infix[i]!='\0'){
        elem = infix[i];
        if (elem=='('){
            p_push(elem);
        }
        else if (elem==')'){
            while (p_stack[p_top]!='('){
                postfix[j] = p_pop();
                j++;
            }
            p_pop();
        }
        else if (elem== 'v'||elem== '|'){
        	while (p_stack[p_top]== 'v'||p_stack[p_top]== '|'){
      	        postfix[j]= p_pop();
       	        j++;
       	    }
        	p_push(elem);
        }
        else if (elem== '^'||elem== '!'){
        	while (p_stack[p_top]== 'v'||p_stack[p_top]== '|'||p_stack[p_top]== '^'||p_stack[p_top]== '!'){
      	        postfix[j]= p_pop();
       	        j++;
       	    }
        	p_push(elem);
        }
        else if (elem== '*'||elem== '/'||elem== '%'){
            while (p_stack[p_top]== 'v'||p_stack[p_top]== '|'||p_stack[p_top]== '^'||p_stack[p_top]== '!'||p_stack[p_top]== '*'||p_stack[p_top]== '/'||p_stack[p_top]== '%'){
      	        postfix[j]= p_pop();
       	        j++;
       	    }
        	p_push(elem);
        }
        else if (elem== '+'||elem== '-'){
            while (p_stack[p_top]== 'v'||p_stack[p_top]== '|'||p_stack[p_top]== '^'||p_stack[p_top]== '!'||p_stack[p_top]== '*'||p_stack[p_top]== '/'||p_stack[p_top]== '%'||p_stack[p_top]== '+'||p_stack[p_top]== '-'){
                postfix[j]= p_pop();
                j++;
            }
            p_push(elem);
        }
        else{
            postfix[j]=elem;
            j++;
        }
        i++;
    }
    while (p_top>=0){
        postfix[j]= p_pop();
        j++;
    }
    postfix[j]='\0';
    evaluate(postfix);
    printf("\nThe Postfix Expression is: %s\nThe answer is:  %d", postfix, s_pop());
    return 0;
}
