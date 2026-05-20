#include "leaderboard.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

Leaderboard::Leaderboard(const std::string& filename)
    : m_filename(filename) {}

void Leaderboard::addRecord(const std::string& name, int score) {
    m_records.push_back({ name, score });
    sort();
}

bool Leaderboard::save() const {
    std::ofstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "[Leaderboard] Failed to open file for writing: " << m_filename << "\n";
        return false;
    }

    for (const auto& rec : m_records) {
        // Format: "score name_with_possible_spaces"
        // Name is written last so spaces inside it are preserved
        file << rec.score << " " << rec.name << "\n";
    }
    return file.good();
}

bool Leaderboard::load() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        // File doesn't exist — create it and start with empty records
        std::ofstream newFile(m_filename);
        if (!newFile.is_open()) {
            std::cerr << "[Leaderboard] Failed to create file: " << m_filename << "\n";
            return false;
        }
        return true;
    }

    m_records.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        PlayerRecord rec;
        if (!(ss >> rec.score)) continue;          // read score
        std::getline(ss >> std::ws, rec.name);     // rest of line = name
        if (!rec.name.empty())
            m_records.push_back(rec);
    }
    return !file.bad();
}

void Leaderboard::clear() {
    m_records.clear();
}

const std::vector<PlayerRecord>& Leaderboard::getRecords() const {
    return m_records;
}

void Leaderboard::sort() {
    std::sort(m_records.begin(), m_records.end(),
        [](const PlayerRecord& a, const PlayerRecord& b) {
            return a.score > b.score; // descending
        });
}