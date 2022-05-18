/*  YASWANTH
 *  JAGILANKA
 *  YJAGILAN
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>

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
    vector<float> v2;
    v2 = std::vector<float>(mean_values.begin(),mean_values.begin() + 15);
    return v2;

}

void isort(vector<vector<int> > class_data_A,vector<vector<int> > class_data_B, vector<vector<int> > populationdata, int n, MPI_Comm comm) {
    
    int size = -1;
    int rank = -1;
    int i,j;

    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    int loc_n = (n / size);
    int loc_n1 = n - ((size -1) * loc_n);
    // Code to be executed inside the processor of Rank 0
    if(rank==0){
        // vector<vector<int> > populationdata;

        // vector<vector<int> >::const_iterator first = populationdata.begin() ;
        // vector<vector<int> >::const_iterator last = populationdata.begin() + loc_n1 -1;
        // vector<vector<int> > newVec(first, last);
        // cout<<"slicing done";

        vector<vector<int> > new_population;
        for(int i=0; i <loc_n1; i++){
            new_population.push_back(populationdata[i]);
        }

        vector<float> out_a;
        vector<float> out_b;
        vector<float> recv_a(15,0);
        vector<float> recv_b(15,0);

        out_a = main_runner(class_data_B,new_population);
        out_b = main_runner(class_data_A,new_population);

        for(i=1;i<size;i++){
            MPI_Recv(&recv_a[0], 15, MPI_FLOAT, i, i, comm,MPI_STATUS_IGNORE);
            MPI_Recv(&recv_b[0], 15, MPI_FLOAT, i, i*i+i+1, comm,MPI_STATUS_IGNORE);
            out_a.insert(out_a.end(), recv_a.begin(), recv_a.end());
            out_b.insert(out_b.end(), recv_b.begin(), recv_b.end());
        }
        
        // Send the count vector to all the other size-1 processors
        for(i=1;i<size;i++){
            MPI_Send(&out_a[0], 15*size, MPI_FLOAT, i, i*i*3+2*i, comm);
            MPI_Send(&out_b[0], 15*size, MPI_FLOAT, i, i*i*3+9*i, comm);
        }


    }

    // Code to be executed inside the processor other than Rank 0
    else{  
        int start = loc_n1+(rank-1)*loc_n;
        vector<vector<int> > new_population;
        for(int i=start; i <start+loc_n; i++){
            new_population.push_back(populationdata[i]);
        }

        vector<float> out_a;
        vector<float> out_b;
        vector<float> final_a(15*size,0);
        vector<float> final_b(15*size,0);
        

        out_a = main_runner(class_data_B,new_population);
        out_b = main_runner(class_data_A,new_population);

        //  Send the data in vector1 with count to Rank 0 for final aggregation
        MPI_Send(&out_a[0],15,MPI_FLOAT,0,rank,comm);
        MPI_Send(&out_b[0],15,MPI_FLOAT,0,rank*rank+rank+1,comm);

        // Receive the final count to be populated in each of the Ranks
        MPI_Recv(&final_a[0], 15*size, MPI_FLOAT, 0, rank*rank*3+2*rank, comm,MPI_STATUS_IGNORE);
        MPI_Recv(&final_b[0], 15*size, MPI_FLOAT, 0, rank*rank*3+9*rank, comm,MPI_STATUS_IGNORE);


    }

} // isort

#endif // A1_HPP
