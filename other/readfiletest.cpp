#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string line;
    std::ifstream infile("classB0data.txt");
    std::vector<std::vector<int> > forest;

    while (std::getline(infile, line)) {
        std::vector<int> row;

        for (int &c : line) {
            if (c != ',') {
                row.push_back(c);
            }
        }

        forest.push_back(row);
    }

    for (std::vector<int> &row : forest) {
        for (int &c : row) {
            std::cout << c << ' ';
        }

        std::cout << '\n';
    }

    return 0;
}