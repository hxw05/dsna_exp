#ifndef RECORD_H
#define RECORD_H
#include <fstream>
#include <vector>

struct Record {
    std::string name;
    int mode;
    int time;
    long long finishedAt;
};

class RecordManager {
public:
    std::string targetFile;

    RecordManager(const std::string &targetFile);

    void addRecord(const Record &record) const;

    std::vector<Record> getRecords() const;

     void clearRecords() const;
};



#endif //RECORD_H
