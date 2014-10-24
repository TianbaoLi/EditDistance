#include"Hash.h"
int Q_Gram=2,GramAmount;
void QGramListBuilder(char schema[DataLength])
{
	FILE *IndexOut;
	char Index[DataLength]={0};
	int GramCounter;
	IndexOut=fopen("Index List.dat","w");
	GramCounter=strlen(schema)-Q_Gram+1;
	for(int j=0;j<GramCounter;j++)
	{
		memset(Index,0,sizeof(char)*DataLength);
		for(int k=0;k<Q_Gram;k++)
			Index[k]=schema[k+j];
		fprintf(IndexOut,"%s %d\n",Index,0);
	}
	fclose(IndexOut);
}
void SchemaAdd(char schema[DataLength])
{
	QGramListBuilder(schema);
	GramAmount+=(int)strlen(schema)-Q_Gram+1;
	HASH Hash("Index List.dat",GramAmount);
	Hash.Init();
}