#include <bits/stdc++.h>
using namespace std;

// Generate a safe filename for a given index using its hash
static string fileName(const string &idx) {
    size_t h = hash<string>{}(idx);
    std::ostringstream oss;
    oss << "idx_" << std::hex << h << ".txt";
    return oss.str();
}

// Load values for an index from its file into a set
static set<int> loadValues(const string &fname) {
    set<int> vals;
    ifstream fin(fname);
    int v;
    while (fin >> v) {
        vals.insert(v);
    }
    return vals;
}

// Save a set of values back to the file (sorted order)
static void saveValues(const string &fname, const set<int> &vals) {
    if (vals.empty()) {
        // Remove empty file
        remove(fname.c_str());
        return;
    }
    ofstream fout(fname, ios::trunc);
    for (int v : vals) {
        fout << v << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    string cmd, idx;
    int val;
    for(int i=0;i<n;++i){
        cin >> cmd >> idx;
        string fname = fileName(idx);
        if (cmd == "insert") {
            cin >> val;
            set<int> vals = loadValues(fname);
            if (!vals.count(val)) {
                vals.insert(val);
                saveValues(fname, vals);
            }
        } else if (cmd == "delete") {
            cin >> val;
            set<int> vals = loadValues(fname);
            if (vals.erase(val)) {
                saveValues(fname, vals);
            }
        } else if (cmd == "find") {
            set<int> vals = loadValues(fname);
            if (vals.empty()) {
                cout << "null\n";
            } else {
                bool first = true;
                for (int v : vals) {
                    if (!first) cout << ' ';
                    first = false;
                    cout << v;
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
