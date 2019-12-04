#include <bits/stdc++.h>
#include <omp.h>
#include <mpi.h>

using namespace std;

int N;

static int cx[8] = {1,1,2,2,-1,-1,-2,-2}; 
static int cy[8] = {2,-2,1,-1,2,-2,1,-1}; 

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


void movimentos(int x, int y, bool flag_master){
    vector<vector<int> > mapa(N, vector<int>(N, -1));
    vector<int> inicio(N*N, 0);
    vector<pair<int, int> > posicao(N*N, pair<int,int>());
    int movimento = 0;
    int k = 0;
    int x_atual = 0;
    int y_atual = 0;
    int rank = x + 1 ;
	int tag = 1;
    mapa[x][y] = movimento;
    posicao[movimento].first = x;
    posicao[movimento].second = y;
    
    while(1){
        int flag = true;
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

            y = posicao[movimento].second;
            x = posicao[movimento].first;
            
        }

        if(movimento == N*N -1){
            
            vector<int> resultado_1(N*N, 0);
            // vector<int> resultado_2(N * N, 0);


            for (int i = 0; i < N*N; ++i){
                resultado_1[i] = posicao[i].first * N + posicao[i].second;
                // resultado_2[i] = posicao[i].first * (N - 1) + ( N - 1 - posicao[i].second + posicao[i].first);
            }
            // for(int i = 0; i < N; i++){
                MPI_Send(&resultado_1[0], N * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            // }
            // cout << "enviado de " << rank << " ..." <<endl;

            // if (flag_master){
            //     MPI_Send(&resultado_2[0], N * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
            // }
        }

    }

    vector<vector<int> > resultado(N, vector<int>(N, -999));

    MPI_Send(&resultado, N*N, MPI_INT, 0, 0, MPI_COMM_WORLD);

}
  
int main(int argc, char *argv[]){ 
    srand(time(NULL)); 

    if(argc != 2){
        cout << "erro" << endl;
        exit(0);
    }

    N = atoi(argv[1]);
    int total = 0, rank, size;

    MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        vector<int> recebe_valor(N*N, -1);
        MPI_Status status;
    	ofstream saida_1;
        int fim_solucoes = 0;
    	saida_1.open("ariel-gustavo-ver.txt");

        while (fim_solucoes < size - 1) {
            
            MPI_Recv(&recebe_valor[0], N*N, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            // cout << "recebi?? ..." << endl;
            if (recebe_valor[0] == -999) {
                fim_solucoes++;
            	cout << "terminado processo: "<< fim_solucoes <<" ..." <<endl;

            }else{
                vector<vector<int> > auxiliar(N, vector<int>(N, -1));
                vector<vector<int> > resultado(N, vector<int>(N, -1));
		        ofstream saida_2;
		        saida_2.open("ariel-gustavo-count.txt");
		        
                for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        auxiliar[i][j] = recebe_valor[i*N+j];
                    }
                }

                for(int i = 0; i < N*N; i++){
                    saida_1 << recebe_valor[i] << " ";
                }
                saida_1 << endl;
                total++;

                for(int i=0; i< N; i++){       
                    for (int j=0; j< N; j++){
                        resultado[j][N-i-1] = auxiliar[i][j];
                    }
                }

                for(int i=0; i<N; i++){
                    for(int j=0; j<N; j++){
                        saida_1 << resultado[i][j] << " ";
                    }
                    saida_1 << endl;
                }
                total++;



                for(int i=0; i<N; i++){       
                    for (int j=0; j<N; j++){
                        resultado[i][N-j-1] = auxiliar[i][j];
                    }
                }

                for(int i=0; i<N; i++){
                    for(int j=0; j<N; j++){
                        saida_1 << resultado[i][j] << " ";
                    }
                    saida_1 << endl;
                }
                total++;


                for(int i=0; i<N; i++){       
                    for (int j=0; j<N; j++){
                        resultado[N-i-1][N-j-1] = auxiliar[i][j];
                    }
                }

                for(int i=0; i<N; i++){
                    for(int j=0; j<N; j++){
                        saida_1 << resultado[i][j] << " ";
                    }
                    saida_1 << endl;
                }
                total++;
    
                for(int i=0; i<N; i++){       
                    for (int j=0; j<N; j++){
                        resultado[N-i-1][j] = auxiliar[i][j];
                    }
                }

                for(int i=0; i<N; i++){
                    for(int j=0; j<N; j++){
                        saida_1 << resultado[i][j] << " ";
                    }
                    saida_1 << endl;
                }
                total++;
  
                for(int i=0; i<N; i++){       
                    for (int j=0; j<N; j++){
                        resultado[N-j-1][i] = auxiliar[i][j];
                    }
                }

                for(int i=0; i<N; i++){
                    for(int j=0; j<N; j++){
                        saida_1 << resultado[i][j] << " ";
                    }
                    saida_1 << endl;
                }
                total++;
                
                saida_2 << total;

            }
        }

    } else {

        #pragma omp parallel for
        for (int j = 0; j < N / 2; j++){
            movimentos(rank - 1, j, true);
        }

        if(N % 2 != 0){
        
            #pragma omp parallel
            {
                movimentos(rank - 1, N/2 + 1, false);
            }
        }

    }

    MPI_Finalize();

    return 0; 
} 