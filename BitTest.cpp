#include <iostream>
#include <cassert>
#include <vector>
using namespace std;



void SwapSort(vector<char>& pArr,vector<int>& pPos)
{
	assert(pArr.size()>0);
	assert(pPos.size()>0);
	assert(pArr.size() == pPos.size());

	char tmp = pArr[0];
	size_t counts = 1;
	int index = 0;
	while (counts < pArr.size())        //循环终止条件
	{
		if (index != pPos[index])
		{
			pArr[index] = pArr[pPos[index]];
			index = pPos[index];
			counts++;
		}
		else
		{
			index++;
			counts++;
		}
	}
	//最后一次填坑需要进行测试
	if (index != pPos[index])
	{
		pArr[index] = tmp;
	}
}

void NewSwapSort(vector<char>&pArr, vector<int>& pPos)
{
	assert(pArr.size()>0);
	assert(pPos.size()>0);
	assert(pArr.size() == pPos.size());

	char tmp	= pArr[0];						 //挖坑
	int  tmpPos = 0;							 //拿到所挖的坑位置的下标
	size_t counts = 1;
	int index = 0;

	while (counts < pArr.size())
	{
		while (index == pPos[index])
		{
			index++;
			counts++;
		}

		if (index == pArr.size())
			break;

		//在index处挖坑
		tmp = pArr[index];
		tmpPos = index;

		while (1)
		{
			//完成交换的条件
			if (index != pPos[index])
			{
				if (tmpPos == pPos[index])
				{
					//如果当前pPos中的下标与当前坑的下标相同
					//把坑的元素填入pArr中
					pArr[index] = tmp;
					pPos[index] = index;

					index++;
					break;
				}
				//如果当前pPos中的下标与当前坑的下标不同
				//则交换pArr中pPos[index]中的元素给当前位置
				pArr[index] = pArr[pPos[index]];

				//更新pPos中的对应下标和当前下标
				int j = pPos[index];
				pPos[index] = index;
				index = j;
				counts++;
			}
		}
	}
}

int main()
{
	char pArr[] = { 'A', 'B', 'C', 'D', 'E' };
	int pPos[] = { 2, 0, 1, 4, 3 };
	vector<char> v1(pArr, pArr + sizeof(pArr) / sizeof(pArr[0]));
	vector<int> v2(pPos, pPos + sizeof(pPos) / sizeof(pPos[0]));
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	NewSwapSort(v1, v2);
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	return 0;
}