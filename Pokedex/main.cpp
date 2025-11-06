/*
AUGUSTO LEITE DEL CARLO CARNEIRO - 866 - GES
PETTRIUS VILAS BOAS DE PAIVA CARDOSO - 854 - GES
SOLANGE RIBEIRO DA FONSECA - 528 - GES
*/

#include <iostream>  
#include <string>  
  
using namespace std;

#define MAX_CIDADES 100 // Numero maximo de cidades que podem ser cadastradas

// --- INICIO DA ENTREGA 3: Estrutura e Arvore Binaria de Busca de Pokemons ---

// struct para armazenar os dados de cada Pokemon
struct Pokemon 
{
    int numero;       // Numero da Pokedex
    string nome;
    string tipo;
    int loc_x;        // Localizacao (coordenada x)
    int loc_y;        // Localizacao (coordenada y)
};

// Estrutura de no da Arvore Binaria de Busca
struct NoPokemon 
{
    Pokemon dados;           // Dados do Pokemon
    NoPokemon* esquerda;     // Ponteiro para subarvore esquerda
    NoPokemon* direita;      // Ponteiro para subarvore direita
};

// Raiz da arvore (inicialmente vazia)
NoPokemon* raizPokedex = nullptr;

// --- FIM DA ENTREGA 3 ---


// struct de cadastro de cidade no grafo
struct Cidade 
{
    int codigo;       // Codigo da cidade
    string nome;      // Nome da cidade
    bool temCentro;   // Indica se tem um Centro de Pokemon
    bool existe;      // Marca se a cidade esta cadastrada
};

Cidade cidades[MAX_CIDADES];  // Vetor para armazenar todas as cidades

// --- MODIFICACAO (Entrega 2): Matriz de Adjacencia ---
// Agora a matriz guarda o PESO (distancia) da estrada.
// 0 significa que nao ha estrada.
int matrizAdj[MAX_CIDADES][MAX_CIDADES];

int totalCidades = 0;   // Contador de quantas cidades foram cadastradas

// Funcao auxiliar que retorna o indice da cidade pelo codigo (sem alteracao)
int indicePorCodigo(int codigo)  
{
    for (int i = 0; i < totalCidades; i++) {
        if (cidades[i].existe && cidades[i].codigo == codigo)
            return i; // Retorna o indice encontrado
    }
    return -1; // Retorna -1 se nao encontrar
}

// Funcao para cadastrar uma nova cidade (sem alteracao)
void cadastrarCidade() 
{
    if (totalCidades >= MAX_CIDADES) {
        cout << "Limite maximo de cidades atingido!" << endl;
        return;
    }

    int codigo;
    string nome;
    char resp;

    cout << "Informe o codigo da cidade: ";
    cin >> codigo;

    if (indicePorCodigo(codigo) != -1) // Verifica se o codigo ja existe
	{
        cout << "Cidade com esse codigo ja existe!" << endl;
        return;
    }

    cin.ignore(); 
    cout << "Informe o nome da cidade: ";
    getline(cin, nome);

    cout << "Possui Centro Pokemon? (s/n): ";
    cin >> resp;

    // Preenche os dados da nova cidade
    cidades[totalCidades].codigo = codigo;
    cidades[totalCidades].nome = nome;
    cidades[totalCidades].temCentro = (resp == 's' || resp == 'S');
    cidades[totalCidades].existe = true;

    // Inicializa conexoes (sem estradas ainda, valor 0)
    for (int j = 0; j < MAX_CIDADES; j++) 
	{
      matrizAdj[totalCidades][j] = matrizAdj[j][totalCidades] = 0;	
	}
    cout << "Cidade cadastrada: [" << codigo << "] " << nome
         << (cidades[totalCidades].temCentro ? " (Centro Pokemon)" : "") << endl;

    totalCidades++; // Incrementa o total de cidades
}

// --- MODIFICACAO (Entrega 2): Cadastrar Estrada com Peso (Distancia) ---
void cadastrarEstrada() {
    if (totalCidades < 2) {
        cout << "E necessario ao menos duas cidades cadastradas." << endl;
        return;
    }

    int codA, codB, distancia; // Adicionada a variavel 'distancia'
    cout << "Informe o codigo da primeira cidade: ";
    cin >> codA;
    cout << "Informe o codigo da segunda cidade: ";
    cin >> codB;
    cout << "Informe a distancia da estrada: "; // Pede a nova informacao
    cin >> distancia;

    if (distancia <= 0) {
        cout << "Distancia invalida." << endl;
        return;
    }

    int a = indicePorCodigo(codA);
    int b = indicePorCodigo(codB);

    if (a == -1 || b == -1) // Verifica se as cidades existem
	{
        cout << "Uma das cidades nao existe!" << endl;
        return;
    }

    if (a == b) // Impede ligar uma cidade a ela mesma
	{
        cout << "Nao e possivel conectar uma cidade a ela mesma." << endl;
        return;
    }

    // Marca a distancia da estrada entre as cidades (grafo nao-direcionado)
    matrizAdj[a][b] = distancia;
    matrizAdj[b][a] = distancia;

    cout << "Estrada cadastrada entre [" << codA << "] " << cidades[a].nome
         << " <-> [" << codB << "] " << cidades[b].nome << " com distancia " << distancia << endl;
}

// Funcao auxiliar para o Dijkstra: encontra o vertice nao visitado com menor distancia
int encontrarMinDistancia(int dist[], bool visitado[]) {
    int min = 2147483647; // Representa "infinito"
    int min_indice = -1;

    for (int v = 0; v < totalCidades; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_indice = v;
        }
    }
    return min_indice;
}

// --- MODIFICACAO (Entrega 2): Busca com Algoritmo de Dijkstra ---
void buscarCentroPokemonMaisProximo() {
    if (totalCidades == 0) {
        cout << "Nenhuma cidade cadastrada." << endl;
        return;
    }

    int codInicio;
    cout << "Informe o codigo da cidade atual: ";
    cin >> codInicio;

    int start = indicePorCodigo(codInicio);
    if (start == -1) {
        cout << "Cidade nao encontrada." << endl;
        return;
    }
    
    if (cidades[start].temCentro) // Se a cidade atual ja tem centro pokemon
	{
        cout << "Voce ja esta em uma cidade com Centro Pokemon!" << endl;
        return;
    }

    // Vetores de controle para o Dijkstra
    int dist[MAX_CIDADES]; // Armazena a menor distancia de 'start' ate 'i'
    bool visitado[MAX_CIDADES]; // Marca se o vertice 'i' ja foi visitado
    int pai[MAX_CIDADES]; // Armazena o pai do vertice 'i' no caminho mais curto

    // Inicializa vetores de controle
    for (int i = 0; i < totalCidades; i++)  
	{
        dist[i] = 2147483647; // Distancia infinita
        visitado[i] = false;
        pai[i] = -1;
    }

    // A distancia da cidade inicial para ela mesma e 0
    dist[start] = 0;

    int destino = -1; // Guarda o indice do centro pokemon encontrado

    // Loop principal do Dijkstra
    for (int count = 0; count < totalCidades; count++) {
        // Pega o vertice com a menor distancia (que ainda nao foi visitado)
        int u = encontrarMinDistancia(dist, visitado);

        if (u == -1) break; // Se nao ha mais vertices alcancaveis

        visitado[u] = true; // Marca o vertice como visitado

        // Se o vertice 'u' tem um centro pokemon, encontramos o mais proximo!
        if (cidades[u].temCentro) {
            destino = u;
            break; // Para o loop principal, pois Dijkstra encontra o mais proximo primeiro
        }

        // Atualiza a distancia dos vizinhos de 'u'
        for (int v = 0; v < totalCidades; v++) {
            // Se 'v' e um vizinho (tem estrada), nao foi visitado,
            // e o novo caminho (passando por 'u') e mais curto
            if (matrizAdj[u][v] != 0 && !visitado[v] && 
                dist[u] + matrizAdj[u][v] < dist[v]) 
            {
                // Atualiza a distancia e o pai
                dist[v] = dist[u] + matrizAdj[u][v];
                pai[v] = u;
            }
        }
    }

    if (destino == -1) {
        cout << "Nenhum Centro Pokemon acessivel a partir desta cidade." << endl;
        return;
    }

    // Reconstroi o caminho percorrendo os pais (igual ao BFS)
    int caminho[MAX_CIDADES];
    int tam = 0;
    for (int v = destino; v != -1; v = pai[v]) {
        caminho[tam++] = v;
    }

    // Exibe a rota (do inicio ao destino)
    cout << "Rota ate o Centro Pokemon mais proximo (Distancia: " << dist[destino] << "):" << endl;
    for (int i = tam - 1; i >= 0; i--) {
        cout << "[" << cidades[caminho[i]].codigo << "] " << cidades[caminho[i]].nome;
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

// --- INICIO DA ENTREGA 3: Funcoes da Arvore Binaria de Busca ---

// Funcao auxiliar para criar um novo no da arvore
NoPokemon* criarNo(Pokemon pokemon) {
    NoPokemon* novoNo = new NoPokemon;
    novoNo->dados = pokemon;
    novoNo->esquerda = nullptr;
    novoNo->direita = nullptr;
    return novoNo;
}

// Funcao auxiliar recursiva para inserir um Pokemon na arvore
NoPokemon* inserirNaArvore(NoPokemon* raiz, Pokemon pokemon) {
    // Caso base: arvore vazia, cria novo no
    if (raiz == nullptr) {
        return criarNo(pokemon);
    }
    
    // Se o numero do pokemon e menor, insere na subarvore esquerda
    if (pokemon.numero < raiz->dados.numero) {
        raiz->esquerda = inserirNaArvore(raiz->esquerda, pokemon);
    }
    // Se o numero do pokemon e maior, insere na subarvore direita
    else if (pokemon.numero > raiz->dados.numero) {
        raiz->direita = inserirNaArvore(raiz->direita, pokemon);
    }
    // Se o numero ja existe, nao insere (evita duplicatas)
    else {
        cout << "Pokemon com numero " << pokemon.numero << " ja existe na Pokedex!" << endl;
    }
    
    return raiz;
}

// Funcao principal para cadastrar Pokemon (usa ABB)
void cadastrarPokemon() { 
    Pokemon novoPokemon;

    cout << "Informe o numero do Pokemon: ";
    cin >> novoPokemon.numero;
    
    cin.ignore(); // Limpa o buffer do teclado
    cout << "Informe o nome do Pokemon: ";
    getline(cin, novoPokemon.nome);
    
    cout << "Informe o tipo do Pokemon: ";
    getline(cin, novoPokemon.tipo);
    
    cout << "Informe a localizacao (X Y): ";
    cin >> novoPokemon.loc_x >> novoPokemon.loc_y;
    
    // Insere o pokemon na arvore binaria de busca
    raizPokedex = inserirNaArvore(raizPokedex, novoPokemon);
    
    cout << "Pokemon " << novoPokemon.nome << " cadastrado com sucesso!" << endl;
}

// Funcao auxiliar recursiva para buscar um Pokemon pelo numero
NoPokemon* buscarPokemon(NoPokemon* raiz, int numero) {
    // Caso base: arvore vazia ou Pokemon encontrado
    if (raiz == nullptr || raiz->dados.numero == numero) {
        return raiz;
    }
    
    // Se o numero procurado e menor, busca na subarvore esquerda
    if (numero < raiz->dados.numero) {
        return buscarPokemon(raiz->esquerda, numero);
    }
    
    // Senao, busca na subarvore direita
    return buscarPokemon(raiz->direita, numero);
}

// Funcao auxiliar para encontrar o menor valor (mais a esquerda)
NoPokemon* encontrarMinimo(NoPokemon* raiz) {
    while (raiz->esquerda != nullptr) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// Funcao auxiliar recursiva para remover um Pokemon da arvore
NoPokemon* removerDaArvore(NoPokemon* raiz, int numero) {
    if (raiz == nullptr) {
        return raiz;
    }
    
    // Procura o no a ser removido
    if (numero < raiz->dados.numero) {
        raiz->esquerda = removerDaArvore(raiz->esquerda, numero);
    }
    else if (numero > raiz->dados.numero) {
        raiz->direita = removerDaArvore(raiz->direita, numero);
    }
    // No encontrado
    else {
        // Caso 1: No sem filhos ou com apenas um filho
        if (raiz->esquerda == nullptr) {
            NoPokemon* temp = raiz->direita;
            delete raiz;
            return temp;
        }
        else if (raiz->direita == nullptr) {
            NoPokemon* temp = raiz->esquerda;
            delete raiz;
            return temp;
        }
        
        // Caso 2: No com dois filhos
        // Encontra o sucessor (menor valor na subarvore direita)
        NoPokemon* temp = encontrarMinimo(raiz->direita);
        
        // Copia os dados do sucessor para este no
        raiz->dados = temp->dados;
        
        // Remove o sucessor
        raiz->direita = removerDaArvore(raiz->direita, temp->dados.numero);
    }
    
    return raiz;
}

// --- Fim da Entrega 3 ---

// Stubs (funcionalidades em construcao)
void removerPokemon() { 
    if (raizPokedex == nullptr) {
        cout << "Nenhum Pokemon cadastrado na Pokedex." << endl;
        return;
    }
    
    int numero;
    cout << "Informe o numero do Pokemon a ser removido: ";
    cin >> numero;
    
    NoPokemon* pokemon = buscarPokemon(raizPokedex, numero);
    if (pokemon == nullptr) {
        cout << "Pokemon nao encontrado!" << endl;
        return;
    }
    
    cout << "Removendo Pokemon: " << pokemon->dados.nome << endl;
    raizPokedex = removerDaArvore(raizPokedex, numero);
    cout << "Pokemon removido com sucesso!" << endl;
}

void listarPokemonsNome() { cout << "Funcionalidade em construcao..." << endl; }
void listarPokemonsTipo() { cout << "Funcionalidade em construcao..." << endl; }
void contarPokemonsTipo() { cout << "Funcionalidade em construcao..." << endl; }
void encontrarPokemonsProximos() { cout << "Funcionalidade em construcao..." << endl; }


// Funcao principal para exibir menu e chamar as funcoes conforme a escolha
int main()
{
    int opcao;

    do 
    {
        cout << "\n...MENU POKEDEX...:" << endl;
        cout << "1. Cadastrar Cidade" << endl;
        cout << "2. Cadastrar Estrada" << endl;
        cout << "3. Buscar Centro Pokemon Mais Proximo" << endl;
        cout << "4. Cadastrar Pokemon" << endl;
        cout << "5. Remover Pokemon" << endl;
        cout << "6. Listar Pokemons Por Nome" << endl;
        cout << "7. Listar Pokemons Por Tipo" << endl;
        cout << "8. Contar Pokemons de Cada Tipo" << endl;
        cout << "9. Encontrar Pokemons Proximos" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch(opcao)
        {
            case 1: cadastrarCidade(); break;
            case 2: cadastrarEstrada(); break;
            case 3: buscarCentroPokemonMaisProximo(); break;
            case 4: cadastrarPokemon(); break;
            case 5: removerPokemon(); break;
            case 6: listarPokemonsNome(); break;
            case 7: listarPokemonsTipo(); break;
            case 8: contarPokemonsTipo(); break;
            case 9: encontrarPokemonsProximos(); break;
            case 0: cout << "Saindo do programa..." << endl; break;
            default: cout << "Opcao invalida. Tente novamente." << endl; break;
        }

    } while(opcao != 0);

    return 0;
}