int T_Occurrence;
std::vector<int> Answer;
int Hashmap(char *x)
{
	int Seed=13;
	int Sol=0;
	while(*x)
		Sol=(Sol*Seed+(*x++))%BigPrime;
	return Sol%BigPrime;
}
void DataFoundSegment(char schema[DataLength],std::vector<ListNode>&L)
{
	std::vector<int> TargetGram;
	char GramTemp[DataLength];
	int GramTempHashAnswer;
	for(int i=0;i+Q_Gram<(int)strlen(schema)+1;i++)
	{
		memset(GramTemp,0,sizeof(char)*DataLength);
		for(int j=0;j<Q_Gram;j++)
			GramTemp[j]=schema[i+j];
		GramTempHashAnswer=Hashmap(GramTemp);
		TargetGram.push_back(GramTempHashAnswer);
	}
	sort(TargetGram.begin(),TargetGram.end());
	std::vector<int>::iterator IntIter=TargetGram.begin();
	for(std::vector<ListNode>::iterator ListNodeIter=L.begin();ListNodeIter!=L.end();)
	{
		if(IntIter==TargetGram.end())
		{
			ListNodeIter=L.erase(ListNodeIter,L.end());
			break;
		}
		if(ListNodeIter->HashNumber==*IntIter)
		{
			ListNodeIter++;
			IntIter++;
		}
		else if(ListNodeIter->HashNumber<*IntIter)
			ListNodeIter=L.erase(ListNodeIter);
		else
			IntIter++;
	}
}
//<vector> ListRecord¿½±´µ½ListRecordBackUp
void DivideSkip(char schema[DataLength])
{
	std::vector<ListNode>ListRecordBackUp(ListRecord);
	sort(ListRecordBackUp.begin(),ListRecordBackUp.end(),HashNumberSort);
	DataFoundSegment(schema,ListRecordBackUp);
	ListAmount=ListRecordBackUp.size();
	sort(ListRecordBackUp.begin(),ListRecordBackUp.end(),CountSort);
	ListDivide(T_Occurrence,ListRecordBackUp);
	int CountShort,CountLong,HashNumber;
	FILE *HashNumberIn;
	char GetsTemp[DataLength];
	for(std::vector<ListNode>::iterator ListNodeIter=ListShort.begin();ListNodeIter!=ListShort.end();ListNodeIter++)
	{
		HashNumberIn=fopen(ListNodeIter->ListLocation,"r");
		for(int i=0;i<ListNodeIter->CurrentIndex+1;i++)
			fgets(GetsTemp,DataLength,HashNumberIn);
		fscanf(HashNumberIn,"%d",&HashNumber);
		ListNodeIter->CurrentIndex++;
		ListNodeIter->CurrentHashNumber=HashNumber;
		fclose(HashNumberIn);
	}
	sort(ListShort.begin(),ListShort.end(),CurrentHashNumberSort);
	int MergeMin;
	std::vector<ListNode>::iterator ListNodeAddIter;
	while(!ListShort.empty())
	{
		MergeMin=0x7FFFFFFF;
		CountShort=0;
		CountLong=0;
		for(std::vector<ListNode>::iterator ListNodeIter=ListShort.begin();ListNodeIter!=ListShort.end();ListNodeIter++)
			if(ListNodeIter->CurrentHashNumber<MergeMin)
				MergeMin=ListNodeIter->CurrentHashNumber;
		sort(ListShort.begin(),ListShort.end(),CurrentHashNumberSort);
		while(!ListShort.empty()&&ListShort.begin()->CurrentHashNumber==MergeMin)
		{
			CountShort++;
			ListNodeAddIter=ListShort.begin();
			if(ListNodeAddIter->CurrentIndex<=ListNodeAddIter->Count)
			{
				HashNumberIn=fopen(ListNodeAddIter->ListLocation,"r");
				for(int i=0;i<ListNodeAddIter->CurrentIndex+1;i++)
					fgets(GetsTemp,DataLength,HashNumberIn);
				if(fscanf(HashNumberIn,"%d",&HashNumber)<0)
					ListNodeAddIter->CurrentHashNumber=-1;
				else
					ListNodeAddIter->CurrentHashNumber=HashNumber;
				ListNodeAddIter->CurrentIndex++;
				fclose(HashNumberIn);
			}
			else
				ListShort.erase(ListNodeAddIter);
			if(ListShort.empty())
				break;
			if(ListShort.begin()->CurrentIndex>ListShort.begin()->Count)
				ListShort.erase(ListShort.begin());
			sort(ListShort.begin(),ListShort.end(),CurrentHashNumberSort);
		}
		for(std::vector<ListNode>::iterator ListNodeIter=ListLong.begin();ListNodeIter!=ListLong.end();ListNodeIter++)
		{
			HashNumberIn=fopen(ListNodeIter->ListLocation,"r");
			fgets(GetsTemp,DataLength,HashNumberIn);
			for(int i=0;i<ListNodeIter->Count;i++)
			{
				fscanf(HashNumberIn,"%d",&HashNumber);
				if(HashNumber==MergeMin)
				{
					CountLong++;
					break;
				}
			}
			fclose(HashNumberIn);
		}
		if(CountShort+CountLong>=T_Occurrence)
			Answer.push_back(MergeMin);
		for(std::vector<ListNode>::iterator ListNodeIter=ListShort.begin();ListNodeIter!=ListShort.end();ListNodeIter++)
			if(ListShort.size()==1&&ListNodeIter->CurrentIndex>ListNodeIter->Count)
				return ;
			else if(ListNodeIter->CurrentIndex>ListNodeIter->Count)
				ListNodeIter=ListShort.erase(ListNodeIter);
	}
}
bool SchemaFound(char schema[DataLength])
{
	DivideSkip(schema);
	if(Answer.empty())return 0;
	else return 1;
}