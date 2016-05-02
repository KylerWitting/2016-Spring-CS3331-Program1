// ----------------------------------------------------------- 
// NAME : Kyler Witting                         User ID: kmwittin 
// DUE DATE : 02/03/2016                                       
// PROGRAM ASSIGNMENT 1                                        
// FILE NAME : prog1.c             
// PROGRAM PURPOSE :                                           
//     This  program takes four positive integers from its commend line arguments, creates four child processes, waits for them to complete, and exits. 
//     The first process sorts m random integers using the heap sort.
//     The second computes the n-th Fibonacci number fn using recursion. 
//     The third process finds the solution of Buffoon's needle problem by throwing a needle r times. 
//     The fourth process computes the integration of function sin(x) between 0 and π.
// ----------------------------------------------------------- 

#include <stdio.h>      //Needed for sprintf
#include <string.h>     //Needed for strlen
#include <sys/types.h>  //Has all system data types
#include <unistd.h>     //Declares standard symbolic constants and types
#include <sys/wait.h>   //The wait command 
#include <time.h>       //Used for srand seed
#include <math.h>       //Used for sin 
#include <stdlib.h>     //Used for RAND_MAX


//Main Proccess Methods, mostly used for printing
int heap          ( long int *m );
int fibonacci     ( long int *n );
int buffon        ( long int *r );
int integration   ( long int *s );

//Helper Methods, does most calculation
int sortArray     (  int array[], long int m ); 
int generateArray (  int array[], long int m );
int printArray    (  int array[], long int m, int type ); 
long int fibRecur (  long int cur );
float throw       (  long int reps );
long int findHits (  long int reps );

int main( int argc, char **argv) {
    //i: wait() for loop. status: used in wait()
    int i, status;
    //Stores the command line input
    long int m, n, r, s;
    //PID of the processes 
    pid_t parent, child1, child2, child3, child4; 
    //Used for printing to stdout
    char error[256], buffer[256]; 

    sprintf( buffer, "Main Started \n" );
    write( 1, buffer, strlen( buffer ) );

    //Basic Error checking on inputs 
    if ( argc == 1 ) {
        sprintf( error, "No arguments were given.\n" );
        write( 2, error, strlen( error ) );
        return ( -1 );
    }
    if ( argc == 2 ) {
        sprintf( error, "Only one arguments were given.\n" );
        write( 2, error, strlen( error ) );
        return ( -1 );
    }
    if ( argc == 3 ) {
        sprintf( error, "Only two  arguments were given.\n" );
        write( 2, error, strlen( error ) );
        return ( -1 );
    }
    if ( argc == 4 ) {
        sprintf( error, "Only three arguments were given.\n" );
        write( 2, error, strlen( error ) );
        return ( -1 );
    }
    if ( argc > 5 ) {
        sprintf( error, "Too many arguments were given.\n" );
        write( 2, error, strlen( error ) );
        return ( -1 );
    }
    
    //assigns input to variables
    m = atoi( argv[1] );
    n = atoi( argv[2] );
    r = atoi( argv[3] );
    s = atoi( argv[4] );

    parent = getpid();

    sprintf( buffer, "Main Process Started\n" );
    write( 1, buffer, strlen( buffer ) );

    sprintf( buffer, "Number of Random Numbers   = %li\n", m );
    write( 1, buffer, strlen( buffer ) );
    sprintf( buffer, "Fibonacci Input            = %li\n", n );
    write( 1, buffer, strlen( buffer ) );
    sprintf( buffer, "Buffon's Needle Iterations = %li\n", r );
    write( 1, buffer, strlen( buffer ) );
    sprintf( buffer, "Integration Iterations     = %li\n", s );
    write( 1, buffer, strlen( buffer ) );

    //child1 fork with error checking 
    //It will call the method heap if all goes well   
    if ( ( child1 = fork() ) == 0 ) {
        if ( getppid() != parent ) {
            sprintf( error, "   Child1's parent does not match original parent. \n" );
            write( 2, error, strlen( error ) );
            return -1; 
        }
        //Run function for desired operation then exit 
        sprintf( buffer, "Heap Sort Process Created\n" );
        write( 1, buffer, strlen( buffer ) );    
        heap( &m );
        return 1;
    }
    if ( child1 < 0 ) {
        sprintf( error, "   Child1 fork() failed. Now exiting. \n" );
        write( 2, error, strlen( error ) );
        return -1;
    }

    //child2 fork with error checking 
    //It will call the method Fibonacci if all goes well   
    if ( ( child2 = fork() ) == 0 ) {
        if ( getppid() != parent ) {
            sprintf( error, "      Child2's parent does not match original parent. \n" );
            write( 2, error, strlen( error ) );
            return -1; 
        }
        //Run function for desired operation then exit 
        sprintf( buffer, "Fibonacci Process Created\n" );
        write( 1, buffer, strlen( buffer ) );    
        fibonacci( &n );
        return 1;
    }
    if ( child2 < 0 ) {
        sprintf( error, "      Child2 fork() failed. Now exiting. \n" );
        write( 2, error, strlen( error ) );
        return -1;
    }

    //child3 fork with error checking 
    //It will call the method buffon if all goes well   
    if ( ( child3 = fork() ) == 0 ) {
        if ( getppid() != parent ) {
            sprintf( error, "         Child3's parent does not match original parent. \n" );
            write( 2, error, strlen( error ) );
            return -1; 
        }
        //Run function for desired operation then exit 
        sprintf( buffer, "Buffon's Needle Process Created\n" );
        write( 1, buffer, strlen( buffer ) );    
        buffon( &r );
        return 1;
    }
    if ( child3 < 0 ) {
        sprintf( error, "         Child3 fork() failed. Now exiting. \n" );
        write( 2, error, strlen( error ) );
        return -1;
    }

    //child4 fork with error checking 
    //It will call the method integration if all goes well   
    if ( ( child4 = fork() ) == 0 ) {
        if ( getppid() != parent ) {
            sprintf( error, "            Child4's parent does not match original parent. \n" );
            write( 2, error, strlen( error ) );
            return -1; 
        }
        //Run function for desired operation then exit 
        sprintf( buffer, "Integration Process Created\n" );
        write( 1, buffer, strlen( buffer ) );    
        integration( &s );
        return 1;
    }
    if ( child4 < 0 ) {
        sprintf( error, "            Child4 fork() failed. Now exiting. \n" );
        write( 2, error, strlen( error ) );
        return -1;
    }

    sprintf( buffer, "Main Process Waits\n" );
    write( 1, buffer, strlen( buffer ) );    

    for (i = 0; i < 4; i++) 
        wait( &status );

    sprintf( buffer, "Main Process Exits\n" );
    write( 1, buffer, strlen( buffer ) );    

    return 1; 
}


// ----------------------------------------------------------- 
// FUNCTION  Heap Sort : (heap)                          
//    Sorts m random integers using the heap sort                            
// PARAMETER USAGE :                                           
//    m : The number of integers to sort using heap sort                
// FUNCTION CALLED :                                           
//    generateArray: It creates a random array of size m, of ints
//    printArray: Prints the array given to it. For both sorted and unsorted array
//    sortArray: Sorts the array given to it
//----------------------------------------------------------- 
int heap( long int *m ) {
    char buffer[256];
    int heapArray[*m], i;
  
    sprintf( buffer, "   Heap Sort Process Started\n" );
    write( 1, buffer, strlen( buffer ) );    

    generateArray( heapArray, *m );
    printArray( heapArray, *m, 0 );   

    sortArray( heapArray, *m );
    printArray( heapArray, *m, 1 );   

    sprintf( buffer, "   Heap Sort Process Exits\n" );
    write( 1, buffer, strlen( buffer ) );    
}

// ----------------------------------------------------------- 
// FUNCTION Fibonacci number : (fibonacci)                          
//     computes the n-th Fibonacci number fn using recursion                            
// PARAMETER USAGE :                                           
//    n : What number fibonacci will go up to and find                
// FUNCTION CALLED :                                           
//    fibRecur: the recursive method to find the fib number 
// ----------------------------------------------------------- 
int fibonacci( long int *n ) {
    char buffer[256];

    sprintf( buffer, "      Fibonacci Process Started\n" );
    write( 1, buffer, strlen( buffer ) );    
    sprintf( buffer, "      Input Number %li\n", *n );
    write( 1, buffer, strlen( buffer ) );    

    sprintf( buffer, "      Fibonacci Number f(%li) is %li\n", *n, fibRecur( *n ) );
    write( 1, buffer, strlen( buffer ) );    
    sprintf( buffer, "      Fibonacci Process Exits\n" );
    write( 1, buffer, strlen( buffer ) );    
}

// ----------------------------------------------------------- 
// FUNCTION  Buffon's Needle Problem : (buffon)                          
//     finds the solution of Buffoon's needle problem by throwing a needle r times                            
// PARAMETER USAGE :                                           
//    r : the number of times a needle is thrown 
// FUNCTION CALLED :                                           
//    throw: calculates the percentage of throws of a needle that will land accross 
//    a line. It should be near 2/PI = 0.63661... for larage "r"
// ----------------------------------------------------------- 
int buffon( long int *r ) {
    char buffer[256];
    double result = 0;

    sprintf( buffer, "         Buffon's Needle Process Started\n" );
    write( 1, buffer, strlen( buffer ) );    
    sprintf( buffer, "         Input Number %li\n", *r );
    write( 1, buffer, strlen( buffer ) );    

    sprintf( buffer, "         Estimated Probability is %0.5f\n", throw( *r ) );
    write( 1, buffer, strlen( buffer ) );
    sprintf( buffer, "         Buffon's Needle Process Exits\n" );
    write( 1, buffer, strlen( buffer ) );    
}

// ----------------------------------------------------------- 
// FUNCTION  Sin Integration : (integration)                          
//     computes the integration of function sin(x) between 0 and pi                            
// PARAMETER USAGE :                                           
//    s : Iterates s times and count the number of points in the area between sin(x) and the x-axis               
// FUNCTION CALLED :                                           
//    findHits: Finds the number of points in the area between sin(x) and the x-axis and returns it as a long int. 
// ----------------------------------------------------------- 
int integration( long int *s ) {
    char buffer[256];
    long int hit = 0;
    double result = 0;

    sprintf( buffer, "            Integration Process Started\n" );
    write( 1, buffer, strlen( buffer ) );    
    sprintf( buffer, "            Input Number %li\n", *s );
    write( 1, buffer, strlen( buffer ) );   

    hit = findHits( *s );

    sprintf( buffer, "            Total Hit %li\n", hit);
    write( 1, buffer, strlen( buffer ) );
    
    result = ( (double) hit / (double) *s ) * M_PI;

    sprintf( buffer, "            Estimated Area is %1.7f\n", result);
    write( 1, buffer, strlen( buffer ) );
    sprintf( buffer, "            Integration Process Exits\n" );
    write( 1, buffer, strlen( buffer ) );    

}

// ----------------------------------------------------------- 
// FUNCTION  Generate Array : (generateArray)                          
//    Creates an array of size m into array                          
// PARAMETER USAGE :                                           
//    m : The number of integers to sort using heap sort
//    array: The array to put the int's into                
// FUNCTION CALLED :                                           
//    rand(): used to get a random int for the array
//    srand(): the seed for rand()
//    time(): Used to get a new seed number for the rand()
// ----------------------------------------------------------- 
int generateArray( int array[], long int m ) {
    long int i;
    time_t t;
    srand((unsigned) time(&t));
    for( i = 0; i < m; i++ ) 
        array[i] = rand()%100; 
}

// ----------------------------------------------------------- 
// FUNCTION  Sort Array : (sortArray)                          
//    Sorts m random integers using the heap sort                            
// PARAMETER USAGE :                                           
//    m : The number of integers to sort using heap sort                
//    array: the array to sort 
// FUNCTION CALLED :                                           
//    None
// ----------------------------------------------------------- 
int sortArray( int array[], long int m ) {
    char buffer[256];
    long int temp, cur, child, i = m, parent = m/2;

    if( m ==  0 ){ 
        sprintf( buffer, "Heap is Empty\n" );
        write( 1, buffer, strlen( buffer ) );
        return -1;
    }

    while( 1 ) { 
        if( parent > 0 )  
            temp = array[--parent];
        else { 
            i--;
            if( i == 0 ) 
                return 1;
            temp = array[i];
            array[i] = array[0];
        }
        cur = parent; 
        child = cur * 2 + 1;
        while( child < i ) {
            if( child + 1 < i && array[child + 1] > array[child] )
                child++;
            if( array[child] > temp ) {
                array[cur] = array[child];
                cur = child; 
                child = cur * 2 + 1;
            }
            else
                break;
        }
        array[cur] = temp;
    }
}


// ----------------------------------------------------------- 
// FUNCTION  Heap Sort : (heap)                          
//    Prints the array given
// PARAMETER USAGE :                                           
//    m : The number of integers in the array
//    array: the array to print               
//    type: 0 for Random Numbers Generated:
//          1 for Sorted Sequence:
// FUNCTION CALLED :                                           
//    None
// ----------------------------------------------------------- 
int printArray( int array[], long int m, int type ) {
    long int i = 0, lineCount = 0;
    char buffer[(m*5)+20];
    if( type == 0 ){
        sprintf( buffer, "   Random Numbers Generated:\n" );

    }else{
        sprintf( buffer, "   Sorted Sequence:\n" );
    }
    sprintf( buffer + strlen( buffer ), "  " );
    for( i = 0; i < m; i++ ) {
        //Keeps each line under 80
        if( lineCount > 17 ) { 
            sprintf( buffer + strlen( buffer ), "\n  " );
            lineCount = 0;    
        }

        sprintf( buffer + strlen( buffer ), "%4d", array[i] );

        lineCount+=1;
    }

    //Prints the final buffer into stdout
    sprintf( buffer + strlen( buffer ), "\n" );
    write( 1, buffer, strlen( buffer ) );
}

// ----------------------------------------------------------- 
// FUNCTION Fibonacci Recursive Function  : (fibRecur)                          
//    Uses recursion to find the fibonacci number of the number given
// PARAMETER USAGE :                                           
//    cur: the current number to find the fib number with 
// FUNCTION CALLED :                                           
//    fibRecur: Recursively used 
// ----------------------------------------------------------- 
long int fibRecur( long int cur ) { 
    if( cur == 0 ) 
        return 0; 
    if( cur <= 2 ) 
        return 1; 
    return fibRecur( cur - 1 ) + fibRecur( cur - 2 );
}


// ----------------------------------------------------------- 
// FUNCTION Buffoon's Needle Throw  : (throw)
//    Throws a needle "reps" times. It then checks if the needle crosses a dividing line
//    If it is then it puts one in success. 
// PARAMETER USAGE :                                           
//    reps: The number of times the needle will be thrown. Max for the "for loop"
// FUNCTION CALLED :                                           
//    rand(): used to get a random int for the array
//    srand(): the seed for rand()
//    time(): Used to get a new seed number for the rand()
// ----------------------------------------------------------- 
float throw( long int reps ) {
    long int i, success = 0; 
    int L = 1, G = 1;
    float d, a, temp;
    time_t t;

    srand((unsigned) time(&t));

    for( i = 0; i < reps; i++ ) { 
        d =  ( (float) rand() ) / RAND_MAX; 
        a = ( ( (float) rand() ) / RAND_MAX ) * ( 2 * M_PI );

        temp = d + ( L * sin( a ) );

        if( temp < 0 || temp > G )
            success++;    
    }
    return (float) success/(float) reps;
}


// ----------------------------------------------------------- 
// FUNCTION Integration Hit calculator  : (findHits)
//    This will find how many times point (a,b) is in the area between sin(x) and the x-axis
// PARAMETER USAGE :                                           
//    reps: The number of points picked in the rectangle. Max for the "for loop"
// FUNCTION CALLED :                                           
//    rand(): used to get a random int for the array
//    srand(): the seed for rand()
//    time(): Used to get a new seed number for the rand()
// ----------------------------------------------------------- 
long int findHits ( long int reps ) { 
    long int i, success = 0; 
    double a, b;
    time_t t;

    srand((unsigned) time(&t));

    for( i = 0; i < reps; i++ ) { 
        a = ( ( (float) rand() ) / RAND_MAX ) *  M_PI ;
        b =  ( (float) rand() ) / RAND_MAX; 

        if( b <= sin( a ) )
            success++;    
    }
    return success;
}
