#pragma once
#include <string>
#include <vector>

struct PlayerRecord {
    std::string name;
    int score;
};

class Leaderboard {
public:
    Leaderboard(const std::string& filename);

    void addRecord(const std::string& name, int score);
    bool save() const;
    bool load();
    void clear();

    const std::vector<PlayerRecord>& getRecords() const;

private:
    std::string m_filename;
    std::vector<PlayerRecord> m_records;

    void sort();
};