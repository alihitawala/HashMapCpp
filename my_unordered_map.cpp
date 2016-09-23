#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>

#define BUCKET_SIZE 10

using namespace std;

class Data {
    string key;
    double first;
    int second, count;
public:
    Data() {}

    Data(const string &key, double first, int second) : key(key), first(first), second(second) {
        Data::count = 0;
    }

    double getFirst() const {
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

    void setFirst(double first) {
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
class HashMap {
    vector<Data> buckets[BUCKET_SIZE];
    int hash_function(string word) {
        int seed = 131;
        unsigned long hash = 0;
        for(int i = 0; i < (int)word.length(); i++)
        {
            hash = (hash * seed) + word[i];
        }
        int h = (int) hash % BUCKET_SIZE;
        return h < 0 ? -h : h;
    }

    int getIndexIfPresent(string key) {
        int k = hash_function(key);
        vector<Data> temp = buckets[k];
        int i = 0;
        for (std::vector<Data>::iterator it = temp.begin() ; it != temp.end(); ++it) {
            if (it->getKey().compare(key) == 0) {
                return i;
            }
            i++;
        }
        return -1;
    }
public:
    HashMap() {}

    bool find(string key) {
        return this->getIndexIfPresent(key) != -1;
    }

    Data getData(string key) {
        int k = hash_function(key);
        return buckets[k][this->getIndexIfPresent(key)];
    }

    void add(string key, Data value) {
        int index = this->getIndexIfPresent(key);
        int k = this->hash_function(key);
        if (index == -1) {
            buckets[k].push_back(value);
        } else {
            buckets[k][index] = value;
        }
    }

    vector<Data> getAllData() {
        vector<Data> result;
        for (int i = 0; i < BUCKET_SIZE; ++i) {
            vector<Data> temp = buckets[i];
            for (auto const &item: temp) {
                result.push_back(item);
            }
        }
        return result;
    }
};

inline bool isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

    char * p ;
    strtol(s.c_str(), &p, 10) ;

    return (*p == 0) ;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage <program_name> <input_file_name> <outout_file_name>" << endl;
        exit(1);
    }
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string line, delim = ",";
    unordered_map<string, Data> data(9);
    while (getline(input, line)) {
        char *token, *str, *tofree;
        tofree = str = strdup(line.c_str());
        token = strsep(&str, delim.c_str());
        string key = string(token);
        token = strsep(&str, delim.c_str());
        double f = 0.0;
        if (isInteger(token)) {
            f = (double) stoi(token);
        }
        token = strsep(&str, delim.c_str());
        double s = 0.0;
        if (isInteger(token)) {
            s = (double) stoi(token);
        }
        if (data.find(key) == data.end()) {
            data[key] = Data(key, f, s);
        } else {
            data[key].setFirst(data[key].getFirst() + f);
            if (data[key].getSecond() < s) {
                data[key].setSecond(s);
            }
        }
        data[key].setCount(data[key].getCount() + 1);
        free(tofree);
    }
    for (auto const &item: data) {
        Data d = item.second;
        double avg = d.getFirst() * 1.0 / d.getCount();
        ostringstream strs;
        strs << avg;
        string out = d.getKey() + "\t" + strs.str() + "\t" + to_string(d.getSecond()) + "\n";
        output << out;
    }
    output.close();
    input.close();
    return 0;
}