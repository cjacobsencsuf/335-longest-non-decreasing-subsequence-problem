///////////////////////////////////////////////////////////////////////////////
// subsequence.hpp
//
// Two algorithms for solving the longest non-decreasing subsequence problem.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <sstream>
#include <vector>

using sequence = std::vector<int>;

// Convert a sequence into a human-readable string useful for pretty-printing
// or debugging.
std::string sequence_to_string(const sequence& seq) {
  std::stringstream ss;
  ss << "[";
  bool first = true;
  for (auto& x : seq) {
    if (!first) {
      ss << ", ";
    }
    ss << x;
    first = false;
  }
  ss << "]";
  return ss.str();
}

// Generate a pseudorandom sequence of the given size, using the given
// seed, where all elements are in the range [0, max_element]. max_element
// must be non-negative.
sequence random_sequence(size_t size, unsigned seed, int max_element) {

    assert(max_element >= 0);

    sequence result;

    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(0, max_element);

    for (size_t i = 0; i < size; ++i) {
        result.push_back(dist(gen));
    }

    return result;
}

bool is_nondecreasing(const sequence& A) 
{//is_nondecreasing
	for (size_t i = 1; i < A.size(); ++i) 
		{//for
		//check for decreasing
		if(A[i-1] > A[i])
			{//if
			//decreasing
			return false;
			}//if
  		}//for
	//non-decreasing
	return true;
}//is_nondecreasing

sequence longest_nondecreasing_end_to_beginning(const sequence& A) 
{//longest_nondecreasing_end_to_beginning

	const size_t n = A.size();

	// populate the array H with 0 values
	std::vector<size_t> H(n, 0);

	// calculate the values of array H
	// note that i has to be declared signed, to avoid an infinite loop, since
	// the loop condition is i >= 0
	for (signed int i = n-2;  i>= 0; i--) 
		{//outer for loop 
		for (size_t j = i+1; j < n ; j++) 
			{//inner for loop
			// write the statements that compute the value of
        		// H[i] based on conditions that involve A[i], A[j]
        		// and H[j]
			//if A[i] <= A[j] 	&&	H[i] <= H[j]		
			if((A[i] <= A[j]) && (H[i] <= H[j]))
				{//if
				//update H[i]
				H[i] = 1 + H[j];
				}//if
    			}//inner for loop
  		}//outer for loop

	// calculate in max the length of the longest subsequence
  	// by adding 1 to the maximum value in H
 	auto max = *std::max_element(H.begin(), H.end()) + 1;

	// allocate space for the subsequence R
	std::vector<int> R(max);

	// add elements to R by whose H's values are in non-decreasing order,
	// starting with max-1
  	// store in index the H values sought
    	size_t index = max-1, j = 0;
    	for (size_t i = 0; i < n; ++i) 
		{//for
      		if (H[i] == index) 
			{//if
          		// write the statements to add A[i] to the sequence R by
          		// storing it into R[j], decrement index and increment j
			R[j] = A[i];
			--index;
			++j;
      			}//if
    		}//for

  	return sequence(R.begin(), R.begin() + max);
}//longest_nondecreasing_end_to_beginning

sequence longest_nondecreasing_powerset(const sequence& A) 
{//longest_nondecreasing_powerset
	const size_t n = A.size();
  	sequence best;
  	std::vector<size_t> stack(n+1, 0);
  	size_t k = 0;
  	while (true) 
		{//while

    		if (stack[k] < n) 
			{//if
      			stack[k+1] = stack[k] + 1;
      			++k;
    			}//if
		else 
			{//else
      			stack[k-1]++;
      			k--;
    			}//else

    		if (k == 0) 
			{//if
      			break;
    			}//if

    		sequence candidate;
    		for (size_t i = 1; i <= k; ++i) 
			{//for
      			candidate.push_back(A[stack[i]-1]);
    			}//for
   		// write the if statement to test whether candidate determines
   		// a non-decreasing sequence AND has a size larger than the size
   		// of the current best
   		// if both conditions are satisfied, then stored candidate in best
		//if candidate is nondecreasing AND candidate.size > best.size
		if((is_nondecreasing(candidate)) && (candidate.size() > best.size()))
			{//if
			best = candidate;
			}//if
    		}//while

  	return best;
}//longest_nondecreasing_powerset
