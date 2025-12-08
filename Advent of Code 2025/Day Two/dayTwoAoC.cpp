#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<std::pair<long long, long long>> parseFile() {
    std::vector<std::pair<long long, long long>> idSeq;

    std::ifstream readFile("input.txt");
    std::string line;

    while(getline(readFile, line, ',')) {
        if (line.empty()) continue;

        while(!line.empty() && (line.back() == '\n' || line.back() == '\r'))
            line.pop_back();

        std::size_t idx = line.find('-');
        if (idx == std::string::npos) continue;

        long long start = std::stoll(line.substr(0, idx));
        long long end = std::stoll(line.substr(idx + 1));

        idSeq.push_back(std::make_pair(start, end));
    }

    return idSeq;
}


long long partTwo(const std::vector<std::pair<long long, long long>> idSeq) {
    long long result = 0;
    
    for(const auto& range : idSeq) {
        long long start = range.first;
        long long end = range.second;

        for(long long id = start; id <= end; ++id) {
            std::string s = std::to_string(id);
            int L = s.length();
            bool invalid = false;

            for(int baseLen = 1; baseLen <= L / 2 && !invalid; ++baseLen) {
                if(L % baseLen != 0) continue;

                // First block of size baseLen
                std::string pattern = s.substr(0, baseLen);
                bool allMatch = true;

                // Verify every subsequent block against pattern
                for(int pos = baseLen; pos < L; pos += baseLen) {
                    if(s.compare(pos, baseLen, pattern) != 0) {
                        allMatch = false;
                        break;
                    }
                }
                if(allMatch) invalid = true;
            }
            if(invalid) result += id;
        }
    }
    return result;
}

long long partOne(const std::vector<std::pair<long long, long long>> idSeq) {
    long long result = 0;

    for(const auto& range : idSeq) {
        long long start = range.first;
        long long end = range.second;

        for(long long id = start; id <= end; ++id) {
            std::string str = std::to_string(id);
            if(str.length() % 2 == 1) continue;

            int half = str.length() / 2;
            std::string left = str.substr(0, half);
            std::string right = str.substr(half);

            if(left == right) result += id;
        }
    }
    return result;
}

int main() {
    std::vector<std::pair<long long, long long>> idSeq;

    idSeq = parseFile();

    std::cout << "Part One: " << partOne(idSeq) << '\n';
    std::cout << "Part Two: " << partTwo(idSeq) << '\n';

    return 0;
}