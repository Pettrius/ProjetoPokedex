#include <iostream>  
#include <string>  
#include <list>
  
using namespace std;

#define MAX_CIDADES 100 // Numero maximo de cidades que podem ser cadastradas

void cadastrarCidade(string nome) {
    cout << "Funcionalidade em construcao..." << endl;
}

void cadastrarEstrada(string nome) {
    cout << "Funcionalidade em construcao..." << endl;
}

void buscarCentroPokemonMaisProximo(string nomeCidade) {
    cout << "Funcionalidade em construcao..." << endl;
}

void cadastrarPokemon(string nome, string tipo) {
    cout << "Funcionalidade em construcao..." << endl;
}

void removerPokemon(string nome) {
    cout << "Funcionalidade em construcao..." << endl;
}

void listarPokemonsNome(string nome) {
    cout << "Funcionalidade em construcao..." << endl;
}

void listarPokemonsTipo(string tipo) {
    cout << "Funcionalidade em construcao..." << endl;
}

int contarPokemonsTipo(int qtdTipo) {
    cout << "Funcionalidade em construcao..." << endl;
    return 0;
}

void encontrarPokemonsProximos(string localizacao) {
    cout << "Funcionalidade em construcao..." << endl;
}

struct Cidade // struct de cadastro de cidade no grafo
{
    int codigo;       // Codigo da cidade
    string nome;      // Nome da cidade
    bool temCentro;   // Indica se tem um Centro de Pokemon
    bool existe;      // Marca se a cidade esta cadastrada
};

Cidade cidades[MAX_CIDADES];  // Vetor para armazenar todas as cidades

// Matriz de adjac�ncia: 1 indica estrada entre duas cidades, 0 indica aus�ncia
int matrizAdj[MAX_CIDADES][MAX_CIDADES];

int totalCidades = 0;   // Contador de quantas cidades foram cadastradas

// Funcao auxiliar que retorna o indice da cidade pelo codigo
int indicePorCodigo(int codigo)  
{
    for (int i = 0; i < totalCidades; i++) {
        if (cidades[i].existe && cidades[i].codigo == codigo)
            return i; // Retorna o indice encontrado
    }
    return -1; // Retorna -1 se nao encontrar
}

// Funcao para cadastrar uma nova cidade
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

    // Inicializa conexoes (sem estradas ainda)
    for (int j = 0; j < MAX_CIDADES; j++) 
	{
      matrizAdj[totalCidades][j] = matrizAdj[j][totalCidades] = 0;	
	}
    cout << "Cidade cadastrada: [" << codigo << "] " << nome
         << (cidades[totalCidades].temCentro ? " (Centro Pokemon)" : "") << endl;

    totalCidades++; // Incrementa o total de cidades
}

// Funcao para cadastrar estrada entre duas cidades
void cadastrarEstrada() {
    if (totalCidades < 2) {
        cout << "E necessario ao menos duas cidades cadastradas." << endl;
        return;
    }

    int codA, codB;
    cout << "Informe o codigo da primeira cidade: ";
    cin >> codA;
    cout << "Informe o codigo da segunda cidade: ";
    cin >> codB;

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

    // Marca estrada entre as cidades (grafo nao-direcionado)
    matrizAdj[a][b] = 1;
    matrizAdj[b][a] = 1;

    cout << "Estrada cadastrada entre [" << codA << "] " << cidades[a].nome
         << " <-> [" << codB << "] " << cidades[b].nome << endl;
}

// Busca o Centro Pok�mon mais proximo usando BFS
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

    bool visitado[MAX_CIDADES];
    int pai[MAX_CIDADES];

    
    for (int i = 0; i < totalCidades; i++)  // Inicializa vetores de controle
	{
        visitado[i] = false;
        pai[i] = -1;
    }

    // Implementacao manual de fila
    int fila[MAX_CIDADES];
    int ini = 0, fim = 0;

    // Comeca a BFS na cidade atual
    fila[fim++] = start;
    visitado[start] = true;

    int destino = -1; // Cidade com centro encontrada

    while (ini < fim) {
        int atual = fila[ini++];

        if (cidades[atual].temCentro) // Se encontrou cidade com centro, para
		{
            destino = atual;
            break;
        }

        for (int v = 0; v < totalCidades; v++) // Percorre vizinhos
		{
            if (matrizAdj[atual][v] == 1 && !visitado[v]) {
                visitado[v] = true;
                pai[v] = atual;
                fila[fim++] = v;
            }
        }
    }

    if (destino == -1) {
        cout << "Nenhum Centro Pokemon acessivel a partir desta cidade." << endl;
        return;
    }

    // Reconstroi o caminho percorrendo os pais
    int caminho[MAX_CIDADES];
    int tam = 0;
    for (int v = destino; v != -1; v = pai[v]) {
        caminho[tam++] = v;
    }

    // Exibe a rota (do inicio ao destino)
    cout << "Rota ate o Centro Pokemon mais proximo:" << endl;
    for (int i = tam - 1; i >= 0; i--) {
        cout << "[" << cidades[caminho[i]].codigo << "] " << cidades[caminho[i]].nome;
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

void cadastrarPokemon() { cout << "Funcionalidade Pokemon nao implementada ainda." << endl; }
void removerPokemon() { cout << "Funcionalidade Pokemon nao implementada ainda." << endl; }
void listarPokemonsNome() { cout << "Funcionalidade Pokemon nao implementada ainda." << endl; }
void listarPokemonsTipo() { cout << "Funcionalidade Pokemon nao implementada ainda." << endl; }
void contarPokemonsTipo() { cout << "Funcionalidade Pokemon nao implementada ainda." << endl; }
void encontrarPokemonsProximos() { cout << "Funcionalidade Pokemon nao implementada ainda." << endl; }


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
