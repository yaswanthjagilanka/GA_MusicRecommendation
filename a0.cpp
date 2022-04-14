#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
 
using namespace std;
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream;

using namespace std;
using namespace std::chrono;

double cosine_similarity(vector<int> A, vector<int> B, unsigned int Vector_Length)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
     for(unsigned int i = 0u; i < Vector_Length; ++i) {
        dot += A[i] * B[i] ;
        denom_a += A[i] * A[i] ;
        denom_b += B[i] * B[i] ;
    }
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
}


vector<float> main_runner(vector<vector<int> > class_data, vector<vector<int> > populationdata){

    vector<vector<float> > cosine_values(populationdata.size(), vector<float> (class_data.size(),0));

    //Cosine similarity for all samples class * population
    for(int i=0; i<populationdata.size();i++){
        for(int j=0; j<class_data.size();j++){
        double value = cosine_similarity(populationdata[i],class_data[j],1280);
        cosine_values[i][j]=value;
    }
    }

    vector<float> mean_values(populationdata.size());
    // Mean of the cosine values for all class data
    for(int i=0; i<cosine_values.size();i++){
        double mean = 0;
        for(int j =0; j<cosine_values[0].size();j++){
            mean+=cosine_values[i][j];
        }
        mean = mean / cosine_values[0].size();
        mean_values[i] = mean;
    }

    // sort based on the mean of cosine values
    sort(mean_values.begin(), mean_values.end());

    // return the first 100 values
    return mean_values;

}

vector<vector<int> > readfile(string filename){
    // string filename(filex);
    int number;

    vector<vector<int> > data;
    vector<int> temp;

    ifstream input_file(filename);
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


    return data;
}
 
int main()
{
    clock_t begin = clock();

    // Read Class A data
    vector<vector<int> > class_data_A;
    string filename("drive_data/classA137data.txt");
    class_data_A = readfile(filename);

    // Read Class B data
    vector<vector<int> > class_data_B;
    string filename1("drive_data/classB0data.txt");
    class_data_B = readfile(filename1);

    // // Read population data
    vector<vector<int> > populationdata;
    string filename2("drive_data/populationdata.txt");
    populationdata = readfile(filename2);

    // Compute 100 for class A
    vector<float> out_class_A;
    out_class_A = main_runner(class_data_A,populationdata);

    // Compute 100 for class B
    vector<float> out_class_B(populationdata.size(),0);
    out_class_B = main_runner(class_data_B,populationdata);
 
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"elapsed time"<<elapsed_secs;
 
    return 0;
}
