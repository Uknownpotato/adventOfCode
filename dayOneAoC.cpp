#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<std::pair<char,int>> parseFile() {
    std::vector<std::pair<char,int>> instructions;

    std::ifstream readFile("input.txt");
    std::string line;

    while(getline(readFile, line)) {
        if (line.empty()) continue;

        char direction = line[0];
        int value = stoi(line.substr(1));

        instructions.push_back({direction,value});

    }

    return instructions;
}

void partTwo(const std::vector<std::pair<char,int>>& instructions) {
    int result = 0;
    int pos = 50;

    for(int i = 0; i < instructions.size(); i++) {
        char direction = instructions[i].first;
        int value = instructions[i].second;

        int full_rotations = value / 100;
        result += full_rotations;

        int remaining = value % 100;

        if(direction == 'R') {
            int zeroClick = (100 - pos) % 100;

            if(zeroClick != 0 && zeroClick <= remaining) result++;

            pos = (pos + remaining) % 100;
        } else if(direction == 'L') {
            int zeroClick = pos;

            if(zeroClick != 0 && zeroClick <= remaining) result++;

            pos = ((pos - remaining) % 100 + 100) % 100;
        } else {
            continue;
        }
    }

    std::cout << "Part Two: " << result << '\n';
}

void partOne(const std::vector<std::pair<char,int>>& instructions) {
    int result = 0;
    int pos = 50;

    for(int i = 0; i < instructions.size(); i++) {
        char direction = instructions[i].first;
        int value = instructions[i].second;

        if(direction == 'R') {
            pos = (pos + value) % 100;
        } else if(direction == 'L') {
            pos = (pos - value) % 100;
        } else {
            continue;
        }
        if(pos == 0) result++;
    }

    std::cout << "Part One: " << result << '\n';
}


int main() {
    std::vector<std::pair<char,int>> instructions;

    instructions = parseFile();

    partOne(instructions);
    partTwo(instructions);

    return 0;
}
