#include "RecordManager.h"

RecordManager::RecordManager(const std::string &targetFile): targetFile(targetFile) {}

void RecordManager::addRecord(const Record &record) const {
    auto stream = std::ofstream(targetFile, std::ios::app);;
    stream << record.name << " " << record.mode << " " << record.time << " " << record.finishedAt << std::endl;
}

void RecordManager::clearRecords() const {
    auto stream = std::ofstream(targetFile, std::ios::trunc);
    stream.close();
}

std::vector<Record> RecordManager::getRecords() const {
    auto stream = std::ifstream(targetFile);
    std::vector<Record> records;
    std::string name;
    int mode, time;
    long long finishedAt;
    while (stream >> name >> mode >> time >> finishedAt) {
        records.emplace_back(name, mode, time, finishedAt);
    }
    stream.close();
    return records;
}

