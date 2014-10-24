#include<iostream>
#include<fstream>
using namespace std;
string xml=".xml";
string root="cse444";
void solve(string cla,string name)
{
	string path="cse444\\";
	string temp="\\schemas\\";
	path+=cla;
	path+=temp;
	path+=name;
	path+=xml;
	ifstream fin(path.c_str());
	string s;
	ofstream fout("V2.in",ios::app);
	fout<<"Schema:"<<name<<endl;
	while(getline(fin,s))
	{
		if(s.find("table name",0)!=string::npos)
		{
			int lpos,rpos;
			string prop;
			lpos=s.find("\"",0);
			rpos=s.find("\"",lpos+1);
			prop.assign(s,lpos+1,rpos-1-lpos);
			fout<<prop<<endl;
		}
	}
}
int main()
{
	system("RMDIR /S /Q cse444_DataList");
	system("md cse444_DataList");
	system("del V2.in");
	system("del cse444_DataList\\FolderList.txt");
	system("dir /b cse444 >> cse444_DataList\\FolderList.txt");
	ifstream fin("cse444_DataList\\FolderList.txt");
	string s;
	while(getline(fin,s))
		if(s.find(".",0)==string::npos)
		{
			string order1="md cse444_DataList\\";
			order1+=s;
			system(order1.c_str());
			string order2="dir /b cse444\\";
			string temp1="\\schemas >>cse444_DataList\\";
			string temp2="\\SchemaList.txt";
			order2+=s;
			order2+=temp1;
			order2+=s;
			order2+=temp2;
			system(order2.c_str());
			string path="cse444_DataList\\";
			string temp3="\\SchemaList.txt";
			path+=s;
			path+=temp3;
			ifstream schemain(path.c_str());
			string schema;
			while(getline(schemain,schema))
			{
				int dotpos=schema.find(".",0);
				schema.erase(dotpos);
				solve(s,schema);
			}
		}
	return 0;
}
