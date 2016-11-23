#include <iostream>
using namespace std;
#include <vector>

//class Solution {
//public:
//	static bool Find(int target, vector<vector<int>> array) 
//	{
//		for (int i = 0; i < array.size(); i++)
//		{
//			if (array[i][array[i].size() - 1] < target)
//			{
//				continue;
//			}
//			else if (array[i][array[i].size() - 1] > target)
//			{
//				//定位到数组的行
//				for (int j = array[i].size() - 1; j >= 0; j--)
//				{
//					if (array[i][j] == target)
//						return true;
//				}
//				return false;
//			}
//			else
//				return false;
//		}
//		return false;
//	}
//};
//
//
//int main()
//{
//	vector<vector<int>> a;
//	int index = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		vector<int> b;
//		for (int j = 0; j < 5; j++)
//		{
//			b.push_back(index++);
//		}
//		a.push_back(b);
//	}
//	cout << Solution::Find(15, a);
//	return 0;
//}