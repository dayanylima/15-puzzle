#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>    // std::find
#include "puzzle.h"

using namespace std;
using namespace chrono;

void file_read(const string &file_name, vector<vector<int>> &instances)
{
    string line;
    ifstream inputFile(file_name);
    if (!inputFile)
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        throw runtime_error("Erro ao abrir o arquivo.");
    }
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        int aux;
        vector<int> instances_aux;
        while (ss >> aux)
        {
            instances_aux.push_back(aux);
        }
        instances.push_back(instances_aux);
    }
    inputFile.close();
}

void print_instances(const vector<vector<int>> &instances)
{
    for (size_t i = 0; i < instances.size(); ++i)
    {
        cout << "Instância " << i + 1 << ": ";
        for (int value : instances[i])
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

void exibirSolucao(const vector<char> &solucao, const vector<int> &tabuleiroInicial)
{
    cout << "Solucao encontrada em " << solucao.size() << " passos: ";
    for (char c : solucao)
    {
        cout << c << " ";
    }
    cout << endl;

    cout << "Tabuleiro inicial:" << endl;
    for (int i = 0; i < 16; i++)
    {
        cout << tabuleiroInicial[i] << " ";
        if ((i + 1) % 4 == 0)
        {
            cout << endl;
        }
    }
    cout << endl;

    cout << "Movimentos:" << endl;
    vector<int> tabuleiroAtual = tabuleiroInicial;

    for (char c : solucao)
    {
        cout << "Movimento " << c << ":" << endl;
        int indiceZero = find(tabuleiroAtual.begin(), tabuleiroAtual.end(), 0) - tabuleiroAtual.begin();
        int x = indiceZero % 4;
        int y = indiceZero / 4;

        switch (c)
        {
        case 'U': // UP
            swap(tabuleiroAtual[indiceZero], tabuleiroAtual[x + (y - 1) * 4]);
            break;
        case 'D': // DOWN
            swap(tabuleiroAtual[indiceZero], tabuleiroAtual[x + (y + 1) * 4]);
            break;
        case 'L': // LEFT
            swap(tabuleiroAtual[indiceZero], tabuleiroAtual[(x - 1) + y * 4]);
            break;
        case 'R': // RIGHT
            swap(tabuleiroAtual[indiceZero], tabuleiroAtual[(x + 1) + y * 4]);
            break;
        }

        for (int i = 0; i < 16; i++)
        {
            cout << tabuleiroAtual[i] << " ";
            if ((i + 1) % 4 == 0)
            {
                cout << endl;
            }
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> instances;
    string file_name = "15puzzle_instances.txt";

    try
    {
        file_read(file_name, instances);
    }
    catch (const exception &e)
    {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }

    while (true)
    {
        cout << "Instâncias lidas do arquivo:" << endl;
        print_instances(instances);

        int choice;
        cout << "Escolha uma instância para resolver (1 a " << instances.size() << ", ou 0 para sair): ";
        cin >> choice;

        if (choice == 0)
        {
            break;
        }

        if (choice < 1 || choice > static_cast<int>(instances.size()))
        {
            cout << "Escolha inválida. Tente novamente." << endl;
            continue;
        }

        const auto &instance = instances[choice - 1];
        cout << "Resolvendo a instância " << choice << ":" << endl;
        for (int value : instance)
        {
            cout << value << " ";
        }
        cout << endl;

        Puzzle puzzle(instance);

        puzzle.print_board();

        int evaluated_states = 0;
        auto start = high_resolution_clock::now();
        vector<char> solucao = puzzle.solve(evaluated_states);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start).count();

        if (!solucao.empty())
        {
            exibirSolucao(solucao, instance);
        }
        else
        {
            cout << "Não foi encontrada uma solução." << endl;
        }

        cout << "Estados avaliados: " << evaluated_states << endl;
        cout << "Tempo de execução: " << duration << " ms" << endl;
    }

    return 0;
}
