#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

int main()
{
  //graph<char, int> a;

  //a.AddVertex('C');
  //a.AddVertex('D');
  //a.AddVertex('F');
  //a.AddVertex('A');
  //a.AddVertex('B');
  //a.AddVertex('E');
  //a.AddVertex('G');
  //a.AddVertex('H');

  //a.AddEdge('A', 'B', 1);
  //a.AddEdge('E', 'F', 1);
  //a.AddEdge('E', 'A', 1);
  //a.AddEdge('B', 'E', 1);
  //a.AddEdge('B', 'F', 1);
  //a.AddEdge('B', 'C', 1);
  //a.AddEdge('G', 'F', 1);
  //a.AddEdge('F', 'G', 1);
  //a.AddEdge('C', 'G', 1);
  //a.AddEdge('C', 'D', 1);
  //a.AddEdge('D', 'C', 1);
  //a.AddEdge('D', 'H', 1);
  //a.AddEdge('G', 'H', 1);



  //int i = 0;
  //for (auto it = a.begin_bfs('A'); it != a.end_bfs(); ++it)
  //  ++i;
  //for (auto it = a.begin_dfs('A'); it != a.end_dfs(); ++it)
  //  ++i;

  //graph<int, int> a;

  //a.AddVertex(1);
  //a.AddVertex(2);
  //a.AddVertex(3);
  //a.AddVertex(4);
  //a.AddVertex(5);
  //a.AddVertex(6);
  //a.AddVertex(7);
  //a.AddVertex(8);
  //a.AddVertex(9);

  //a.AddEdge(1, 2, 1);
  //a.AddEdge(1, 6, 1);
  //a.AddEdge(2, 4, 1);
  //a.AddEdge(2, 6, 1);
  //a.AddEdge(3, 4, 1);
  //a.AddEdge(3, 5, 1);
  //a.AddEdge(3, 8, 1);
  //a.AddEdge(3, 9, 1);
  //a.AddEdge(4, 7, 1);
  //a.AddEdge(4, 1, 1);
  //a.AddEdge(5, 8, 1);
  //a.AddEdge(5, 9, 1);
  //a.AddEdge(6, 1, 1);t
  //a.AddEdge(6, 7, 1);
  //a.AddEdge(6, 4, 1);
  //a.AddEdge(7, 1, 1);
  //a.AddEdge(8, 5, 1);
  //a.AddEdge(9, 8, 1); 
  //a.AddEdge(8, 3, 1);

  //
  //auto res = a.Kosaraju();
  //auto res2 = a.Tarjan();
  //for (size_t i = 0; i < res.size(); ++i)
  //{
  //  std::sort(res[i].begin(), res[i].end());
  //  std::sort(res2[i].begin(), res2[i].end());
  //}
  //std::sort(res.begin(), res.end());
  //std::sort(res2.begin(), res2.end());

 /* freopen("stdin.txt", "r", stdin);
  freopen("stdout.txt", "w", stdout);*/

  //graph<int, int> a;

  /*int m, n, r;
  std::cin >> r;
  std::cin >> m >> n;
  for (int i = 0; i < m; ++i)
    a.AddVertex(i);
  for (int i = 0; i < n; ++i){
    int w1, w2, w;
    std::cin >> w1 >> w2 >> w;
    a.AddEdge(w1, w2, w);
  }
  std::vector< std::vector< int> > res;
  if (r == 0)
    res = a.Tarjan();
  else
    res = a.Kosaraju();
  
  std::cout << res.size() << std::endl;
  for (auto it = res.begin(); it != res.end(); ++it) {
    for (auto jt = it->begin(); jt != it->end(); ++jt)
      std::cout << *jt << " ";
    std::cout << std::endl; 
  }*/
  /*fclose(stdin);
  fclose(stdout);*/

  /*a.AddVertex('A');
  a.AddVertex('B');
  a.AddVertex('C');
  a.AddVertex('D');


  a.AddUndirectedEdge('A', 'B', 2);
  a.AddUndirectedEdge('A', 'C', 3);
  a.AddUndirectedEdge('A', 'D', 100);
  a.AddUndirectedEdge('B', 'D', 4);
  auto res = a.Prim();
  auto res2 = a.Kruskal();*/

  graph<char, int> a;

  a.AddVertex('C');
  a.AddVertex('D');
  a.AddVertex('F');
  a.AddVertex('A');
  a.AddVertex('B');
  a.AddVertex('E');
  a.AddVertex('G');
  a.AddVertex('H');

  a.AddEdge('A', 'B', 4);
  a.AddEdge('B', 'C', 2);
  a.AddEdge('C', 'D', 6);
  a.AddEdge('A', 'E', 1);
  a.AddEdge('E', 'C', 3);
  a.AddEdge('A', 'F', 4);
  a.AddEdge('F', 'G', 2);
  a.AddEdge('G', 'D', 1);
  a.AddEdge('F', 'E', 7);
  a.AddEdge('G', 'C', 1);
  int maxFlow = a.EdmondsKarp('A', 'D');
  return 0;
}
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      


