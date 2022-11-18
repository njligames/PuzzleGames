#include <vector>
#include <string>

using namespace std;

class NameGenerator {
    public:
        NameGenerator();
        string next();
    void randomize();
    void sort();
    private:
        vector<string> mNames;
        vector<string>::iterator mIterator;
};

