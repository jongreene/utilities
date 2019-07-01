#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <stack>
using namespace std;

#define DEBUG (0)
void testPrint(string output)
{
  cout << output << "\n";
}

void PrintArray(vector<int> arr)
{
	for(auto e : arr)
		cout << e << " ";

	cout << endl;
}

void Prind2DArray()
{

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
		PrintArray(arrMerged);

	}
	return arrMerged;
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

	vector<int> sorted1 = {1,3,5,7,9,10};
	vector<int> sorted2 = {3,4,5,6,9,11,16,17};
	MergeSortedArrays(sorted1,sorted2);
	// PrintArray(MergeSortedArrays(sorted1,sorted2));

	return 0;
}

// Rearrange positive and negative values in an array
