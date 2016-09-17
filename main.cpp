#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <unordered_map>

using namespace std;

class Data {
    string key;
    int first, second, count;
public:
    Data() {}

    Data(const string &key, int first, int second) : key(key), first(first), second(second) {
        Data::count = 0;
    }

    int getFirst() const {
        return first;
    }

    int getSecond() const {
        return second;
    }

    const string &getKey() const {
        return key;
    }

    void setKey(const string &key) {
        Data::key = key;
    }

    void setFirst(int first) {
        Data::first = first;
    }

    void setSecond(int second) {
        Data::second = second;
    }

    int getCount() const {
        return count;
    }

    void setCount(int count) {
        Data::count = count;
    }
};

int main() {
    ifstream input("data.txt");
    ofstream output("output.dat");
    string line, delim = ",";
    unordered_map<string, Data> data(9);
    while (getline(input, line)) {
        char *cstr = strdup(line.c_str());
        char *p = strtok(cstr, delim.c_str());
        string key = string(p);
        p = strtok(NULL, delim.c_str());
        int f = stoi(p);
        p = strtok(NULL, delim.c_str());
        int s = stoi(p);
        if (data.find(key) == data.end()) {
            data[key] = Data(key, f, s);
        } else {
            data[key].setFirst(data[key].getFirst() + f);
            if (data[key].getSecond() < s) {
                data[key].setSecond(s);
            }
        }
        data[key].setCount(data[key].getCount() + 1);
    }
    for (auto const &item: data) {
        Data d = item.second;
        double avg = d.getFirst() * 1.0 / d.getCount();
        ostringstream strs;
        strs << avg;
        string out = d.getKey() + "\t" + strs.str() + "\t" + to_string(d.getSecond()) + "\n";
        output << out;
        cout << d.getKey() << " " << avg << " " << d.getSecond() << endl;
    }
    output.close();
    input.close();
    return 0;
}