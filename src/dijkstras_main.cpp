#include "dijkstras.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    Graph G;
    string filename = "src/small.txt";

    try {
        file_to_graph(filename, G);
                
        int source = 0;
        vector<int> previous;
        
        vector<int> distances = dijkstra_shortest_path(G, source, previous);
        for (int i = 0; i < G.numVertices; ++i) {
            vector<int> path = extract_shortest_path(distances, previous, i);
            
            if (i != source) {
                print_path(path, distances[i]);
            }
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}