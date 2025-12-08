#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<std::string> parseFile() {
    std::vector<std::string> instructions;

    std::ifstream readFile("input.txt");
    std::string line;

    while(getline(readFile, line)) {
        if (line.empty()) continue;
        instructions.push_back(line);
    }

    return instructions;
}

int partOne(const std::vector<std::string>& instructions) {
    int result = 0;

    for(const auto& range : instructions) {
        const std::string& s = range;
        int best = 0;

        // Brute Force
        for(int i = 0; i < s.size() - 1; ++i) {
            int first = s[i] - '0';

            for(int j = i + 1; j < s.size(); ++j) {
                int second = s[j] - '0';

                int value = first * 10 + second;
                if(value > best) best = value;
            }
        }
        result += best;
    }

    return result;
}

long long partTwo(const std::vector<std::string>& instructions) {
    long long result = 0;

    for(const auto& batteries : instructions) {
        int toRemove = batteries.length() - 12;

        // Monotonic stack container
        std::string best;
        best.reserve(batteries.length());

        for(char c : batteries) {
            while(!best.empty() && best.back() < c && toRemove > 0) {
                best.pop_back();
                toRemove--;
            }
            best.push_back(c);
        }
        best.resize(12);

        result += std::stoll(best);
    }


    return result;
}

int main() {
    std::vector<std::string> instructions;
    instructions = parseFile();

    std::cout << "Part One: " << partOne(instructions) << '\n';
    std::cout << "Part Two: " << partTwo(instructions) << '\n';
    
    return 0;
}