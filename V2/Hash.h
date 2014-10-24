#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<string>
#include<cstring>
#include<io.h>
#include<direct.h>
#include<algorithm>
#include"ListNode.h"
#define BigPrime 2147483647
#define DataLength 80
#define FolderName "HashList\\"
class HASH
{
	private:
        int Amount;
		int FoundAnswer;
		int DataNo;
        char DataFound[DataLength];
        char DataRead[DataLength];
        char DataName[DataLength];
	public:
		HASH(char *x,int y);
		void DeleteFolder();
		void Init();
		int Hashmap(char *x);
		void Insert(char *x,int y);
		void Find(char *x);
		int ReturnFoundAnswer();
};
void HASH::DeleteFolder()
{
	char str[120] ="RMDIR /S /Q ";
	strcat(str,FolderName);
	system(str);
} 
HASH::HASH(char *x,int y)
{
	Amount=y;
	FoundAnswer=0;
	memset(DataFound,0,sizeof(char)*DataLength);
	memset(DataRead,0,sizeof(char)*DataLength);
	memset(DataName,0,sizeof(char)*DataLength);
	strcpy(DataName,x);
	//DeleteFolder();
	//_mkdir(FolderName);
}
void HASH::Init()
{
	FILE *DataIn;
	DataIn=fopen(DataName,"r");
	for(int i=0;i<Amount;i++)
	{
		fscanf(DataIn,"%s %d",&DataRead,&DataNo);
		Insert(DataRead,DataNo);
	}
	fclose(DataIn);
}
int HASH::Hashmap(char *x)
{
	int Seed=13;
	int Sol=0;
	while(*x)
		Sol=(Sol*Seed+(*x++))%BigPrime;
	return Sol%BigPrime;
}
void HASH::Insert(char *x,int y)
{
	int HashAnswer,NoCompare;
	HashAnswer=Hashmap(x);
	char Name[DataLength],Path[PathLength],IndexCompare[DataLength];
	bool IndexMatched=0,NoMatched=0;
	memset(Name,0,sizeof(char)*DataLength);
	memset(Path,0,sizeof(char)*PathLength);
	memset(IndexCompare,0,sizeof(char)*DataLength);
	_itoa(HashAnswer,Name,10);
	strcpy(Path,FolderName);
	strcat(Path,Name);
	strcat(Path,".dat");
	while(_access(Path,0)==0)
	{
		FILE *CompareIn;
		CompareIn=fopen(Path,"r");
		fscanf(CompareIn,"%s",&IndexCompare);
		if(strcmp(IndexCompare,x)==0)
		{
			IndexMatched=1;
			while(fscanf(CompareIn,"%d",&NoCompare)!=EOF)
			{
				if(y==NoCompare)
				{
					NoMatched=1;
					break;
				}
			}
		}
		fclose(CompareIn);
		if(IndexMatched==1)break;
		memset(Path,0,sizeof(char)*DataLength);
		strcpy(Path,FolderName);
		HashAnswer++;
		if(HashAnswer==BigPrime-1)HashAnswer=0;
		_itoa(HashAnswer,Name,10);
		strcat(Path,Name);
		strcat(Path,".dat");
	}
	if(IndexMatched==0)
	{
		FILE *HashNumberOut;
		HashNumberOut=fopen(Path,"w");
		fprintf(HashNumberOut,"%s\n%d\n",x,y);
		fclose(HashNumberOut);
		struct ListNode Temp(HashAnswer,1,0,Path);
		ListRecord.push_back(Temp);
	}
	else if(NoMatched==0)
	{
		FILE *HashNumberOut;
		HashNumberOut=fopen(Path,"a+");
		fprintf(HashNumberOut,"%d\n",y);
		fclose(HashNumberOut);
		ListRecord=ListCountAdd(ListRecord,HashAnswer);
	}
}
void HASH::Find(char *x)
{
	strcpy(DataFound,x);
	int HashAnswer;
	HashAnswer=Hashmap(DataFound);
	char Name[DataLength],Compare[DataLength],Path[PathLength];
	memset(Name,0,sizeof(char)*DataLength);
	memset(Compare,0,sizeof(char)*DataLength);
	memset(Path,0,sizeof(char)*PathLength);
	_itoa(HashAnswer,Name,10);
	strcpy(Path,FolderName);
	strcat(Path,Name);
	strcat(Path,".dat");
	while(_access(Path,0)==0)
	{
		freopen(Path,"r",stdin);
		while(scanf("%s",Compare)!=EOF)
		{
			getchar();
			if(strcmp(Compare,DataFound)==0)
			{
				FoundAnswer=1;
				break;
			}
		}
		fclose(stdin);
		if(FoundAnswer==1)return;
		memset(Path,0,sizeof(char)*DataLength);
		strcpy(Path,FolderName);
		HashAnswer++;
		if(HashAnswer==BigPrime-1)HashAnswer=0;
		_itoa(HashAnswer,Name,10);
		strcat(Path,Name);
	}
	FoundAnswer=0;
	return;
}
int HASH::ReturnFoundAnswer()
{
	return FoundAnswer;
}
