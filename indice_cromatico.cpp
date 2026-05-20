#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 101

// ATEN��O: O c�lculo da complexidade deve incluir todo o cc�digo, inclusive a leitura do arquivo.


char nome_arquivo[50], aux[MAX];								// proibido alterar esta linha
int opcao, tamanho, i, j, n, m, digrafo, matriz_adj[MAX][MAX];  // proibido alterar esta linha
// Declare vari�veis globais a partir daqui.
int cor_aresta[MAX][MAX]; // matriz para armazenar a cor de cada aresta, 0 significa aresta nao colorida



void executafuncao (){   										// � dentro desta fun��o que o aluno dever� escrever seu c�digo
    int cor; // cor para a aresta atual
    int indice = 0; // indice = maior cor usada ate o momento
    int proibidas[MAX]; // vetor para armazenar as cores proibidas para a aresta atual

    /*inicializacao: define todas as arestas com cor 0 (não coloridas)*/

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cor_aresta[i][j] = 0;
        }
    }

    /*coloracao gulosa das arestas:
    
    percorre cara par de vertices (i,j) com i < j pra evitar passar pela mesma aresta duas vezes
    
    */

    for (int i = 1; i <= n; i++) { // O(n^3)
        for (int j = i + 1; j <= n; j++) { //O(n²)
            if (matriz_adj[i][j] != 0) {
                for (int c = 0; c < MAX; c++) {
                    proibidas[c] = 0;
                }

                /* marca como proibidas as cores usadas por arestas incidentes a i (exceto a propria aresta (i,j))*/
                for (int k = 1; k <= n; k++) { // O(n)
                    if (cor_aresta[i][k] != 0) {
                        proibidas[cor_aresta[i][k]] = 1;
                    }
                }

                /* marca como proibidas as cores usadas por arestas incidentes a j (exceto a propria aresta (i,j))*/
                for (int k = 1; k <= n; k++) { // O(n)
                    if (cor_aresta[j][k] != 0) {
                        proibidas[cor_aresta[j][k]] = 1;
                    }
                }

                cor = 1;
                while (proibidas[cor] == 1) {
                    cor++;
                }
                cor_aresta[i][j] = cor;
                cor_aresta[j][i] = cor;

                if (cor > indice) {
                    indice = cor;
                }
            }
        }
    }

    /*exibicao dos resultados*/

    printf("\n============================= INDICE CROMATICO ==============================\n");
    //caso especial: se o grafo nao tiver arestas, o indice cromatico é 0
    if (m == 0) {
        printf("\nO grafo nao possui arestas, logo o indice cromatico é 0.\n");
        return;
    }
    
    printf("\nO indice cromatico do grafo é: %d\n", indice);
    printf("\nA coloracao das arestas é:\n");
    for (int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if (matriz_adj[i][j] != 0) {
                printf("Aresta (%d, %d): Cor %d\n", i, j, cor_aresta[i][j]);
            }
        }
    }
    printf("\n=============================================================================\n");
}




int main() {
	opcao = 1;

    while(opcao != 0){
        inicio:
        tamanho = 0;
        m = 0;
        digrafo = 0;
        system("cls"); 
        fflush(stdin); 
        printf("Digite o nome do arquivo (sem o .txt): ");
        gets(nome_arquivo);
        FILE *arquivo; 
        strcat(nome_arquivo,".txt"); 
            
        if((arquivo = fopen(nome_arquivo,"r")) != NULL){
        	while(fgets(aux, MAX, arquivo)) { 
                   char *elemento; 
                   elemento = strtok(aux, " ");
                    while (elemento != NULL){
                        elemento = strtok(NULL, " "); 
                    }
                    tamanho = tamanho + 1; 
                }
                fclose(arquivo);
                
                printf ("\n --------------------------- MATRIZ DE ADJAC�NCIA ---------------------------\n");
                
                if((arquivo = fopen(nome_arquivo,"r")) != NULL){
                    printf("\n");
                    for(int i = 1; i <= tamanho; i++){
                        for(int j = 1; j <= tamanho; j++){
                            fscanf(arquivo, "%d", &matriz_adj[i][j]);
							printf("%3d ", matriz_adj[i][j]); 
                        }
                        printf("\n");
                    }
                }
                fclose(arquivo);
				n = tamanho;
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (matriz_adj[i][j] != matriz_adj[j][i]) {
							digrafo = 1;   // � d�grafo
						}
					}
				}
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (digrafo == 1 && matriz_adj[i][j] != 0) {
							m = m + 1;
						} 
						if (digrafo == 0 && matriz_adj[i][j] != 0 && i <= j) {
							m = m + 1;
						}
					}
				}
				
	          printf ("\nN = %d e M = %d \n \n",n,m);     
            } else {
                printf("\nErro ao abrir o arquivo/Erro ao localizar o arquivo\n\n");
                
            }
        	  
		executafuncao ();       
        printf("\nDigite 0 para sair ou qualquer outra coisa para continuar: ");
		scanf("%d", &opcao);
        
    }
    return 0;
}

