//int n;
//n = 8;
int x=0;
int fibo(int n){
    int a = 0;
    int b= 1;
    int c;
    //int sum= 0;
    for(int i= 0; i<= n; i=i+1)
    {
        //printf("%d\t",a);
        //return a;//0,1,1,2
        c= a + b;//c=0+1;c=1+1;c=1+2
        a=b;//a=1;a=1,a=2,
        b=c;//b=1,b=2;b=3,
    }

    return a;
}


int main(){ //function main qui fait boucle infinite

    int result= fibo(8);
    return result;
    /*
    while(1) //boucle infinite
    {}
    */
}