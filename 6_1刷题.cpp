#include <iostream>
using namespace std;
#include <vector>
#include <cassert>
#include <cmath>
#include <string>
#include <cstdlib>

//size_t Port_Sort(int* a, int begin, int end)
//{
//	size_t left = begin;
//	size_t right = end - 1;
//	int key = a[end];
//	while (left < right)
//	{
//		while (left<right && a[left] <= key)
//		{
//			//left找比key大的
//			left++;
//		}
//		while (left < right && a[right] >= key)
//		{
//			//right为找a中小于key的下标
//			right--;
//		}
//
//		if (left < right)             //left < right  交换
//		{
//			swap(a[left], a[right]);
//		}
//	}
//	if (key <= a[left])
//	{
//		swap(a[end], a[left]);
//		return left;
//	}
//	else
//		return end;
//}


size_t Port_Sort(int* v1, int begin, int end){
	int left = begin;
	int right = end - 1;
	int key = v1[end];
	while (left < right){
		while (left < right && v1[left] <= key){
			left++;
		}
		while (left < right && v1[right] >= key){
			right--;
		}
		if (left < right){
			swap(v1[left], v1[right]);
		}
	}
	// left >= right 
	if (v1[left] >= key){
		swap(v1[left], v1[end]);
		return left;
	}
	return end;

}

//快速排序挖坑法
size_t Port_Sort_K(int* v1, int begin, int end)
{
	int left = begin;
	int right = end - 1;
	int key = v1[end];
	int index = end;
	while (left < right)
	{
		while (left < right && v1[left] <= key){
			left++;
		}
		//填坑
		if (left < right){
			v1[index] = v1[left];
			index = left;
		}
		while (left < right && v1[right] >= key){
			right--;
		}
		if (left < right){
			v1[index] = v1[right];
			index = right;
		}
	}
	v1[index] = key;
	return index;
}

void Quick_Sort(int* v1, int begin, int end)
{
	//assert(v1.size() >= 0);
	int div = Port_Sort_K(v1, begin, end);
	if (div - 1 > begin){
		Quick_Sort(v1, begin, div - 1);
	}
	if (div + 1 < end){
		Quick_Sort(v1, div + 1, end);
	}

}

void Adjust_Down(int* a,int size,int parent)
{
	assert(a);
	//拿到子节点
	int child = parent * 2 + 1;
	while (child < size){
		if ((child + 1) < size && a[child] < a[child + 1]){
			child = child + 1;
		}
		if (a[parent] < a[child]){
			swap(a[parent], a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

void Heap_Sort(int* a,int size)
{
	//建堆
	for (int i = (size - 1 - 1) / 2; i >= 0; i--){
		Adjust_Down(a, size, i);
	}

	for (int i = size - 1; i > 0;){
		swap(a[0], a[i]);
		Adjust_Down(a, --i, 0);
	}
}

//插入排序
void Insert_Sort(int* a,int size)
{
	assert(a);
	for (int index = 1; index < size; index++){
		int pos = index - 1;
		int tmp = a[index];
		while (pos >= 0 && a[pos] > tmp){
			swap(a[pos], a[pos + 1]);
			//a[pos + 1] = a[pos];
			pos--;
		}
		//a[pos+1] = tmp;
	}
}

//希尔排序
void Sheel_Sort(int* a,int size)
{
	int gap = size;
	while (gap > 1){
		gap = gap / 3 + 1;
		for (int index = gap; index < size; index += gap){
			int pos = index - gap;
			int tmp = a[index];
			while (pos >= 0 && a[pos] > tmp){
				swap(a[pos], a[pos + gap]);
				pos -= gap;
			}
		}
	}
}

void _MergeSort(int* a, int* tmp, int begin,int end){
	int mid = begin + (end - begin) / 2;
	int left1 = begin;
	int	right1 = mid ;
	int left2 = mid + 1;
	int right2 = end;
	if (left1 < right1){
		_MergeSort(a,tmp,left1,right1);
	}
	if (left2 < right2){
		_MergeSort(a, tmp, left2, right2);
	}
	int index = begin;
	while (left1<=right1 && left2<=right2){
		if (a[left1]>a[left2])
			tmp[index++] = a[left2++];
		else
			tmp[index++] = a[left1++];
	}
	while (left1 <= right1){
		tmp[index++] = a[left1++];
	}
	while (left2 <= right2){
		tmp[index++] = a[left2++];
	}

	for (int i = begin; i <= end; i++){
		a[i] = tmp[i];
	}
}

void Merge_Sort(int* a, int size){
	assert(a);
	int* tmp = new int[size];
	_MergeSort(a,tmp,0,size-1);
	delete[] tmp;
}

void PrintArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void TestQuickSort()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Quick_Sort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestInsertSort()
{
	//int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Insert_Sort(a,sizeof(a) / sizeof(a[0]) );
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestHeapSort()
{
	//int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Heap_Sort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestSheelSort()
{
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Sheel_Sort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

void TestMergeSort()
{
	int a[] = { 10, 9, 8, 7, 6, 5, -4, 3, 2, 1 };
	//int a[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };
	Merge_Sort(a, sizeof(a) / sizeof(a[0]));
	PrintArray(a, sizeof(a) / sizeof(a[0]));
}

int max(int a, int b){
	if (a > b){
		return a;
	}
	else
		return b;
}
//求非连续子数组和的最大值
//int MaxSum(int* a, int size,vector<int>& out){
//	assert(a);
//
//	//保存当前序列的和
//	int m2 = 0;
//	//序列的和
//	int sum = 0;
//	int tmpIndex = size - 1;
//	for (int i = size - 1; i >= 0; i--)
//	{
//		if (m2 < 0) 
//			m2 = 0;  //处理最后一位为负数或全为负数的情况
//		int tmp = sum;
//
//		if (a[i] + m2 >= sum){
//			if (i + 1 != tmpIndex){
//				cout << a[i] << " ";
//				out.push_back(i);
//				sum = a[i] + m2;
//				tmpIndex = i;
//			}
//		}
//		m2 = tmp;
//	}
//	return sum;
//}


//已知二叉树的前序和终须求后序序列
//#include <iostream>  
//#include <string>  
//using namespace std;
//
//int find(const string &str, char c)
//{
//	for (int i = 0; i < str.size(); ++i)
//	if (c == str[i])
//		return i;
//	return -1;
//}

//bool PreMid(const string &pre, const string &mid)
//{
//	if (pre.size() == 0)
//		return false;
//	if (pre.size() == 1)
//	{
//		cout << pre;
//		return true;
//	}
//
//	//根节点是第一个元素  
//	int k = find(mid, pre[0]);
//
//	//左子树
//	string pretmp = pre.substr(1, k);
//	string midtmp = mid.substr(0, k);
//	PreMid(pretmp, midtmp);
//
//	//右子树
//	pretmp = pre.substr(k + 1, pre.size() - k - 1);
//	midtmp = mid.substr(k + 1, mid.size() - k - 1);
//	PreMid(pretmp, midtmp);
//
//	//变成后序遍历要最后输出节点的值  
//	cout << pre[0];
//}


//int main()
//{
//	vector<int> out;
//	int a[] = { 10,-10,-11,20,-20,-30,5,6,8,9};
//	//TestQuickSort();
//	//TestHeapSort();
//	//TestInsertSort();
//	//TestSheelSort();
//	//TestMergeSort();
//	cout << MaxSum(a, sizeof(a) / sizeof(a[0]),out);
//	cout << endl;
//	for (int i = 0; i < out.size(); i++){
//		cout << out[i] << " ";
//	}
//	cout << endl;
//	string pre = "ABDECFG";
//	string mid = "DBEAFCG";
//	PreMid(pre,mid);
//	return 0;
//}


//STL string 的使用练习 

//int main()
//{
//	string a1 = "this is python";
//	//test1 :a1.replace(8,6,"C++");
//	a1.replace();
//	cout << a1 << endl;
//	return 0;
//}


//给出前序和中序遍历求后序遍历

int find(const string& pre,char c)
{
	for (int i = 0; i<pre.size(); i++){
		if (pre[i] == c)
			return i;
	}
	return -1;
}

void preMid(const string& pre, const string& mid)
{
	if (pre.size() == 0 && mid.size()==0)
		return;
	
	int index = find(mid, pre[0]);
	//分割子串
	//substr(pos,len)
	string pretmp = pre.substr(1, index);
	string midtmp = mid.substr(0, index);
	//左子树遍历
	preMid(pretmp, midtmp);
	//右子树遍历
	pretmp = pre.substr(index + 1, pre.size() - index - 1);
	midtmp = mid.substr(index+1, mid.size() - index - 1);
	preMid(pretmp, midtmp);

	cout << pre[0] << " ";
}

//根据后序和中序序列求前序序列
void backMid(const string& back, const string& mid)
{
	if (back.size() == 0 && mid.size() == 0){
		return;
	}

	//根据后序遍历在中序序列中找到根节点的下标
	int index = find(mid, back[back.size() - 1]);

	cout << back[back.size() - 1] << " ";
	string backTmp = back.substr(0,index);
	string midTmp = mid.substr(0,index);
	backMid(backTmp, midTmp);

	backTmp = back.substr(index, back.size() - 1 - index);
	midTmp = mid.substr(index + 1, mid.size() - 1 - index);
	backMid(backTmp, midTmp);
}

int main()
{
	string mid = "DBEAFCG";
	string pre  = "ABDECFG";
	string back = "DEBFGCA";
	cout << "pre:" << pre << endl;
	cout << "mid:" << mid << endl;
	cout << "back:" << back << endl;
	preMid(pre, mid);
	cout << endl;
	backMid(back, mid);
	return 0;
}
