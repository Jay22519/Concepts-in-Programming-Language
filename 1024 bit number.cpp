/** CPL Assignment

Name -> Jay Puri Goswami
Enrollment Number -> BT18CSE***

Implementing a 1024 bits number
And perform operation like Addition , Subtraction , Multiplication and Division

As we know that 2^3 is nearly 10^1 . So a 2^n number will have nearly n/3 digits in it's decimal
format . So a 1024 bits number will have 1024/3 with some factor difference which comes out to be ~= 309 digits in it's decimal format .


**/

/** This is a comment added through command terminal and will be later added through git **/

#include<bits/stdc++.h>
using namespace std ;

int num_random[] = {0,1,2,3,4,5,6,7,8,9} ;

int random_generator()
{
    return num_random[rand()%10];
}

/** The struct below is a wrapper for taking the string input of the number and the sign of the number */


/** A utility function for struct  BigData of the same return type that will help in assigning a string input of number to the struct **/

 string value(string S , int *sign)
{
    string s  ;
    s = S ;
    if(S[0] == '-')
    {
        *sign = 1 ;
        s.erase(0,1) ;
    }
    else
    {
        *sign = 0 ;
    }

    return s ;
}


/**string random_number()
{
    string a ;
    for(int i = 0 ; i<10 ; i++)
    {
        a +=(random_generator() + '0') ;
    }
    cout<<"Number is \t"<<a<<"\n" ;
    return a ;

} **/

/** This is the function declaration for both add and subtract function so that there is no error
while doing a mutual recursion between **/

int add(string , string , int sign_a , int sign_b  , int sign_decider) ;
int subtract(string , string ,  int sign_a ,int sign_b ) ;
int  multiply(string , string) ;


/** Decider function decided whether this function was call for addition or
addition as a substitute for Subtraction **/

/** Decider  = 0 for addition
Decider = 1 for Subtraction **/

/** sign_decide decides the sign of result **/
/** Though it increases the parameter but make sures that the main function and the user interface is clean **/
int  add(string a , string b , int a_sign , int b_sign , int sign_decide)
{
    string result ="" ;

    int a_ret  = 0 ;

    //result.sign = sign_decide ;

         int a_len = a.length() ;
         int b_len = b.length() ;
         if(a_len < b_len)
         {
             string temp =a; a = b ; b = temp ;
             int len = a_len ; a_len = b_len ; b_len = len ;
             int signn = a_sign ; a_sign = b_sign ; b_sign = signn ;
         }

         int carry = 0  ; int temp  ;
         int i ;  int len1 = a_len , len2 = b_len ;
         for(i = 0 ; i<b_len ; i++)
         {

             temp = ((a[len1-1-i] - '0') + (b[len2-1-i] - '0') + carry) ;
             result+=(temp%10) + '0' ;
             carry = temp/10 ;
         }
         for(i = b_len ; i<a_len ; i++)
         {
             temp = (a[len1-1-i] +  carry) - '0' ;
             result += (temp%10) + '0' ;
             carry = temp/10 ;
         }

         if(carry>0)
         {
             result += carry + '0' ;
         }

         if(sign_decide || (a_sign + b_sign == 2))
         {
             cout<<"-" ;
         }

         //cout<<"Temp\t"<<result[0]<<result[1]<<"\n" ;

        reverse(result.begin(), result.end());
        i = 0 ; int len = result.length() ;
        while(result[0] == '0' && i<len)
        {
            result.erase(0,1) ;
            i+=1 ;
        }
        if(i == len)
        {
            cout<<"0\n" ;
        }
        else
        {
            cout<<result<<"\n" ;
        }


    return a_ret ;
} //End of addition function ;


/** Again here also decider decides whether the function call is for subtraction
or subtraction as a substitute of additon **/

/** Decider = 0 means subtraction
Decider = 1 means addition **/
int subtract(string a , string b , int a_sign , int b_sign )
{
    string result = "" ;

    int a_ret = 0  ;


        /** Now wel'll make sure that string "a" is bigger than string "b" in length ; **/

        int a_len = a.length() ;
        int b_len = b.length() ;
        int swap_done = 0 , sign_changer = 0 ;
        /** swap_done is 1 , is the swap is done , so in that case the number should be negative as "b" was greater
        than "a" **/
        if(a_len < b_len)
        {
            string temp =a; a = b ; b = temp ;
            int len = a_len ; a_len = b_len ; b_len = len ;
            int signn = a_sign ; a_sign = b_sign ; b_sign = signn ;
            swap_done = 1 ; sign_changer = 1 ;
        }
        else if(a_len == b_len)
        {
            if(a.compare(b) < 0)
            {
                swap(a,b) ;
                //int len = a_len ; a_len = b_len ; b_len = len ;

                swap_done = 1 ;
            }
            if(swap_done == 1 && (a_sign  == b_sign))
            {
                sign_changer = 1 ;
            }
            else if(swap_done ==0 && (a_sign != b_sign))
            {
                sign_changer = 1 ;
            }
        }
        int temp = 0 ;
        for(int i = 0 ; i<b_len ; i++)
        {
            if((a[a_len -1 -i] - '0') >= (b[b_len - 1 - i] - '0'))
            {
                temp = ((a[a_len -1 -i] - '0') - (b[b_len - 1 - i] - '0')) ;
                result += (temp%10 + '0') ;
            }
            else
            {
               a[a_len -1 -i] = (((a[a_len -1 -i] - '0') + 10) + '0') ;
               int j = i ;

               while(a[a_len -1 - (j+1)] == '0')
               {
                   a[a_len -1 - (j+1)] = '9' ;
                   j+=1 ;
               }
               a[a_len -1 - (j+1)] = ((a[a_len -1 - (j+1)] - '0')  - 1 ) + '0' ;

                temp = ((a[a_len -1 -i] - '0') - (b[b_len - 1 - i] - '0')) ;
                result += (temp%10 + '0') ; //cout<<"Chk "<<(char)(temp%10 + '0')<<"\n" ;

            }
         }
         for(int i = b_len ; i<a_len ; i++)
         {
             result += a[i] ;
             //cout<<"Chk"<<(temp%10 + '0')<<"\n" ;
         }
         if(sign_changer == 1)
         {
             cout<<"-" ;
         }


        reverse(result.begin(), result.end());
        int i = 0 ; int len = result.length() ;
        while(result[0] == '0' && i<len)
        {
            result.erase(0,1) ;
            i+=1 ;
        }
        if(i == len)
        {
            cout<<"0\n" ;
        }
        else
        {
            cout<<result<<"\n" ;
        }


    return a_ret ;
}

int multiplication(string  a , string  b  , int a_sign , int b_sign)
{
        /** Now multiplying 2 numbers with digits m and n will have either m+n or m+n-1 digits in the result **/
    /** Now to be honest that is of no use I guess , still I'm writing that **/

    string result ;

    //result.sign = 0 ;


    int m = a.length()  ;
    int n = b.length() ;

    int what_sign = 0 ;

    /** We will initiliaze all the values in result as 0  , as we'll be doing multiplication operation **/
    for(int i =  0 ; i<(m+n) ; i++)
    {
        result += '0' ;
    }

    for(int i = 0 ; i<m ; i++)
    {
        int carry = 0 ;
        for(int j = 0 ; j<n;j++)
        {
            int temp = ((result[(m+n) - (i+j) - 1] - '0') + carry + (a[m-i-1]-'0')*(b[n-1-j] - '0')) ;


            result[(m+n) - (i+j) - 1] = temp%10 + '0' ;
            carry = temp/10 ;
        }

        if(carry>0)
        {
            result[(m+n) - 1 - (i+n)] = carry + '0' ;
        }
    }

    if(a_sign^b_sign)
    {
        what_sign = 1 ;
    }

    int i = 0 , len = result.length() ;
    while(result[i] == '0' && i<(len))
    {
        i+=1 ;
    }

    cout<<"The product of 2 numbers is \t" ;
    if(i == (len))
    {
        cout<<"0"<<"\n" ;
    }
    else
    {
        int i = 0 ; int len = result.length() ;
        while(result[0] == '0' && i<len)
        {
            result.erase(0,1) ;
            i+=1 ;
        }
        if(what_sign)
        {
            cout<<"-" ;
        }
        cout<<result<<"\n" ;
    }


    return 1  ;

}


int main()
{
    string a,b,val3 ;
    int a_sign ;
    int b_sign ;
    int value_stop = -3 ;   string s ; int flag = 0 ;

    int a_ret = 0 ;
    while(value_stop != 0 && flag ==0)
    {
        int invalid_checker = 0 ;
        int want_random ;
        cout<<"\nEnter 1 to add numbers\nEnter2 to subtract 2 numbers\nEnter 3 to multiply 2 numbers\nEnter0 to quit\n" ;
        cin>>value_stop ;
        cout<<"Enter 1 if you want a random number of length 300\n" ;
        cin>>want_random ;

        if(value_stop == 0)
        {
            flag = 1 ;
        }
        if(value_stop<0 || value_stop>3 && flag ==0)
        {
            cout<<"You have entered invalid option\n" ;
            invalid_checker = 1 ;
        }
        else if(flag == 0 && invalid_checker == 0)
        {
            if(want_random ==0)
            {
                cout<<"\n Enter number 1 \t" ; cin>>s ;
                if(s.length() >= 309)
                {
                    invalid_checker = 1 ;
                    cout<<"Invalid Integer entry\n" ;
                }
                if(!invalid_checker)
                {
                    a = value(s , &a_sign) ;
                    cout<<"\n Enter number 2 \t " ; cin>>s ;
                    if(s.length() >=309)
                    {
                        cout<<"Invalid Integer entry\n" ;
                        invalid_checker = 1 ;
                    }
                    else
                    {
                        b = value(s , &b_sign) ;
                    }
                }
            }
            else if(want_random == 1)
            {
                a = "2039568783564019774057658669290345772801939933143482630947726464532830627227012776329366160631440881733123728826771238795387094001583065673383282791544996983660719067664400370742171178056908727928481491120222863321448761833763265120835748216479339929612499173198362193042742802438031040150005637901234567891230" ;
                b = "2902453291655700251160164872177402875088379132955716094639143487783196544891184358552433019690018720615757558048028740620219277196473570604471353215770289292695785747605472683100550568673868759590451190939679722051242704416484508251888770951737541963465519525425992262954130577873402785282523588093299876543210" ;
                cout<<"Number 1 is \t"<<a<<"\n" ;
                cout<<"Number 2 is \t"<<b<<"\n" ;
            }


            if(value_stop == 1 && invalid_checker == 0)
            {
                cout<<"Addition of 2 number is \n" ;
                if(a_sign^b_sign)
                {
                    if(a_sign == 1)
                    {
                        a_ret = subtract(b,a,b_sign,0) ;
                    }
                    else if(b_sign == 1)
                    {
                        a_ret = subtract(a,b,a_sign ,0) ;
                    }
                }
                else
                {
                   a_ret =  add(a,b,a_sign,b_sign, 0) ;
                }
            }
            else if(value_stop == 2 && invalid_checker == 0)
            {
                cout<<"Subtraction of 2 number is \n" ;
                if(a_sign^b_sign)
                {
                    if(a_sign == 1)
                    {
                        a_ret = add(a,b,a_sign,b_sign,1) ;
                    }
                    else if(b_sign == 1)
                    {
                        a_ret = add(a,b,a_sign,b_sign,0) ;
                    }
                }
                else
                {
                    a_ret = subtract(a,b,a_sign,b_sign) ;
                }

            }
            else if(value_stop == 3 && invalid_checker == 0)
            {
                a_ret = multiplication(a,b , a_sign , b_sign) ;
            }

        }
        cout<<"-----------------------------------------------------------------------------------------\n" ;
        cout<<"-----------------------------------------------------------------------------------------\n" ;
    }
    return 0 ;

}
