#include<bits/stdc++.h>
using namespace std ;


bool isNumber(string s)  //Utility Function to find whether a given input from user is integer or string
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

/** This is a utility number to calculate fibonacci number for the fibonacci heap allocation **/
int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}

int countDigit(int n) // Utility function to count number of digits in the number
{
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

typedef struct Int   //Stores just 1 digit
{
    int i ;

} INT ;

typedef struct Char //Stores just 1 character
{
    char c ;
} CHAR ;


struct My_Var  //This is the variant record for the heap I'm creating
{
    char tag ;
    union
    {
        INT i ;
        CHAR c ;
    } U ;
} ;

struct Variant  //This is the variant record which the user will use for inputting the data
{
    char tag ;
    union
    {
        int i ;
        char c[100] ;
    } U ;
};


struct Free_List  //This will be the free list of Heap
{
    int start ;
    int length ;
    struct Free_List *next ;
};

struct Alloc_List  //This will be the Alloc list of heap
{
    //string name ;
    int start ;
    int length ;
    char name ;
    struct Alloc_List *next ;
};

struct Aval_pos  //This is a utility function used in My_Alloc function
{
    int start ;
    int end_pos ;
} ;

struct Alloc_List *insert_node(struct Alloc_List *my_list , struct Alloc_List *newNode)
{
    if(my_list == NULL)
    {
        return newNode ;
    }
    else
    {
        struct Alloc_List *temp = my_list ;
        while(temp->next != NULL)
        {
            temp = temp->next ;
        }

        temp->next =  newNode ;

        return my_list ;
    }

};


struct Free_List *insert_node_Free(struct Free_List *my_list, struct Free_List *newNode)
{
    if(my_list == NULL)
    {
        return newNode ;
    }
    else
    {
        struct Free_List *temp = my_list ;
        while(temp->next != NULL)
        {
            temp = temp->next ;
        }
        temp->next = newNode ;

        return my_list ;
    }
};

struct Heap
{
    My_Var Storage[10000] ; //This is the memory where things will be stored
    int Occupied[10000] ;   //If it is 0 , so the location is unoccupied other wise it is occupied
    char Name[10000] ;


    struct Free_List *f ;
    struct Alloc_List *a  ;

};


struct Heap *constructor(struct Heap *h)
{

    h->f = (struct Free_List*)malloc(sizeof(struct Free_List)) ;

    h->a = (struct Alloc_List*)malloc(sizeof(struct Alloc_List)) ;

    h->f->length = 10000;
    h->f->start = 0 ;
    h->f->next = NULL ;
    h->a = NULL ;




    for(int i = 0 ; i<10000 ; i++)
    {

        h->Occupied[i] = 0 ;
        h->Name[i] ='N' ;

    }


    return h ;
};


struct Heap *My_Alloc(struct Heap *h , struct Variant input , char name)
{

    //cout<<"Enterint into the heap\n" ;
    struct Free_List *F = (struct Free_List*)malloc(sizeof(struct Free_List)) ;

    //cout<<"\n Free llist created\n" ;
    struct Aval_pos p ;  //To calulate the first the and the last position
    int length = 0 ;

    int min_length = 10000 ; //This makes sure that we're following the best fit strategy with fibonacci system

    int end_point = 0 ;

    if(input.tag == 'i')
    {
      //  cout<<"\n Tag is integer\n" ;

        int integer = input.U.i ;  //Plus 1 for the ending character of '.'
        int length = countDigit(integer) + 1 ;
        //cout<<"Integer\t"<<integer<<"\n" ;
        //cout<<"\n Length is \t"<<length<<"\n" ;
        int i = 0  ;
        int near_big_fibo = fib(i) ;
        while(near_big_fibo<length)
        {
            i+=1 ;
            near_big_fibo = fib(i) ;
        }

        int fibo_1 = fib(i) ;
       int fibo_2 = fib(i-1) ;

        //cout<<"Fibo 1  is \t"<<fibo_1<<"\t Fibo 2  is \t"<<fibo_2<<"\n" ;

        int done =0 ;
        for(int j= 0 ; j<=10000 - (fibo_1 + fibo_2) ; j++)
        {
            int k = j ;
            while(h->Occupied[k] == 0)
            {
                k+=1 ;
            }
            k-= 1 ; //Now k is shifted to the last unoccupied index ;

            if((k-j +1 )>=(fibo_1 + fibo_2)  && ((k-j +1 )<=min_length))
            {
                p.start = j ;
                p.end_pos = k ;
                min_length = k-j + 1  ;
                done = 1 ;
            }


        }

        if(!done)
        {
            cout<<"Sorry we couldn't find enough space for allocation\n" ;
        }
        else
        {
          //  cout<<"\nAllocation starting\n" ;
            for(int j = p.start ; j<p.start + length - 1  ; j++)
            {
                h->Storage[j].U.i.i = integer%10 ;
                h->Occupied[j] = 1 ;
                integer = integer/10 ;
            }
            h->Storage[p.start + length - 1].U.c.c = '.' ;

            h->Name[p.start] = name ;

            F->next = NULL ;
            F->start = p.start + fibo_1 ;
            F->length = fibo_2   ;

            end_point = p.start + length - 1 ;
            //cout<<"Done with allocation\n" ;

        }

    } //End of tag == 'i' ;
    else if(input.tag == 'c')
    {
        int i = 0 ;
        while(input.U.c[i] != '.')
        {
            i+=1 ;
        }
        length = i ;
        int k = 0 ;
        int near_fib_big = fib(k) ;
        while(near_fib_big < length)
        {
            k+= 1 ;
            near_fib_big = fib(k) ;
        }

        int fibo_1 = near_fib_big ;
        int fibo_2 = fib(k-1) ;

        int done = 0 ;

        for(int j= 0 ; j<=10000 - (fibo_1 + fibo_2) ; j++)
        {
            int k = j ;
            while(h->Occupied[k] == 0)
            {
                k+=1 ;
            }
            k-= 1 ; //Now k is shifted to the last unoccupied index ;

            if((k-j +1 )>=(fibo_1 + fibo_2)  && ((k-j +1 )<=min_length))
            {
                p.start = j ;
                p.end_pos = k ;
                min_length = k-j + 1  ;
                done = 1 ;
            }


        }

        if(!done)
        {
            cout<<"Sorry we couldn't find enough space for allocation\n" ;
        }
        else
        {
            for(int j = p.start ; j<p.start + length   ; j++)
            {
                h->Storage[j].U.c.c = input.U.c[j-p.start] ;
                h->Occupied[j] = 1 ;
                //ans = ans/10 ;
            }

            h->Name[p.start] = name ;

            F->next = NULL ;
            F->start = p.start + fibo_1 ;
            F->length = fibo_2    ;

            end_point = p.start + length - 1 ;
        }


    } //End of tag == 'c'

    //Alloc list created and inserted to the alloc linked list
    //cout<<"Alloc list to be created\n"  ;
    struct Alloc_List *A = (struct Alloc_List*)malloc(sizeof(struct Alloc_List)) ;
    A->start = p.start ;
    A->length = end_point - p.start + 1 ;
    A->next = NULL ;
    A->name = name ;

    h->a = insert_node(h->a , A) ;

    //cout<<"Alloc list created\n"  ;
    //Now creating a Free List

    h->f = F ;

    //cout<<"Free list to be created \n" ;
    int k = 0 ;
    while(k!=10000)
    {
        if(h->Occupied[k] == 0)
        {
            int start = k ;
            while(h->Occupied[k] == 0)
            {
                k+=1 ;
            }
            k-= 1 ; //The last unoccupied index ;

            int length = k - start + 1 ;

            struct Free_List *FF = (struct Free_List*)malloc(sizeof(struct Free_List)) ;
            FF->start = start ;
            FF->length = length  ;
            FF->next = NULL ;

             h->f = insert_node_Free(h->f , FF) ;
             k+=1 ;
        }
        else
        {
            k+= 1;
        }

    }
    //cout<<"Free list created\n" ;

    return h ;
};



struct Heap *My_Free(struct Heap *h , char name)
{
    int ok_boomer = 0 ;
    int start = 0 ;
    for(int k = 0 ; k<10000 && ok_boomer == 0 ; k++)
    {
        if(h->Name[k] == name)
        {
            ok_boomer = 1 ;
            start = k ;
        }


    }
    //cout<<"Starting position is \t"<<start<<"\n" ;
    if(!ok_boomer)
    {
        cout<<"Given variable is not in the memory\n" ;
    }
    else
    {
        int k = start ; //cout<<"k is \t"<<k<<"\n" ;

        /**
        Will stop at location either the word is finished hinted by either the further heap is unoccupied
        or a new Word begins (inted by Name == 'N')
          **/
        while(h->Occupied[k+1] == 1 && h->Name[k+1] == 'N')
        {
            k+=1 ;
        }

        //Now k is at index where Storage[k] == '.' ;
        int end_free = k ;

      //  cout<<"Ending position is \t"<<end_free<<"\n";

        int memory_compaction = 0 ;

        struct Free_List *F = h->f ;
        while(F!=NULL && memory_compaction == 0)
        {
            if(F->start + F->length  == start)
            {
                F->length += (end_free - start ) + 1 ;
                memory_compaction = 1 ;
            }
            F = F->next ;
        }

        if(!memory_compaction)
        {
            struct Free_List *F = (struct Free_List*)malloc(sizeof(struct Free_List)) ;
            F->start =start ;
            F->length = end_free - start + 1 ;
            F->next = NULL ;

            h->f = insert_node_Free(h->f , F) ;
        }


        //cout<<"Alloc deletion starts\n" ;

        struct Alloc_List *A = h->a ;
        struct Alloc_List *tmp = (struct Alloc_List*)malloc(sizeof(struct Alloc_List)) ;
        int done = 0 ;

       /** cout<<"Printing Alloc List\n" ;
        while(A != NULL)
        {
            cout<<A->start<<"\t"<<A->length<<"\t"<<A->name<<"\n" ;
            A =A->next ;
        } **/

        if(A->name == name)
        {
            if(A->next == NULL)
            {
                h->a = NULL ;
            }
            else
            {
                h->a = h->a->next  ;
            }
        }
        else
        {
            tmp = A  ;
            while(A->name != name)
            {
                tmp = A ;
                A = A->next ;
            }
            tmp->next = A->next ;
            free(A) ;
        }
        //So deletion of the Alloc List is done


        //struct Free_List *Fa = h->f ;
        //struct Free_List *FF = h->f->next ;



    }


    return h ;

};


struct Heap *Memory_compaction(struct Heap *h)
{
    struct Free_List *F = h->f ;
    if(F->next == NULL)
    {
        return h ;
    }
    else
    {
        struct Free_List *FF = F->next ;
        while(F->next != NULL)
        {
            if(F->start + F->length == F->next->start)
            {
                //cout<<"Found memeory compaction\n" ;
                //cout<<F->start<<"\t"<<F->length<<"\t"<<F->next->start<<"\n" ;
                F->length = F->length + F->next->length  ;
                F->next = F->next->next ;

            }

            F = F->next ;
        }
    }

    return h ;
};



void print(struct Heap *h)
{
    struct Free_List *F = h->f ;
    F = F->next ;
    cout<<"\nPrinting Free List\n" ;
    while(F!=NULL)
    {
        cout<<F->start<<"\t"<<F->length<<"\n" ;
        F = F->next ;
    }

    cout<<"\nPrinting Alloc list\n" ;

    struct Alloc_List *A = h->a ;

    if(A != NULL)
    {
        if(A->start <10000)
        {
            while(A!=NULL)
            {
                cout<<"Start is  "<<A->start<<" Length is  "<<A->length<<"\n" ;
                A = A->next ;
            }
        }
        else
        {
            cout<<"\nAlloc List is empty\n" ;
        }
    }
    else
    {
        cout<<"\nAlloc List is empty\n" ;
    }
}




int main()
{
    //cout<<"Starting the program\n" ;
    struct Heap *h = (struct Heap*)malloc(sizeof(struct Heap)) ;
    h = constructor(h) ;


    int answer = 0 ;

    char input ;
    int done = 0 ;
    cout<<"Welcome\n\n" ;
    while(answer != 4 && done == 0)
    {
            cout<<"\n"  ;
            cout<<"Enter 1 to allocate some variable\n" ;
            cout<<"Enter 2 to show the Alloc and the Free List\n" ;
            cout<<"Enter 3 to Free some variable\n" ;
            cout<<"Enter 4 to Quit\n" ;
            cin>>answer ;
        if(answer == 1)
        {
            Variant input_to_memory ;
            cout<<"Enter your Variable's type   (i for integer and c for character and string and I for Array of Integer) \n" ;
            cin>>input ;

            cout<<"\nEnter name of your variable in small Alphabet\n";

            char name  ;

            cin>>name ;
            if(input == 'i')
            {

                cout<<"\nEnter number \n " ;
                cin>>input_to_memory.U.i ;
                input_to_memory.tag = 'i' ;
                // int answer ;
                //Assigning number to input Variant

                h = My_Alloc(h,input_to_memory , name) ;
            }
            else if(input == 'c')
            {
                input_to_memory.tag = 'c' ;
                cout<<"\n Enter your character and to stop enter '.' \n" ;
                int k = 0 ;
                cin>>input_to_memory.U.c[k] ;
                while(input_to_memory.U.c[k] != '.')
                {
                    k+=1 ;
                    cin>>input_to_memory.U.c[k] ;

                }

                h = My_Alloc(h,input_to_memory,name) ;

            }
            else
            {
                cout<<"Enter the Array size\n" ;
                int siz ; cin>>siz ;
                for(int k = 0  ; k<siz ; k++)
                {
                    cin>>input_to_memory.U.i ;
                    input_to_memory.tag = 'i' ;
                    // int answer ;
                    //Assigning number to input Variant

                    h = My_Alloc(h,input_to_memory , name) ;
                }
            }
        } //End of 1
        else if(answer == 2)
        {
            print(h) ;
        }
        else if(answer == 3)
        {
            cout<<"\nEnter the name of the variable you want to delete\n"  ;
            char del ; cin>>del ;
            h = My_Free(h , del) ;
        }
        else if(answer == 4)
        {
            done = 1 ;
        }
        else
        {
            cout<<"You've entered Wrong number , please consider entering it again \n" ;

        }
        h = Memory_compaction(h) ;
    }

    return 0 ;
}
