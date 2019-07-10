#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <stack>
using namespace std;

#define DEBUG (0)
void testPrint(string output)
{
  cout << output << "\n";
}

template <class T>
void PrintArray(vector<T> arr)
{
	//no checking is being done
	for(auto e : arr)
		cout << e << " ";

	cout << endl;
}

template <class T>
void Prind2DArray(vector<vector<T>> arr)
{
	for(auto e : arr)
		PrintArray<T>(e);
}
// Find the second minimum element of an array
int GetSecondMin(vector<int> &elements)
{
  int smallest = INT_MAX;
  int second_smallest = INT_MAX;

  for(auto e : elements)
  {
    if(e < second_smallest)
    {
      smallest = second_smallest;
      second_smallest = e;
    }
    else if(e < smallest)
    {
      smallest=e;
    }
  }
  return second_smallest;
}

// First non-repeating integer in an array
int FirstNonRepeatInt(vector<int> &elements)
{
	stack<int> recorder;
	int last = elements.at(0);
	for(int i=1; i<elements.size(); i++)
	{
		if(last == elements.at(i))
		{
			if(recorder.empty())
				recorder.push(last);
		}
		else if(last != elements.at(i))
		{
			if(recorder.empty())
				return last;

			recorder.pop();
			last = elements.at(i);
		}
	}
	//some sort of invalid flag needed
	return -1;
}


// Evaluate postfix expression
int EvaluatePostfix(std::vector<char> exp)
{
	stack<int> current_exp;
	for(auto c : exp)
	{
		if(isdigit(c))
		{
			current_exp.push(c - '0');
		}
		else
		{
			int val1 = current_exp.top();current_exp.pop();
			int val2 = current_exp.top();current_exp.pop();
			switch (c)
            {
	            case '+': current_exp.push(val2 + val1); break;
	            case '-': current_exp.push(val2 - val1); break;
	            case '*': current_exp.push(val2 * val1); break;
	            case '/': current_exp.push(val2/val1); break;
            }
		}
	}
	return current_exp.top();
}

/*
 * Merge two sorted arrays
 * The below method takes advantage of the fact that the length of the initial
 * array sizes.
 */
vector<int> MergeSortedArrays(vector<int> &arr1, vector<int> &arr2)
{
	int elements = arr1.size()+arr2.size();
	vector<int> arrMerged(elements);

	int left_index = 0, right_index = elements-1;
	int arr1_left_index = 0, arr1_right_index = arr1.size()-1;
	int arr2_left_index = 0, arr2_right_index = arr2.size()-1;
	while(left_index < right_index)
	{
		if(arr1_left_index >= arr1_right_index && arr2_left_index < arr2_right_index)
			arrMerged[left_index++] = arr2[arr2_left_index++];
		else if(arr2_left_index >= arr2_right_index && arr1_left_index < arr1_right_index)
			arrMerged[left_index++] = arr1[arr1_left_index++];
		else if(right_index==left_index)
		{
			if((arr1_left_index-arr1_right_index)==0)
				arrMerged[right_index] = arr1[arr1_left_index];
			else
				arrMerged[right_index] = arr2[arr2_left_index];
		}
		else
		{
			if(arr2_left_index <= arr2_right_index && arr1_left_index <= arr1_right_index)
			{
				if(arr1[arr1_left_index] < arr2[arr2_left_index])
					arrMerged[left_index++] = arr1[arr1_left_index++];
				else
					arrMerged[left_index++] = arr2[arr2_left_index++];
			}
			if(arr2_left_index <= arr2_right_index && arr1_left_index <= arr1_right_index)
			{
				if(arr1[arr1_right_index] < arr2[arr2_right_index])
					arrMerged[right_index--] = arr2[arr2_right_index--];
				else
					arrMerged[right_index--] = arr1[arr1_right_index--];
			}
		}

		if(left_index==right_index)
		{
			if(arr1_left_index-arr1_right_index == 0)
				arrMerged[right_index] = arr1[arr1_right_index];
			else
				arrMerged[right_index] = arr2[arr2_right_index];
		}
	}
	return arrMerged;
}

bool isAnagram(unordered_map<char,int> &anagram, string str)
{
	unordered_map<char,int> local_bank = anagram;
	for(auto c : str)
	{
		if(local_bank.find(c)==local_bank.end())
			return false;

		if(local_bank[c]-- < 1)
			return false;
	}

	return true;
}

int CountAnagrams(string str)
{
	unordered_map<char,int> anagram;
	unordered_map<char,int> anagram2;

	for(int k = 0; k<str.length()-1; k++)
	{
		string substr = str.substr(0,k+1);
		anagram[str.at(k)]++;

		for(int i=0; i<substr.length(); i++)
		{
			anagram2 = anagram;

			cout << substr << "   ";

			for(int j=i+1; j<k; j++)
			{
				if(isAnagram(anagram2,substr.substr(j,j+i)))
					cout << "  " << substr.substr(j,j+i);
			}
		}
		cout << endl;

	}

	return 5;
}

int main(int argc, char** argv)
{
	#if(DEBUG)
	testPrint();
	#endif
	// vector<int> min_elements = {-21,1,2,1,43,12,2323,1,-23,2333,231};
	// cout << GetSecondMin(elements) << endl;

	// vector<int> non_repeat_elements = {3,3,2,2,2,2,2,4,4,4,4,3,3,7,3,3};
	// cout << FirstNonRepeatInt(non_repeat_elements) << endl;

	// vector<int> sorted1 = {1,3,5,7,9,10,11,16,17};
	// vector<int> sorted2 = {3,4,5,6,9,11,18,19,22};
	// PrintArray<int>(MergeSortedArrays(sorted1,sorted2));

	// vector<char> postfil = {'9','2','3','*','+'};
	// cout << EvaluatePostfix(postfil) << endl;

	string input = "ifailuhkqq";
	CountAnagrams(input);

	return 0;
}
