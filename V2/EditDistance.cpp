#define _CRT_SECURE_NO_WARNINGS
#include"SchemaAdd.h"
#include"SchemaFound.h"
int Threshold=1,SchemaLength,MinList;
char Schema[DataLength];
void DeleteFolder()
{
	char str1[DataLength] ="RMDIR /S /Q HashList\\";
	char str2[DataLength] ="del V2.in";
	system(str1);
	system(str2);
} 
void Init(char schema[DataLength])
{
	SchemaLength=strlen(schema);
	Threshold=1;
	Q_Gram=2;
	GramAmount=0;
	T_Occurrence=0;
	MinList=0;
	Answer.clear();
	ListAmount=0;
	ListLong.clear();
	ListShort.clear();
	T_Occurrence=(SchemaLength-Q_Gram+1)-Threshold*Q_Gram;
	MinList=(SchemaLength-Q_Gram+1)-(T_Occurrence-1);
}
int main()
{
	DeleteFolder();
	_mkdir(FolderName);
	system("DataScratch.exe");
	FILE *SchemaIn,*SchemaListOut;
	SchemaIn=fopen("V2.in","r");
	int k=0;
	while(fscanf(SchemaIn,"%s",Schema)>0)
	{
		k++;
		bool b=0;
		for(int i=0;i<(int)strlen(Schema);i++)
			if(Schema[i]==':')
			{
				b=1;
				break;
			}
		if(k==115)
		{
			k+=0;
		}
		if(b==0)
		{
			Init(Schema);
			if(!SchemaFound(Schema))
			{
				SchemaAdd(Schema);
				SchemaListOut=fopen("SchemaList.dat","a");
				fprintf(SchemaListOut,"%s\n",Schema);
				fclose(SchemaListOut);
			}
		}
		memset(Schema,0,sizeof(char)*DataLength);
	}
	fclose(SchemaIn);
	
	return 0;
}
