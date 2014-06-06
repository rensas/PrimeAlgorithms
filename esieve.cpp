#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

using namespace std;

//Sieve of Eratosthenese algorithm
// http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

bool *standard_sieve(unsigned long upper_bound){
  
  //Allocate memory for result array, zeroing it
  bool *array = (bool*)calloc((upper_bound+1), sizeof(bool));

  // Calculate the maximum value we should loop to (Square root of the upper bound)
  unsigned long c = (unsigned long)ceil(sqrt(upper_bound));

  // Loop to C
  for(unsigned long i=2; i<=c; i++){

    // If the value of array[i] is 0, the number is prime and we proceed.
    // if not, skip to the next i
    if(array[i] == 0){
      
      // Start at i*i, increment every i elements of the array, 
      // assigning the value 1 (mark it as not prime)
      for(unsigned long j = i*i; j<=upper_bound; j+=i){
	array[j] = 1;
      }
    }
  }

  // Return results
  return array;

}

// Modified sieve using 2*i increment for inner loop. (Skips even numbers)
bool *n2_sieve(unsigned long upper_bound){

  // Allocate memory for the sieve array
  bool *array = (bool*)calloc((upper_bound+1), sizeof(bool));
  
  // Calculate the maximum value we should loop to (Square root of the upper bound)
  unsigned long c = (unsigned long)ceil(sqrt(upper_bound));
  
  // Loop to our C value
  for(unsigned long i=2; i<=c; i++){
    
    // If the number we are looking for is prime ( == 0), remove it's
    // multiples from the memory array by assigning them the value 1
    if(array[i] == 0){

      // Set the inner loop increment value to 2*i if i is not 2
      int s = i*i;
      int inc;
      if(i==2){
	inc=2;
      } else {
	inc=2*i;
      }
      // Assign multiples the value 1
      for(unsigned long j = s; j<=upper_bound; j+=inc){
	array[j] = 1;
      }
    }
  }

  // Return the resulting array
  return array;
}

// Odd number only sieve
bool *odd_sieve(unsigned long upper_bound){

  // Allocate enough memory to store only the odd numbers between
  // 1 and upper_bound. Twice as memory efficient as the n2_sieve,
  // and saves time by removing the need to iterate through the 
  // even numbers.
  bool *array = (bool*)calloc((upper_bound/2), sizeof(bool));

  // Ceiling calculation
  unsigned long c = (unsigned long)ceil(sqrt(upper_bound));

  // Loop through, using some really goofy indexing math
  // (because only odd numbers are listed, indexes no longer
  // match the number they refer to.)
  for(unsigned long i=1; (i+(i+1))<=c; i++){

    // If this number is prime...
    if(array[i] == 0){

      // Set our loop increment value
      unsigned long inc = (i+(i+1));
      
      // Set our loop starting point (the square of i)
      unsigned long sqr = (inc*i)+i;

      // Loop and flag as not prime
      for(unsigned long j=sqr; j<=(upper_bound/2); j+=inc){
	array[j] = 1;
      }
    }
  }

  //Return results
  return array;
}

// Standard double for loop implementation with break
// on factor find.
bool *standard(int upper_bound){
  
  // If a factor has been found
  bool factor = 0;

  // Allocate memory for result array
  bool *array = (bool*)malloc(upper_bound+1);
  // Set the memory to all 1s
  memset(array, 1, (upper_bound+1));

  // Loop through each number from 2 to upper_bound
  for(int i=3; i<=upper_bound; i++){

    // Loop through each possible factor for i (2 to i)
    for(int j=2; j<i; j++){
      
      // If i is divisible by j, break because we found a factor
      if(i%j == 0){
	factor = 1;
	break;
      }
    }

    // If no factors were found, flag the number as prime. Otherwise,
    // it remains flagged as not prime
    if(factor == 0){
      array[i] = 0;
    }
    // Reset factor
    factor = 0;
  }

  // Return results
  return array;
}

//Print results
void print_array(bool *array, int upper_bound, int list_mod){
  int tc = 0;
  int num_primes = 0;
  for(int i=2; i<=upper_bound; i++){
    if(array[i] == 0){
      if(list_mod > 0){
	cout<<i<<"\t";
      }
      num_primes++;
      tc++;
    }
    if(list_mod > 0 && tc==list_mod){
      cout<<"\n";
      tc = 0;
    }
  }
  cout<<"Found "<<num_primes<<" primes.\n";
}

// Print results for odd only array. Needs funky indexing
void print_odd(bool *array, int upper_bound, int list_mod){
  int tc = 1;
  int num_primes = 1;
  cout<<"2\t";
  for(int i=1; i<=(upper_bound/2); i++){
    if(array[i] == 0){
      if(list_mod > 0){
	cout<<(i+(i+1))<<"\t";
      }
      num_primes++;
      tc++;
    }
    if(list_mod > 0 && tc==list_mod){
      cout<<"\n";
      tc = 0;
    }
  }
  cout<<"Found "<<num_primes<<" primes.\n";
}

int main(int argc, char* argv[]){


  unsigned long upper_bound = atol(argv[1]);
  int list_mod = atoi(argv[2]);
  int mode = atoi(argv[3]);

  // Run n2_sieve()
  if(mode == 1){

    bool *array = n2_sieve(upper_bound);
    if(list_mod != -5){
      print_array(array, upper_bound, list_mod);
    }
    // Release memory
    free(array);  


    // Run standard (double for loop)
  } else if(mode == 2){  //Standard
    bool *array = standard(upper_bound);
    
    cout<<"Done. Print results? (y/n): ";
    char in = getchar();
    if(in =='y'){
      print_array(array, upper_bound, list_mod);
    }
   
    free(array);  

    //Run Standard Sieve of Eratosthenes
  } else if(mode == 3) {    

    bool *array = standard_sieve(upper_bound);
    if(list_mod != -5){
      print_array(array, upper_bound, list_mod);
    }
    // Release memory
    free(array);  

    //Run the odd number only sieve
  } else {
    bool *array = odd_sieve(upper_bound);
    
    if(list_mod != -5){
      print_odd(array, upper_bound, list_mod);
    }
    // Free results
    free(array);
  }

  return 0;
}
