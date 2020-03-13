#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
string str;
pair<int,int> reach[510][510][35];

map<char,pair<int,int> > mov = {
    {'L', {0, -1}},
    {'R', {0, 1}},
    {'U', {-1, 0}},
    {'D', {1, 0}}
};

bool ok(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m && grid[x][y] != '#';
}

void pro(int x, int y) {
    int sx = x, sy = y;
    for(int i = 0; i < (int)str.size(); i++) {
        char c = str[i];
        int nx = x + mov[c].first;
        int ny = y + mov[c].second;
        if(ok(nx, ny)) {
            x = nx;
            y = ny;
        }
    }
    reach[sx][sy][0] = {x, y};
}
void pre() {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == '#'){
                reach[i][j][0] = {i, j};
                //continue;
            }
            else{
                pro(i, j);
            }
            //cout << reach[i][j][0].first << " " << reach[i][j][0].second << "     ";
        }
    }
    
    for(int p = 1; p <= 30; p++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                pair<int,int>  last = reach[i][j][p-1];
                reach[i][j][p] = reach[last.first][last.second][p-1];
            }
        }
    }
}

void solve() {
    int x, y, z;
    cin >> x >> y >> z;
    x--;
    y--;
    
    int temp = z / (int)str.size();
    int remain = z  % (int)str.size();
    
    for(int i = 30; i >= 0; i--){
        if(temp & (1 << i)) {
           // cout << "On bit " << i << endl;
            int tx = reach[x][y][i].first;
            int ty = reach[x][y][i].second;
            x = tx, y = ty;
        }
    }
    
    for(int i = 0; i < remain; i++) {
        char c = str[i];
        int nx = x + mov[c].first;
        int ny = y + mov[c].second;
        if(ok(nx, ny)) {
            x = nx;
            y = ny;
        }
    }
    cout << x + 1 << " " << y + 1 << endl;
}

int main() {
    int q;
    cin >> n >> m >> q;
    
    grid.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    cin >> str;
    pre();
    
    while(q--){
        solve();
    }
    
}
