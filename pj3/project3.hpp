/*
Diego Rivera Project 3 
*/

#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

/* Function prototypes */

bool read_inputs(vector<int>& numbers, string filename);
void run_tests(string filename);


/* PROBLEM 1 */

// normal for loop that starts from 0 and starts if conditions at i>=1.
int count_inversions_iterative(const vector<int>& numbers);

// recursive function calls recursive helper function below.
int count_inversions_recursive(const vector<int>& numbers);
// recursive helper starts at the end of the vector and works its way to the front.
int count_inversions_recursive_helper(const vector<int>& numbers, int n);

void inversions_test(const vector<int>& numbers, string inputfile);


/* PROBLEM 2 */

/* normal for loop to iterate through the vector and uses a nested for loop to find closest 
   larger integer from the left. Outer for loop starts at 0. */
void largest_left_iterative(const vector<int>& numbers, vector<int>& result);

// recusive function calls recursive helper function below.
void largest_left_recursive(const vector<int>& numbers, vector<int>& result);
/* recursive helper below starts at the 0 index to traverse through the vector and calls
   "larger_left_right_recursive_helperL" to find the closest larger interger from the left. */
void largest_left_recursive_helper(const vector<int>& numbers, vector<int>& result, int index);

void largest_left_test(const vector<int>& numbers, vector<int>& result, string filename);
// PROBLEM 3

/* normal for loop that starts from 0 and uses two nested for loops to find the closest larger 
   integer from left and right, compares them, result is inserted in the result vector */
void larger_left_right_iterative(const vector<int>& numbers, vector<int>& result);

// recursive function calls recursive helper function below
void larger_left_right_recursive(const vector<int>& numbers, vector<int>& result);
/* recursive helper function starts at the end of the vector and works its way to the front of the vector.
   Calls helper function L (left) and R (right) to find the closest larger interger from the left and right
   to compare them */
void larger_left_right_recursive_helper(const vector<int>& numbers, vector<int>& result, int index);
/* recursive helper L iterates to the front of the list to find the closest larger interger. 
   if it doesnt find anything it returns 0 */
int larger_left_right_recursive_helperL(const vector<int>& numbers, vector<int>& result, int index, int value);
/* recursive helper R iterates to the end of the list to find the closest larger interger. 
   if it doesnt find anything it returns 0 */
int larger_left_right_recursive_helperR(const vector<int>& numbers, vector<int>& result, int index, int value);

void left_right_test(const vector<int>& numbers, vector<int>& result, string filename);

// PROBLEM 4

/* normal for loop starts at 0, iterative count starts a 1. If it the element before i is less than 
   or equal to, it increases the count. */
int increasing_sequences_iterative(vector<int> &numbers);

// recursive function calls recursive helper function below
int increasing_sequences_recursive(vector<int> &numbers);
/* recursive helper function starts at index 0, iterative count starts at 1. Comparisons start at index 1 where if 
   the previous element is less than current element, count is increased. Else if count is greater than 
   the max (max = the biggest count) then the current count is the new max */
int increasing_sequences_recursive_helper(vector<int> &numbers, int index, int max, int count);

void increasing_test(vector<int> &numbers, string filename);
