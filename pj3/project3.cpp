/*
Diego Rivera Project 3
*/
#include "project3.hpp"
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;
/* 
 * read_inputs(vector<int>&, char*)
 *
 * Pass it the filename as a C-string and a vector to populate with
 * the numbers in that file (which should be separated by whitespace)
 *
 * This vector should be empty prior to calling this function
 *
 * Returns true if it was able to read at least one number into the
 * vector, else false
 */
bool read_inputs(vector<int>& numbers, string filename) {
   assert(numbers.empty()); // vector should be empty before call

   ifstream inFile(filename);
   int currentNumber;
   inFile >> currentNumber;
   while (inFile.good() && !(inFile.eof())) {
      numbers.push_back(currentNumber);
      inFile >> currentNumber;
   }

   // Return true if at least 1 number was read from input file,
   // else false
   return (numbers.size() > 0);
}

/*
 * Run_tests
 * Given a filename, call your functions and run unit tests
 *
 * You'll probably want to change this function to pass it
 * the desired outputs for each input file
 */
void run_tests(string inputfile) {
    vector<int> inputs, result;
    bool failureFlag = false;

    if (!read_inputs(inputs, inputfile)) {
       cerr << "I couldn't read from" << inputfile << endl;
       return;
    }
    cout << "Testing your functions on " << inputfile << endl;

    // Call your test functions here
    
    //PROBLEM 1
    inversions_test(inputs, inputfile);
    
    
    // PROBLEM 2
    largest_left_test(inputs, result, inputfile);
    
    
    // PROBLEM 3

    left_right_test(inputs,result,inputfile);

    // PROBLEM 4
    increasing_test(inputs, inputfile);

    if (!failureFlag) {
        cout << "All tests passed\n";
    }
}

//PROBLEM 1

// normal for loop that starts from 0 and starts if conditions at i>=1.
int count_inversions_iterative(const vector<int>& numbers){

    int count = 0;
    for (int i = 0; i < numbers.size(); ++i){
        if (i >= 1){
            if (numbers.at(i-1) > numbers.at(i)){
                count ++;
            }
        }
    }

    return count;
}

// recursive function calls recursive helper function below.
int count_inversions_recursive(const vector<int>& numbers){
    return count_inversions_recursive_helper(numbers, numbers.size());

}

// recursive helper starts at the end of the vector and works its way to the front.
int count_inversions_recursive_helper(const vector<int>& numbers, int n){


    int count = 0;
    if(n == 1){
        return count;
    }

    count += count_inversions_recursive_helper(numbers, n-1);
    if(numbers.at(n-1) >= numbers.at(n-2)){
        return count;
    }
    else{
        count++;
        return count;
    }

}

void inversions_test(const vector<int>& numbers, string inputfile){
    cout << "\nPROBLEM 1\n\nIterative: ";
    int result1 = count_inversions_iterative(numbers);
    cout << result1 << endl;
    cout << "Recursive: ";
    int result2 = count_inversions_recursive(numbers);
    cout << result2 << endl;

    if(inputfile == "numbers1.txt"){
        assert(result1 == 3);
        assert(result2 == 3);
    }
    else if(inputfile == "numbers2.txt"){
        assert(result1 == 8);
        assert(result2 == 8);
    }
    else if(inputfile == "numbers3.txt"){
        assert(result1 == 54);
        assert(result2 == 54);
    }
    


}
//PROBLEM 2

/* normal for loop to iterate through the vector and uses a nested for loop to find closest 
   larger integer from the left. Outer for loop starts at 0. */
void largest_left_iterative(const vector<int>& numbers, vector<int>& result){
    int leftVal = 0;
    result.resize(numbers.size());
    for (int i = 0; i < numbers.size(); ++i){
        for (int m = i; m >= 0; --m){
            
            if( numbers.at(i) < numbers.at(m)){
                leftVal = numbers.at(m);
                break;
            }
            else {
                leftVal = 0;
            }

        }
        if (numbers.at(i) < leftVal){
            result.at(i) = leftVal;
        }
        else{
            result.at(i) = 0;
        }

        
    }
}

// recusive function calls recursive helper function below.
void largest_left_recursive(const vector<int>& numbers, vector<int>& result){
    result.resize(numbers.size());

    largest_left_recursive_helper(numbers, result, numbers.size()-1);
}

/* recursive helper below starts at the 0 index to traverse through the vector and calls
   "larger_left_right_recursive_helperL" to find the closest larger interger from the left. */
void largest_left_recursive_helper(const vector<int>& numbers, vector<int>& result, int index){
    if(index < 0){
        return;
    }
    int left = 0;
    left = larger_left_right_recursive_helperL(numbers, result, index, numbers.at(index));
    
    if(left > numbers.at(index)){
        result.at(index) = left;
    }
    else{
        result.at(index) = 0;
    }
    
    largest_left_recursive_helper(numbers,result,index-1);
}

void largest_left_test(const vector<int>& numbers, vector<int>& result, string filename){
    vector<int> num2vec {0,10,10,0,0,200,200,0,300,300,300,180,130,0,0,360,360,0,400,30};
    vector<int> num1vec {0,32,32,0,43,43,22,22,0};
    result.clear();
    cout << "\nPROBLEM 2\n\nIterative: ";
    largest_left_iterative(numbers, result);
    for (int i = 0 ; i < result.size(); ++i){
        cout << result.at(i) << " ";
    }
    result.clear();
    cout << "\nRecursive: ";
    largest_left_recursive(numbers,result);
    for (int i = 0 ; i < result.size(); ++i){
        cout << result.at(i) << " ";
    }

    if(filename == "numbers1.txt"){
        for (int i = 0 ; i < result.size(); ++i){
            assert(result.at(i) == num1vec.at(i));
        }
        
    }
    else if(filename == "numbers2.txt"){
        for (int i = 0 ; i < result.size(); ++i){
            assert(result.at(i) == num2vec.at(i));
        }
    }
}
// PROBLEM 3

/* normal for loop that starts from 0 and uses two nested for loops to find the closest larger 
   integer from left and right, compares them, result is inserted in the result vector. */
void larger_left_right_iterative(const vector<int>& numbers, vector<int>& result){
    result.resize(numbers.size());
    int max = 0;

    int leftVal = 0, rightVal = 0;
    for (int i = 0 ; i< numbers.size(); ++i){
        
        for (int j = i; j < numbers.size(); ++j){
            if( numbers.at(i) < numbers.at(j)){
                rightVal = numbers.at(j);
                break;
            }
            else {
                rightVal = 0;
            }
        }

        for (int m = i; m >= 0; m--){
            if( numbers.at(i) < numbers.at(m)){
                leftVal = numbers.at(m);
                break;
            }
            else {
                leftVal = 0;
            }
        }

        if(rightVal < leftVal){
            result.at(i) = leftVal;
        }
        else{
            result.at(i) = rightVal;
        }
    }
}

// recursive function calls recursive helper function below.
void larger_left_right_recursive(const vector<int>& numbers, vector<int>& result){
    int index =numbers.size()-1;
    result.resize(numbers.size());
    larger_left_right_recursive_helper(numbers,result,index);
    
}

/* recursive helper function starts at the end of the vector and works its way to the front of the vector.
   Calls helper function L (left) and R (right) to find the closest larger interger from the left and right
   to compare them. */
void larger_left_right_recursive_helper(const vector<int>& numbers, vector<int>& result, int index){
    if(index < 0){
        return;
    }
    int left = 0, right = 0;
    left = larger_left_right_recursive_helperL(numbers, result, index, numbers.at(index));
    right = larger_left_right_recursive_helperR(numbers,result, index, numbers.at(index));
    if(left > right){
        result.at(index) = left;
    }
    else{
        result.at(index) = right;
    }
    larger_left_right_recursive_helper(numbers,result,index-1);   
}

/* recursive helper L iterates to the front of the list to find the closest larger interger. 
   if it doesnt find anything it returns 0. */
int larger_left_right_recursive_helperL(const vector<int>& numbers, vector<int>& result, int index,int value){
    if (index < 0){
        return 0;
    }
    if(numbers.at(index) > value){
        return numbers.at(index);
    }
    return larger_left_right_recursive_helperL(numbers,result,index-1,value);
}

/* recursive helper R iterates to the end of the list to find the closest larger interger. 
   if it doesnt find anything it returns 0. */
int larger_left_right_recursive_helperR(const vector<int>& numbers, vector<int>& result, int index,int value){
    if (index > numbers.size()-1){
        return 0;
    }
    else if(numbers.at(index) > value){
        return numbers.at(index);
    }
    return larger_left_right_recursive_helperR(numbers,result,index+1,value);
}

void left_right_test(const vector<int>& numbers, vector<int>& result, string filename){
    vector <int> num2vec {70,10,70,200,300,200,300,310,300,300,310,310,310,360,400,360,400,0,400,30};
    vector<int> num1vec {43,32,43,50,43,50,50,50,0};
    result.clear();
    cout << "\n\nPROBLEM 3\n\nIterative: ";
    larger_left_right_iterative(numbers,result);
    for (int i = 0 ; i < result.size(); ++i){
        cout << result.at(i) << " ";
    }
    result.clear();
    cout << "\nRecursive: ";
    larger_left_right_recursive(numbers,result);
    for (int i = 0 ; i < result.size(); ++i){
        cout << result.at(i) << " ";
    }

    if(filename == "numbers1.txt"){
        for (int i = 0 ; i < result.size(); ++i){
            assert(result.at(i) == num1vec.at(i));
        }
        
    }
    else if(filename == "numbers2.txt"){
        for (int i = 0 ; i < result.size(); ++i){
            assert(result.at(i) == num2vec.at(i));
        }
    }
}
// PROBLEM 4

/* normal for loop starts at 0, iterative count starts a 1. If it the element before i is less than 
   or equal to, it increases the count. */
int increasing_sequences_iterative(vector<int> &numbers){
    int count = 1;
    int max = 0;
    for (int i = 0; i <numbers.size()-1; ++i){
        if (i > 0){
            
            if (numbers.at(i) >= numbers.at(i-1)){
                count ++;
            }
            else{
                if(max < count){
                    max =count;
                }
            
                count = 1;
            }
        }
    }
    return max;
}

// recursive function calls recursive helper function below.
int increasing_sequences_recursive(vector<int> &numbers){
    return increasing_sequences_recursive_helper(numbers, 0,0,1);
}

/* recursive helper function starts at index 0, iterative count starts at 1. Comparisons start at index 1 where if 
   the previous element is less than current element, count is increased. Else if count is greater than 
   the max (max = the biggest count) then the current count is the new max. */
int increasing_sequences_recursive_helper(vector<int> &numbers, int index, int max,int count){
    if(index >= numbers.size()){
        return max;
    }
    else if (index > 0){
        if (numbers.at(index) >= numbers.at(index-1)){
            count ++;
        }
        else{
            if(max < count){
                max =count;
            }
            
            count = 1;
        }
    }
    return increasing_sequences_recursive_helper(numbers,index+1, max,count);

}

void increasing_test(vector<int> &numbers, string filename){

    cout << "\n\nPROBLEM 4\n\nIterative: ";
    int iterative_result = increasing_sequences_iterative(numbers);
    int recursion_result = increasing_sequences_recursive(numbers);
    cout << iterative_result << "\nRecursive: ";
    cout << recursion_result << endl << endl;
    if(filename == "numbers1.txt"){
        assert(iterative_result == 3);
        assert(recursion_result == 3);

    }
    else if(filename == "numbers2.txt"){
        assert(iterative_result == 4);
        assert(recursion_result == 4);
    }
    
}