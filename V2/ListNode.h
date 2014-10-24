#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#define PathLength 80
int ListAmount;
struct ListNode
{
	int HashNumber;
	int Count;
	int CurrentIndex;
	int CurrentHashNumber;
	char ListLocation[PathLength];
	ListNode(int x,int y,int z,char s[PathLength])
	{
		this->HashNumber=x;
		this->Count=y;
		this->CurrentIndex=z;
		strcpy(this->ListLocation,s);
	}
};
std::vector<ListNode> ListRecord,ListLong,ListShort;
bool HashNumberSort(ListNode &lt,ListNode &rt)
{
	return lt.HashNumber<rt.HashNumber;
}
bool CountSort(ListNode &lt,ListNode &rt)
{
	return lt.Count>rt.Count;
}
bool CurrentHashNumberSort(ListNode &lt,ListNode &rt)
{
	return lt.CurrentHashNumber<rt.CurrentHashNumber;
}
std::vector<ListNode> ListCountAdd(std::vector<ListNode> L,int x)
{
	struct ListNode Temp(x,0,0,"");
	for(std::vector<ListNode>::iterator Iter=L.begin();Iter!=L.end();Iter++)
		if(Iter->HashNumber==x)
			Iter->Count++;
	return L;
}
void ListDivide(int T,std::vector<ListNode>&L)
{
	for(int i=0;i<ListAmount-(T-1)&&!L.empty();i++)
	{
		ListShort.push_back(L.back());
		L.pop_back();
	}
	while(!L.empty())
	{
		ListLong.push_back(L.back());
		L.pop_back();
	}
}
