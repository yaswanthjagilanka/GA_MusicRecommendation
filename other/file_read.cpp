#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;
 
int main()
{
	string fname;
    fname="data.csv";
	// cout<<"Enter the file name: ";
	// cin>>fname;
 
	vector<vector<string> > content;
	vector<string> row;
	string line, word;
    vector<vector<int> > data;
 
	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, '\t'))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";
    
    cout<<"file read properly\n";
    cout<<content.size()<<"\n";
    cout<<"hello\n";
    cout<<content[0].size()<<"\n";
    cout<<"testing vector size\n";
    cout<<content[1][5].size()<<"\n";

    // for(int i=0;i<3;i++)
	// {
	// 	for(int j=0;j<content[i].size();j++)
	// 	{
	// 		cout<<content[i][j]<<" \n";
	// 	}
	// 	cout<<"\n";
	// }
	// for(int i=0;i<content.size();i++)
	// {
		for(int j=0;j<content[1].size();j++)
		{
			cout<<content[1][j]<<" ";
            cout<<"first column ends here";
		}
	// 	cout<<"\n";
	// }
 
	return 0;
}