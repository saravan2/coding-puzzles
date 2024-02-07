#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>

const size_t MAX_CHUNK_SIZE = 1000000;
const size_t CHUNK_FILES = 3;

void createChunkFile(const std::string& filename, const std::string& output_folder, int chunk_count) {
    std::ifstream input_file(filename);
    std::unordered_set<std::string> encounteredKeys;
    std::ofstream output_file(output_folder + "/chunk" + std::to_string(chunk_count)+ ".txt");
    while (!input_file.eof()) {
        std::string line;
        int key_count = 0;
        while (key_count < MAX_CHUNK_SIZE && std::getline(input_file, line)) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                if (encounteredKeys.find(key) == encounteredKeys.end()) {
                    output_file << line << std::endl;
                    encounteredKeys.insert(key);
                    key_count++;
                }
            }
        }
    }
    input_file.close();
    output_file.close();
}

void mergeChunks(const std::string& output_folder) {
    std::ofstream output_file(output_folder + "/output.txt");
    std::vector<std::ifstream> input_files; 
    for (int i = 0; i < CHUNK_FILES; i++) {
        input_files.emplace_back(output_folder + "/chunk" + std::to_string(i) + ".txt");
    }
    std::vector<std::pair<std::string, std::string>> current_values;
    for (int i = 0; i < CHUNK_FILES; i++) {
        std::string line;
        if(std::getline(input_files[i], line)) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    current_values.push_back(std::make_pair(key, value));
            }
        }
    }
    while(!current_values.empty()) {
        auto min_entry = std::min_element(current_values.begin(), current_values.end(), 
            [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
                return a.first.compare(b.first) < 0;
            });
        output_file << min_entry->first << "=" << min_entry->second << std::endl;
        int min_index = std::distance(current_values.begin(), min_entry);
        std::string line;
        if(!input_files[min_index].eof() && std::getline(input_files[min_index], line)) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    current_values[min_index] = std::make_pair(key, value);
            }
        } else {
            current_values.erase(current_values.begin() + min_index);
            input_files[min_index].close();
            input_files.erase(input_files.begin() + min_index);
        }
    }

    for (auto& file : input_files) {
        file.close();
    }

    output_file.close();
}

int main(int arg, char* argv[]) {
     for (int i = 0; i < CHUNK_FILES; ++i) {
        createChunkFile("input" + std::to_string(i) + ".txt", "output", i);
     }
     mergeChunks("output");
    return 0;
}