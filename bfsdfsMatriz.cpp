#include <iostream>
using namespace std;

typedef char TipoItem;

class No
{
  public:
  TipoItem valor;
  No* proximo;
};

class filadinamica{ 
    private:
    No* primeiro; //front
    No* ultimo; //rear

    public:
    filadinamica(); // Constructor
    ~filadinamica(); // Destrutor  
    bool estavazio(); //isEmpty
    bool estacheio(); //isFull
    void inserir(TipoItem item); //enqueue //push
    TipoItem remover(); //dequeue //pop
    void imprimir(); //print
  
};

    filadinamica::filadinamica() // Constructor
    {
        primeiro = NULL;
        ultimo = NULL;
    }

    filadinamica::~filadinamica() // Destrutor
    {
        No* temp;
        while (primeiro != NULL){
            temp = primeiro;
            primeiro = primeiro->proximo;
            delete temp;
        }
        ultimo = NULL;
    }

    bool filadinamica::estavazio() //isEmpty
    {
        return (primeiro == NULL);
    }

    bool filadinamica::estacheio() //isFull
    {
        No* temp;
        try{
            temp = new No;
            delete temp;
            return false;
        } catch(bad_alloc exception){
            return true;
        }
    }

    void filadinamica::inserir(TipoItem item) //enqueue //push
    {
        if (estacheio()){
            cout << "A Fila esta cheia!\n";
            cout << "Nao foi possivel inserir este elemento!\n";
        } else{
            No* NoNovo = new No;
            NoNovo->valor = item;
            NoNovo->proximo = NULL;
            if (primeiro == NULL){
                primeiro = NoNovo;
            } else{
                ultimo->proximo = NoNovo;
            }
            ultimo = NoNovo;
        }
    }

    TipoItem filadinamica::remover() //dequeue //pop
    {
        if (estavazio()){
            cout << "A fila esta vazia!\n";
            cout << "Nao tem elemento a ser removido!\n";
            return 0;
        } else{
            No* temp = primeiro;
            TipoItem item = primeiro->valor;
            primeiro = primeiro->proximo;
            if (primeiro == NULL){
                ultimo = NULL;
            }
            delete temp;
            return item;
        }
    }

    void filadinamica::imprimir() //print
    {
        No* temp = primeiro;
        cout << "Fila= [ ";
        while (temp != NULL){
            cout << temp->valor << " ";
            temp = temp->proximo;
        }
        cout << "]\n";
    }


class pilhadinamica{
    private:
    No* NoTopo;

    public:
    pilhadinamica(); //construtor //dynamic stack
    ~pilhadinamica(); //destrutor
    bool estavazio(); //isempty
    bool estacheio(); //tem memória //isfull
    void inserir(TipoItem item); //push
    TipoItem remover(); //pop
    void imprimir(); //print

    
};

    pilhadinamica::pilhadinamica() //construtor //dynamic stack
    {
        NoTopo = NULL;
    }

    pilhadinamica::~pilhadinamica() //destrutor
    {
        No* NoTemp;
        while (NoTopo != NULL){
            NoTemp = NoTopo;
            NoTopo = NoTopo->proximo;
            delete NoTemp;
        }
    }

    bool pilhadinamica::estavazio() //isempty
    {
        return (NoTopo == NULL);
    }

    bool pilhadinamica::estacheio() //tem memória //isfull
    {
        No* NoNovo;
        try{
            NoNovo = new No;
            delete NoNovo;
            return false;
        } catch(bad_alloc exception){
            return true;
        }
    }

    void pilhadinamica::inserir(TipoItem item) //push
    {
        if (estacheio()){
            cout << "A Pilha esta cheia!\n";
            cout << "Nao foi possivel inserir este elemento!\n";
        } else{
            No* NoNovo = new No;
            NoNovo->valor = item;
            NoNovo->proximo = NoTopo;
            NoTopo = NoNovo;
        }
    }

    TipoItem pilhadinamica::remover() //pop
    {
        if (estavazio()){
            cout << "A Pilha esta vazia!\n";
            cout << "Nao foi possivel remover nenhum elemento!\n";
            return 0;
        } else{
            No* NoTemp;
            NoTemp = NoTopo;
            TipoItem item = NoTopo->valor;
            NoTopo = NoTopo->proximo;
            delete NoTemp;
            return item;
        }
    }

    void pilhadinamica::imprimir() //print
    {
        No* NoTemp = NoTopo;
        cout << "Pilha: [ ";
        while (NoTemp != NULL){
            cout << NoTemp->valor << " ";
            NoTemp = NoTemp->proximo;
        }
        cout << "]\n";
    }


class Grafo{
    private:
    int arestanula;
    int maxvertices;
    int numvertices;
    TipoItem* vertices;
    int** matrizadjacencias;
    bool* marcador; //novo

    public:
    Grafo(int max, int valorarestanula);
    ~Grafo();
    int obterindice(TipoItem item);
    bool estacheio();
    void inserevertice(TipoItem item);
    void inserearesta(TipoItem Nosaida, TipoItem Noentrada, int peso);
    int obterpeso(TipoItem Nosaida, TipoItem Noentrada);
    int obtergrau(TipoItem item);
    void imprimirmatriz();
    void imprimirvertices();

    //novos:
    void limpamarcador();
    void bfs(TipoItem origem, TipoItem destino);
    void dfs(TipoItem origem, TipoItem destino);
};


     Grafo::Grafo(int max, int valorarestanula) //construtor
    {
        numvertices = 0;
        maxvertices = max;
        arestanula = valorarestanula;

        marcador = new bool[maxvertices]; //novo

        vertices = new TipoItem[maxvertices];

        matrizadjacencias = new int*[maxvertices];
        for (int i=0 ; i<maxvertices ; i++){
            matrizadjacencias[i] = new int[maxvertices];
        }

        for (int i=0 ; i<maxvertices ; i++){
            for (int j=0 ; j<maxvertices ; j++){
                matrizadjacencias[i][j] = arestanula;
            }
        }
    }

    Grafo::~Grafo() //destrutor
    {
        delete [] vertices;
        for (int i=0 ; i<maxvertices ; i++){
            delete [] matrizadjacencias[i];
        }
        delete [] matrizadjacencias;
    }

    int Grafo::obterindice(TipoItem item)
    {
        int indice = 0;
        while (item != vertices[indice]){
            indice++;
        }
        return indice;
    }

    bool Grafo::estacheio()
    {
        return (numvertices == maxvertices);
    }

    void Grafo::inserevertice(TipoItem item)
    {
        if (estacheio()){
            cout << "O numero maximo de vertices foi alcancado!\n";
        } else{
            vertices[numvertices] = item;
            numvertices++;
        }
    }

    void Grafo::inserearesta(TipoItem Nosaida, TipoItem Noentrada, int peso)
    {
        int linha = obterindice(Nosaida);
        int coluna = obterindice(Noentrada);

        matrizadjacencias[linha][coluna] = peso;

        //matrizadjacencias[coluna][linha] = peso; //Remover se for direcionado
    }

    int Grafo::obterpeso(TipoItem Nosaida, TipoItem Noentrada)
    {
        int linha = obterindice(Nosaida);
        int coluna = obterindice(Noentrada);
        return (matrizadjacencias[linha][coluna]);        
    }

    int Grafo::obtergrau(TipoItem item)
    {
        int linha = obterindice(item);
        int grau = 0;
        for (int i=0 ; i<maxvertices ; i++){
            if (matrizadjacencias[linha][i] != arestanula){
                grau++;
            }
        }
        return grau;
    }

    void Grafo::imprimirmatriz()
    {
        cout << "Matriz de adjacencias:\n";
        for (int i=0 ; i<maxvertices ; i++){
            for (int j=0 ; j<maxvertices ; j++){
                cout << matrizadjacencias[i][j] << " ";
            }
            cout << endl;
        }
    }

    void Grafo::imprimirvertices()
    {
        cout << "Lista de Vertices:\n";
        for (int i=0 ; i<numvertices ; i++){
            cout << i << ": " << vertices[i] << endl;
        }
    }



    //novos:
    void Grafo::limpamarcador()
    {
        for (int i = 0; i<maxvertices ; i++){
        marcador[i] = false;    
        }   
    }

    void Grafo::bfs(TipoItem origem, TipoItem destino)
    {
        filadinamica filavertices;
        bool encontrado = false;
        limpamarcador();
        filavertices.inserir(origem);
        do{
            TipoItem verticeatual = filavertices.remover();
            if (verticeatual == destino){
                cout << "Visitando: " << verticeatual << endl;
                cout << "Caminho encontrado!\n";
                encontrado = true;
            } else{
                int indice = obterindice(verticeatual);
                cout << "Visitando: " << verticeatual << endl;
                for (int i=0 ; i<maxvertices ; i++){
                    if (matrizadjacencias[indice][i] != arestanula){
                        if (!marcador[i]){
                            cout << "Enfileirando: " << vertices[i] << endl;
                            filavertices.inserir(vertices[i]);
                            marcador[i] = true;
                        }
                    }  
                }
            }
        } while (!filavertices.estavazio() && !encontrado);
        if (!encontrado){
            cout << "Caminho nao encontrado!\n";
        }
    }

    


    void Grafo::dfs(TipoItem origem, TipoItem destino)
    {
        pilhadinamica pilhavertices;
        bool encontrado = false;
        limpamarcador();
        pilhavertices.inserir(origem);
        do{
            TipoItem verticeatual = pilhavertices.remover();
            if (verticeatual == destino){
                cout << "Visitando: " << verticeatual << endl;
                cout << "Caminho encontrado!\n";
                encontrado = true;
            } else{
                int indice = obterindice(verticeatual);
                cout << "Visitando: " << verticeatual << endl;
                for (int i=0 ; i<maxvertices ; i++){
                    if (matrizadjacencias[indice][i] != arestanula){
                        if (!marcador[i]){
                            cout << "Empilhando: " << vertices[i] << endl;
                            pilhavertices.inserir(vertices[i]);
                            marcador[i] = true;
                        }
                    }  
                }
            }
        } while (!pilhavertices.estavazio() && !encontrado);
        if (!encontrado){
            cout << "Caminho nao encontrado!\n";
        }
    }
    

using namespace std;

int main(){
    int max, valorarestanula;
    cout << "Digite a quantidade maxima de vertices:\n";
    cin >> max;
    cout << "Digite o valor para representar a ausencia de aresta:\n";
    cin >> valorarestanula;
    Grafo grafo1(max, valorarestanula);
    TipoItem item1, item2;
    int opcao, valor, peso;

    do{
        cout << "Digite 0 para parar o algoritmo!\n";
        cout << "Digite 1 para inserir um vertice!\n";
        cout << "Digite 2 para inserir uma aresta!\n";
        cout << "Digite 3 para imprimir o grau de um vertice!\n";
        cout << "Digite 4 para imprimir o peso de uma aresta!\n";
        cout << "Digite 5 para imprimir a matriz de adjacencias!\n";
        cout << "Digite 6 para imprimir a lista de vertices!\n";
        cout << "Digite 7 para realizar uma busca em largura!\n";
        cout << "Digite 8 para realizar uma busca em profundidade!\n";
        cin >> opcao;

        if (opcao == 1){
            cout << "Digite o elemento do vertice que sera inserido:\n";
            cin >> item1;
            grafo1.inserevertice(item1);
        } else if (opcao == 2){
            cout << "Digite o vertice de saida:\n";
            cin >> item1;
            cout << "Digite o vertice de entrada:\n";
            cin >> item2;
            cout << "Digite o peso desta aresta:\n";
            cin >> peso;
            grafo1.inserearesta(item1, item2, peso);
        } else if (opcao == 3){
            cout << "Digite o vertice que sera calculado o grau:\n";
            cin >> item1;
            valor = grafo1.obtergrau(item1);
            cout << "O grau desse vertice e: " << valor << endl;
        } else if (opcao == 4){
            cout << "Digite o vertice de saida:\n";
            cin >> item1;
            cout << "Digite o vertice de entrada:\n";
            cin >> item2;
            valor = grafo1.obterpeso(item1, item2);
            cout << "O peso dessa aresta e: " << valor << endl;
        } else if (opcao == 5){
            grafo1.imprimirmatriz();
        } else if (opcao == 6){
            grafo1.imprimirvertices();
        } else if (opcao == 7){
            cout << "Digite o vertice de origem:\n";
            cin >> item1;
            cout << "Digite o vertice de destino:\n";
            cin >> item2;
            grafo1.bfs(item1, item2);           
        } else if (opcao == 8){
            cout << "Digite o vertice de origem:\n";
            cin >> item1;
            cout << "Digite o vertice de destino:\n";
            cin >> item2;
            grafo1.dfs(item1, item2);            
        }
    } while (opcao != 0);


    return 0;
}