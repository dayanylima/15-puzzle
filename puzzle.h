#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <functional>
#include <cmath>

using namespace std;

struct PuzzleState
{
private:
    vector<int> board;
    vector<char> path;
    int total_cust, accumulated_cost, heuristic;

public:
    PuzzleState(const vector<int> &board, const vector<char> &path, int accumulated_cost);
    int manhattanDistance(int x1, int y1, int x2, int y2) const;
    int calculateHeuristic() const;
    bool stateObjective() const;
    vector<PuzzleState> generateMovements() const;
    int getTotalCost() const;
    int getAccumulatedCost() const;
    int getHeuristic() const;
    vector<char> getPath() const;
    const vector<int> &getBoard() const;
    size_t generateHash() const;
};

class Puzzle
{
private:
    vector<int> initial_board;
    priority_queue<PuzzleState, vector<PuzzleState>, function<bool(const PuzzleState &, const PuzzleState &)>> priority;
    unordered_set<size_t> visited;
    size_t max_queue_size;    // Alterado para size_t
    int max_depth;           // Limite na profundidade da busca

public:
    Puzzle(vector<int> instance, size_t max_queue_size = 1000000, int max_depth = 50);
    void print_board();
    vector<char> solve(int &evaluated_states);
};


#endif // PUZZLE_H
