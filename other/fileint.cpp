#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream;

int main()
{
    string filename("drive_data/classB0data.txt");
    int number;

    vector<vector<int> > data;
    vector<int> temp;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    int count=0;
    while (input_file >> number) {
        if (count == 1280){
            data.push_back(temp);
            temp.clear();
            count=0;
        }
        temp.push_back(number);
        count+=1;
    }
    cout << endl;
    input_file.close();

    cout<<"hello size of vector "<< data.size()<<"\n";
    cout<<"find the size "<< data[0].size()<<"\n";


    return EXIT_SUCCESS;
}