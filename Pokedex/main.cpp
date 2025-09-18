#include <iostream>
#include <cstring>
#include <list>
#include <iterator>

using namespace std;

// Função de Cadastrar Cidade
void cadastrarCidade(string nome)
{
    cout << "Funcionalidade em construcao..." << endl;
}

// Função de Cadastrar Estrada
void cadastrarEstrada(string nome)
{
    cout << "Funcionalidade em construcao..." << endl;
}

// Função de Buscar Centro Pokemon Mais Proximo
void buscarCentroPokemonMaisProximo(string nomeCidade)
{
    cout << "Funcionalidade em construcao..." << endl;
}

// Função de Cadastrar Pokemon
void cadastrarPokemon(string nome, string tipo)
{
    cout << "Funcionalidade em construcao..." << endl;
}

// Função de Remover Pokemon
void removerPokemon(string nome)
{
    cout << "Funcionalidade em construcao..." << endl;
}

// Função de Listar Pokemons por Nome
void listarPokemonsNome(string nome)
{
    cout << "Funcionalidade em construcao..." << endl;
}

// Função de Listar Pokemons por Tipo
void listarPokemonsTipo(string tipo)
{
    cout << "Funcionalidade em construcao..." << endl;
}

// Função de Contar Pokemons de Cada Tipo
int contarPokemonsTipo(int qtdTipo)
{
    cout << "Funcionalidade em construcao..." << endl;
    return 0;
}

// Função de Encontrar Pokemons Proximos
void encontrarPokemonsProximos(string localizacao)
{
    cout << "Funcionalidade em construcao..." << endl;
}

int main()
{
    int opcao;

    do 
    {
        cout << "...MENU POKEDEX...:" << endl;
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
        cout << "Escolha uma opcao: " << endl;

        cin >> opcao;

        switch(opcao)
        {
            case 1:
            {
                cadastrarCidade(); 
                break;
            }
            case 2:
            {
                cadastrarEstrada(); 
                break;
            }
            case 3:
            {
                buscarCentroPokemonMaisProximo(); 
                break;
            }
            case 4:
            {
                cadastrarPokemon(); 
                break;
            }
            case 5:
            {
                removerPokemon(); 
                break;
            }
            case 6:
            {
                listarPokemonsNome(); 
                break;
            }
            case 7:
            {
                listarPokemonsTipo(); 
                break;
            }
            case 8:
            {
                contarPokemonsTipo(); 
                break;
            }
            case 9:
            {
                encontrarPokemonsProximos(); 
                break;
            }
            case 0:
            {
                cout << "Saindo do programa..." << endl;
                break;
            }
            default:
            {
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
            }
        }

    }while(opcao != 0);

    return 0;
}