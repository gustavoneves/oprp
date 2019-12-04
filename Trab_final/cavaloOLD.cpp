//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <iomanip>   
#include <omp.h>
#include <mpi.h>

using namespace std;

int N = 6;

static int cx[8] = {1,1,2,2,-1,-1,-2,-2}; 
static int cy[8] = {2,-2,1,-1,2,-2,1,-1}; 


MPI_Status status0;
MPI_Request request0;

MPI_Status statusA;
MPI_Request requestA;

MPI_Status statusB;
MPI_Request requestB;

MPI_Status statusC;
MPI_Request requestC;

MPI_Status statusD;
MPI_Request requestD;

MPI_Status statusE;
MPI_Request requestE;

bool verifica(vector<vector<int> > matriz, int x, int y){
    if((x >= 0 && y >= 0) && (x < N && y < N)){
        if(matriz[x][y] == -1){
            return true;
        }
    }

    return false;
}

void printVetor(vector<pair<int,int> > &movimentos, int tamanho, int rank){


}

void printMapa(vector<vector<int> > &mapa){
    for(int i = 0; i < mapa.size(); i++){
        for(int j = 0; j < mapa[i].size(); j++){
            cout << setw(3) << mapa[i][j];
        }

        cout << endl;

    }
}


void movimentos(int x, int y){
    vector<vector<int> > mapa(N, vector<int>(N, -1));
    vector<int> inicio(N*N, 0);
    vector<pair<int, int> > posicao(N*N, pair<int,int>());
    int movimento = 0;
    int k = 0;
    mapa[x][y] = movimento;
    posicao[movimento].first = x;
    posicao[movimento].second = y;
    int x_atual = 0;
    int y_atual = 0;
    int rank = x + 1 ;
	int tag = 1;
    
    while(1){
        int flag = true;
        // cout << endl;
        int i;
        
        for(i = inicio[movimento]; i < 8; i++){
            int x_aux = x + cx[i];
            int y_aux = y + cy[i];

            if(verifica(mapa, x_aux, y_aux)){
                x_atual = x_aux;
                y_atual = y_aux;
                mapa[x_atual][y_atual] = (++movimento);
                flag = false;
                x = x_atual;
                y = y_atual;
                inicio[movimento - 1] = i+1;
                posicao[movimento].first = x;
                posicao[movimento].second = y;

                break;
            }
        }

        if(flag){
            mapa[x][y] = -1;
            posicao[movimento].first = posicao[movimento].second = 0;
            inicio[movimento] = 0;

            movimento--;

            if(movimento < 0){
                return;
            }

            x = posicao[movimento].first;
            y = posicao[movimento].second;
            
        }

        if(movimento == N*N -1){
            
            // cout << "MORTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;        

            // printVetor(posicao, mapa.size(), rank);
		    vector<int> resultado(N*N, 0);
   
            vector<int> resultadoA(N*N, 0);
            vector<int> resultadoB(N*N, 0);
            vector<int> resultadoC(N*N, 0);
            vector<int> resultadoD(N*N, 0);
            vector<int> resultadoE(N*N, 0);

		    // int tamanho = N;
		    for (int i = 0; i < N*N; ++i){
		        // cout <<  << " ";
		        resultado[i] = posicao[i].first * N + posicao[i].second;
		    }
		    // int a = 1;
		    //MPI_Send(&resultado[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Isend(&resultado[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &request0);
            // cout << "enviado de " << rank << " ..." <<endl;


            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    resultadoA[j * N + (N-i-1)] = resultado[i * N + j];
                }
            }
            //MPI_Send(&resultadoA[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Isend(&resultadoA[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &requestA);

            //
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    resultadoB[i * N + (N-j-1)] = resultado[i * N + j];
                }
            }
            //MPI_Send(&resultadoB[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Isend(&resultadoB[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &requestB);

            //
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                     resultadoC[(N-i-1) * N + (N-j-1)] = resultado[i * N + j];
                }
            }
            //MPI_Send(&resultadoC[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Isend(&resultadoC[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &requestC);

            //
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    resultadoD[(N-i-1) * N + j] = resultado[i * N + j];
                }
            }
            //MPI_Send(&resultadoD[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Isend(&resultadoD[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &requestD);

            //
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    resultadoE[(N-j-1) * N + i] = resultado[i * N + j];
                }
            }
            //MPI_Send(&resultadoE[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Isend(&resultadoE[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &requestE);


            MPI_Wait(&request0,&status0);
            MPI_Wait(&requestA,&statusA);
            MPI_Wait(&requestB,&statusB);
            MPI_Wait(&requestC,&statusC);
            MPI_Wait(&requestD,&statusD);
            MPI_Wait(&requestE,&statusE);
        }

    }

    vector<int> resultado(N*N, -999);
    // resultado[N*N-1] = -999;
	// int a = 1;
    MPI_Send(&resultado[0], N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
  
int main(int argc, char *argv[]){ 
    //srand(time(NULL)); 

    if(argc != 2){
        cout << "erro" << endl;
        exit(0);
    }

    //N = atoi(argv[1]);
    int total = 0, rank, size;

    MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        //N = atoi(argv[1]);
        vector<int> recebe_valor(N*N, -1);
        int offset1;
        int offset2;
        MPI_Status status;
    	ofstream saida_1;
        saida_1.open("ariel-gustavo-ver.txt");
        int fim_solucoes = 0;

        //ofstream saida_2;
	    //saida_2.open("ariel-gustavo-count.txt");
        while (fim_solucoes < size - 1) {
            
            //MPI_Recv(&recebe_valor[0], N*N, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            MPI_Irecv(&recebe_valor[0], N*N, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, )
            // cout << "recebi?? ..." << endl;
            if (recebe_valor[N*N-1] == -999) {
                fim_solucoes++;
            	cout << "terminado processo: "<< fim_solucoes <<" ..." <<endl;

            }else{
            
		        ofstream saida_2;
		        saida_2.open("ariel-gustavo-count.txt");
		        
                for(int i = 0; i < N*N; i++){
                    saida_1 << recebe_valor[i] << " ";
                }
                saida_1 << endl;
                total++;

		        
                saida_2 << total;
	            // cout << "recebido..." <<endl;

            }
        }
        //saida_1.close();
        //saida_2.close();


    } else {
        
        #pragma omp parallel for
        for(int j = 0; j < N; j++){
            movimentos(rank-1, j);
        }

    }

    MPI_Finalize();


    return 0; 
} 


// //
                // for(int i=0; i<N; i++){
                //     for(int j=0; j<N; j++){
                //         temp[j * N + (N-i-1)] = recebe_valor[i * N + j];
                //     }
                // }

                // for(int i = 0; i < N*N; i++){
                //     saida_1 << temp[i] << " ";
                // }
                // saida_1 << endl;
                // total++;

                // //
                // for(int i=0; i<N; i++){
                //     for(int j=0; j<N; j++){
                //         temp[i * N + (N-j-1)] = recebe_valor[i * N + j];
                //     }
                // }

                // for(int i = 0; i < N*N; i++){
                //     saida_1 << temp[i] << " ";
                // }
                // saida_1 << endl;
                // total++;

                // //
                // for(int i=0; i<N; i++){
                //     for(int j=0; j<N; j++){
                //         temp[(N-i-1) * N + (N-j-1)] = recebe_valor[i * N + j];
                //     }
                // }

                // for(int i = 0; i < N*N; i++){
                //     saida_1 << temp[i] << " ";
                // }
                // saida_1 << endl;
                // total++;

                // //
                // for(int i=0; i<N; i++){
                //     for(int j=0; j<N; j++){
                //         temp[(N-i-1) * N + j] = recebe_valor[i * N + j];
                //     }
                // }

                // for(int i = 0; i < N*N; i++){
                //     saida_1 << temp[i] << " ";
                // }
                // saida_1 << endl;
                // total++;

                // //
                // for(int i=0; i<N; i++){
                //     for(int j=0; j<N; j++){
                //         temp[(N-j-1) * N + i] = recebe_valor[i * N + j];
                //     }
                // }

                // for(int i = 0; i < N*N; i++){
                //     saida_1 << temp[i] << " ";
                // }
                // saida_1 << endl;
                // total++;

                //total++;