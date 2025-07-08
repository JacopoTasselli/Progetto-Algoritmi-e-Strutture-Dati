#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<string> nodes;
vector<list<int> > edges;
vector<list<int> > inverted_edges;
vector<int> visited;

void read_file(string file_name){
    list<string> node_demo = list<string>();
    node_demo.push_back("");

    list<pair<int,int> > edges_demo = list<pair<int,int> >();

    ifstream filein(file_name);
    string line;
    while(getline(filein,line)){
        if(line.at(0)=='S'){
            node_demo.push_back("");
            for(auto it=line.begin(); it != line.end(); it++){
                if(*it == 'A'||*it == 'C'||*it == 'G'||*it == 'T'){
                    *prev(node_demo.end())+=*it;
                }
            }
        }
        if(line.at(0)=='L'){
            pair<int,int> demo = pair<int,int>(0,0); 
            bool is_first_number = true;
            for(auto it=line.begin()+1; it != line.end(); it++){
                if(*it == ' ' || *it == '	'){
                    continue;
                }
                if(*it == '+'){
                    if(is_first_number){
                        is_first_number = false;
                        continue;
                    } 
                    break;
                }
                if(is_first_number){
                    demo.first = demo.first * 10 + (int)(*it-'0');
                }else{
                    demo.second = demo.second * 10 + (int)(*it-'0');
                }
            }
            edges_demo.push_back(demo);
       }
    }

    nodes = vector<string>(node_demo.size());
    for(int i=0; i<nodes.size(); i++){
        nodes[i] = node_demo.front();
        node_demo.pop_front();
    }
    
    edges = vector<list<int> >(nodes.size(), list<int>());
    inverted_edges = vector<list<int> >(nodes.size(), list<int>());
    while(edges_demo.size() > 0){
        edges[edges_demo.front().first].push_back(edges_demo.front().second);
        inverted_edges[edges_demo.front().second].push_back(edges_demo.front().first);
        edges_demo.pop_front();
    }



}

void verify_aciclicity(int n){
    visited[n] = 1;
    auto i = edges[n].begin();
    while(i != edges[n].end()){
       if(visited[*i] == 0){
            verify_aciclicity(*i);
            i++;
        } else if(visited[*i] == 1){
            auto j = i;
            j++;
            edges[n].erase(i);
            i = j;
        }else{
            i++;
        }
    }
    visited[n] = 2;
}

void start_destination(int &start, int &destination){
    start = 0;
    int i = 1;
    while(start == 0){
        if(inverted_edges[i].size() == 0){
            start = i;
        }
        i++;
    }
    destination = 0;
    i = 1;
    while(destination == 0){
        if(edges[i].size() == 0){
            destination = i;
        }
        i++;
    }
}

void paths_generator(int n, string s, int destination, list<string> &paths ){
    if( n == destination){
        paths.push_back(s+nodes[n]);
        return;
    }
    for(int d : edges[n]){
        paths_generator(d,s+nodes[n],destination,paths);
    }
}

void print_paths(int start, int destination){
    list<string> paths = list<string>();
    paths_generator(start,"",destination,paths);
    for(auto d: paths){
        cout << d << endl;
    }
}

int k_mer_finder(string kmer){
    int k = kmer.size();
    vector<vector<int> > occurences(k, vector<int>(nodes.size(),0));

    for(int n = 1; n<nodes.size(); n++){
        int strlen = nodes[n].size();
        for(int i =1; i<=strlen; i++){
            if(kmer.starts_with())
        }
    }
}

int main(int argc, char* args[]){
    bool must_print_paths;
    string k_mer;
    string filename;
    if(argc < 2){
        cout << "Enter graph file name> ";
        getline(cin, filename);
    }else{
        filename = args[1];
    }
    if(argc < 3){
        string i;
        cout << "Do you want to printh all paths (Y/N)? ";
        getline(cin, i);
        must_print_paths = i == "Y";
    }else{
        must_print_paths = args[2] == "Y";
    }
    if(argc < 4){
        cout << "Enter K-mer> ";
        getline(cin, k_mer);
    }else{
        filename = args[3];
    }

    read_file(filename);

    visited = vector<int>(nodes.size(),0);

    for(int i = 0; i<nodes.size(); i++){
        if(visited[i] == 0){
            verify_aciclicity(i);
        }
    }

    int start, destination;
    start_destination(start,destination);

    if(must_print_paths){
        print_paths(start, destination);
    }

    cout << "k-mer " << k_mer <<  " appears " << k_mer_finder(k_mer) << " times";


    




    return 0;
}
