//
// Created by alihitawala on 9/20/16.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <climits>

// Bucket size for this program
#define BUCKET_SIZE 100

using namespace std;
// Container to store the data each line it stores first - sum till now,
// second - max till now and count is the count this key appeared in data
class Data {
    string key;
    long double first;
    int second, count;
    bool secondPresent;
public:
    Data() {}

    Data(const string &key, long double first, int second) : key(key), first(first), second(second) {
        Data::count = 0;
        Data::secondPresent = false;
    }

    bool isSecondPresent() const {
        return secondPresent;
    }

    void setSecondPresent(bool secondPresent) {
        Data::secondPresent = secondPresent;
    }

    long double getFirst() const {
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

    void setFirst(long double first) {
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

// Hashmap impl - takes key as string and value as Data object
class HashMap {
    vector<Data> buckets[BUCKET_SIZE];
    // hash function for this hash map
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
    // Given key get index of data in its bucket or return -1 if key is missing
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

    // check if that key is there in that map
    bool find(string key) {
        return this->getIndexIfPresent(key) != -1;
    }

    // get Value given key
    Data getData(string key) {
        int k = hash_function(key);
        return buckets[k][this->getIndexIfPresent(key)];
    }

    // add or update the key and value
    void add(string key, Data value) {
        int index = this->getIndexIfPresent(key);
        int k = this->hash_function(key);
        if (index == -1) {
            buckets[k].push_back(value);
        } else {
            buckets[k][index] = value;
        }
    }

    // gets all the values in a vector present in this hash map
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

// checks if the string in an integer
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
    //open input and output file
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string line, delim = ",";
    HashMap* map = new HashMap();
    while (getline(input, line)) {
        char *token, *str, *tofree;
        tofree = str = strdup(line.c_str());
        token = strsep(&str, delim.c_str());
        // Extract string from the line
        string key = string(token);
        token = strsep(&str, delim.c_str());
        // Extract first int from line
        long double f = 0.0;
        bool firstValuePresent = false;
        bool secondValuePresent = false;
        if (isInteger(token)) {
            f = (double) stoi(token);
            firstValuePresent = true;
        }
        token = strsep(&str, delim.c_str());
        // Extract second int from line
        int s = INT_MIN;
        if (isInteger(token)) {
            s = stoi(token);
            secondValuePresent = true;
        }
        Data newData = Data(key, f, s);
        newData.setSecondPresent(newData.isSecondPresent() || secondValuePresent);
        // if the data already present update it
        if (map->find(key)) {
            newData = map->getData(key);
            // sum till now
            newData.setFirst(newData.getFirst() + f);
            // max till now
            if (newData.getSecond() < s) {
                newData.setSecond(s);
            }
        }
        if (firstValuePresent)
            newData.setCount(newData.getCount() + 1);
        map->add(key, newData);
        free(tofree);
    }
    vector<Data> allData = map->getAllData();
    for (auto const &d: allData) {
        output << fixed << setprecision(16);
        if (d.getCount() == 0 && !d.isSecondPresent())
            output << d.getKey() << "\t|" << "" << "\t|" << "" << "\n";
        else if (d.getCount() == 0)
            output << d.getKey() << "\t|" << "" << "\t|" << to_string(d.getSecond()) << "\n";
        else if (!d.isSecondPresent())
            output << d.getKey() << "\t|" << ((double)d.getFirst() / (double) d.getCount()) << "\t|" << "" << "\n";
        else
            output << d.getKey() << "\t|" << ((double)d.getFirst() / (double) d.getCount()) << "\t|" << to_string(d.getSecond()) << "\n";
    }
    output.close();
    input.close();
    return 0;
}