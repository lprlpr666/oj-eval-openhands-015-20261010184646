#include <bits/stdc++.h>
using namespace std;

const string DATA_FILE = "data.txt";

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    string cmd, idx;
    int val;
    for(int i=0;i<n;++i){
        cin >> cmd >> idx;
        if(cmd == "insert"){
            cin >> val;
            // Check if pair already exists
            bool exists = false;
            {
                ifstream fin(DATA_FILE);
                string i2; int v2;
                while(fin >> i2 >> v2){
                    if(i2 == idx && v2 == val){ exists = true; break; }
                }
            }
            if(!exists){
                ofstream fout(DATA_FILE, ios::app);
                fout << idx << ' ' << val << '\n';
            }
        } else if(cmd == "delete"){
            cin >> val;
            // Rewrite file without the specific pair
            ifstream fin(DATA_FILE);
            vector<pair<string,int>> entries;
            string i2; int v2;
            while(fin >> i2 >> v2){
                if(!(i2 == idx && v2 == val)) entries.emplace_back(i2, v2);
            }
            ofstream fout(DATA_FILE, ios::trunc);
            for(auto &p : entries) fout << p.first << ' ' << p.second << '\n';
        } else if(cmd == "find"){
            // Collect values for idx
            set<int> values;
            ifstream fin(DATA_FILE);
            string i2; int v2;
            while(fin >> i2 >> v2){
                if(i2 == idx) values.insert(v2);
            }
            if(values.empty()) cout << "null\n";
            else {
                bool first = true;
                for(int v : values){
                    if(!first) cout << ' ';
                    first = false;
                    cout << v;
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
