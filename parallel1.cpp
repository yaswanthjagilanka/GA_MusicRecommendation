#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
 
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream;

using namespace std;
using namespace std::chrono;

#include <mpi.h>

#include "parallel1.hpp"

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


    return data;
}

int main(int argc, char* argv[]) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);



    if (argc < 2) {
        if (rank == 0) std::cout << "usage: " << argv[0] << " n" << std::endl;
        return MPI_Finalize();
    }

    // int n = 5382;
    int n = std::atoll(argv[1]);

    if (n <= size) {
        if (rank == 0) std::cout << "hey, n is too small even for debugging!" << std::endl;
        return MPI_Finalize();
    }

    

    int loc_n = (n / size);
    if (rank == 0) loc_n = n - ((size -1) * loc_n);



    // Read Class A data
    vector<vector<int> > class_data_A;
    string filename("/user/yjagilan/genetic_algo/drive_data/classA137data.txt");
    class_data_A = readfile(filename);

    // Read Class B data
    vector<vector<int> > class_data_B;
    string filename1("/user/yjagilan/genetic_algo/drive_data/classB0data.txt");
    class_data_B = readfile(filename1);

    // // Read population data
    vector<vector<int> > populationdata;
    string filename2("/user/yjagilan/genetic_algo/drive_data/populationdata.txt");
    populationdata = readfile(filename2);
    populationdata.resize(n);


    MPI_Barrier(MPI_COMM_WORLD);
    auto t0 = MPI_Wtime();

    isort(class_data_A,class_data_B,populationdata,n, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    auto t1 = MPI_Wtime();

    if (rank == 0) std::cout << (t1 - t0) << std::endl;

    return MPI_Finalize();
} // main
