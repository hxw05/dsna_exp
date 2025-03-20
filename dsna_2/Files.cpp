#include "EVFiles.h"

vector<EdgeObject> getEdgesFromFile() {
    ifstream in;
    in.open(EdgeFilePath);

    vector<EdgeObject> result;

    while (true) {
        EdgeObject obj{};
        in >> obj.mark1;
        if (in.fail()) break;

        in >> obj.mark2;
        in >> obj.weight;

        result.push_back(obj);
    }

    in.close();

    return result;
}

void readString(ifstream &in, string &toBuild) {
    char seq;
    in >> seq;
    if (seq == '"') {
        while (true) {
            in.get(seq);
            if (seq == '"') break;
            toBuild.push_back(seq);
        }
    }
}

vector<VexObject> getVexesFromFile() {
    ifstream in;
    in.open(VexFilePath);

    vector<VexObject> result;

    while (true) {
        VexObject obj{};
        in >> obj.number;
        if (in.fail()) break;

        in >> obj.mark;

        readString(in, obj.name);
        readString(in, obj.desc);

        result.push_back(obj);
    }

    in.close();
    return result;
}