#include "puzzle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

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
    for (const auto &instance : instances)
    {
        for (int value : instance)
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

void exibirSolucao(const std::vector<char> &solucao, const std::vector<int> &tabuleiroInicial)
{
    std::cout << "Solucao encontrada em " << solucao.size() << " passos: ";
    for (char c : solucao)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::cout << "Tabuleiro inicial:" << std::endl;
    for (int i = 0; i < 16; i++)
    {
        std::cout << tabuleiroInicial[i] << " ";
        if ((i + 1) % 4 == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "Movimentos:" << std::endl;
    std::vector<int> tabuleiroAtual = tabuleiroInicial;

    for (char c : solucao)
    {
        std::cout << "Movimento " << c << ":" << std::endl;
        int indiceZero = find(tabuleiroAtual.begin(), tabuleiroAtual.end(), 0) - tabuleiroAtual.begin();
        int x = indiceZero % 4;
        int y = indiceZero / 4;

        switch (c)
        {
        case 'U': // UP
            std::swap(tabuleiroAtual[indiceZero], tabuleiroAtual[x + (y - 1) * 4]);
            break;
        case 'D': // DOWN
            std::swap(tabuleiroAtual[indiceZero], tabuleiroAtual[x + (y + 1) * 4]);
            break;
        case 'L': // LEFT
            std::swap(tabuleiroAtual[indiceZero], tabuleiroAtual[(x - 1) + y * 4]);
            break;
        case 'R': // RIGHT
            std::swap(tabuleiroAtual[indiceZero], tabuleiroAtual[(x + 1) + y * 4]);
            break;
        }

        for (int i = 0; i < 16; i++)
        {
            std::cout << tabuleiroAtual[i] << " ";
            if ((i + 1) % 4 == 0)
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
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

    cout << "Instâncias lidas do arquivo:" << endl;
    print_instances(instances);

    for (size_t i = 0; i < instances.size(); ++i)
    {
        cout << "Tentando resolver a instância " << (i + 1) << ":" << endl;
        const auto &instance = instances[i];

        try
        {
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
                cout << "Instância " << (i + 1) << " resolvida com sucesso!" << endl;
                cout << "Estados avaliados: " << evaluated_states << endl;
                cout << "Tempo de execução: " << duration << " ms" << endl;
                // Se desejar parar após encontrar a primeira solução válida, descomente a linha abaixo
                // break;
            }
            else
            {
                cout << "Não foi encontrada uma solução para a instância " << (i + 1) << "." << endl;
            }
        }
        catch (const runtime_error &e)
        {
            cerr << "Erro na resolução da instância " << (i + 1) << ": " << e.what() << endl;
        }
    }

    return 0;
}
