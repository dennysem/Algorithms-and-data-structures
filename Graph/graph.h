#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <memory>
#include <stack>
#include <algorithm>

template <typename Vtype, typename Etype>
class edge{
private:
  Vtype a_, b_;
  Etype price_;
public:
  edge(Vtype a, Vtype b, Etype price): a_(a), b_(b), price_(price) {}

  Vtype getA() const {
    return a_;
  }

  Vtype getB() const {
    return b_;
  }

  Etype price() const {
    return price_;
  }

  friend bool operator<(edge<Vtype, Etype> a, edge<Vtype, Etype> b) {
    return (a.price() < b.price());
  }

};

template <typename Vtype, typename Etype>
class graph{
public:
  graph():size_(0) {}
  
  graph(graph<Vtype, Etype> & g) : size_(g.size_), listOfAdj_(g.listOfAdj_) {}

  template <typename Vtype, typename Etype>
  class vertex{
  public:
    vertex(Vtype val) : val_(val) {}
    friend class graph<Vtype, Etype>;
  private:
    Vtype val_;
  };

  void operator=(graph<Vtype, Etype> & g) {
    if (this == &g)
      return;
    listOfAdj_ = std::vector <std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >();
    size_ = 0; 
    for (auto it = g.listOfAdj_.begin(); it != g.listOfAdj_.end(); ++it) {
      AddVertex(it->first.val_);
      ++size_;
    }
    for (auto it = g.listOfAdj_.begin(); it != g.listOfAdj_.end(); ++it) {
      for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
        AddEdge(it->first.val_, jt->first->val_, jt->second);
    }
  }

  bool AddEdge(Vtype a, Vtype b, Etype price) {
    auto ita = listOfAdj_.begin();
    while ((ita != listOfAdj_.end()) && (ita->first.val_ != a))
      ++ita;
    if (ita == listOfAdj_.end())
      return false;
    auto itb = listOfAdj_.begin();
    while ((itb != listOfAdj_.end()) && (itb->first.val_ != b))
      ++itb;
    if (itb == listOfAdj_.end())
      return false;
    ita->second.push_back(std::make_pair(&itb->first, price));
    return true;
  }

  bool AddUndirectedEdge(Vtype a, Vtype b, Etype price) {
    return (AddEdge(a, b, price) && AddEdge(b, a, price));
  }

  void AddVertex(Vtype v) {
    listOfAdj_.push_back(std::make_pair(vertex<Vtype, Etype>(v), std::list< std::pair< vertex<Vtype, Etype>*, Etype > >()));
    ++size_;
  }

  std::unordered_map<Vtype, Etype> BellmanFord(Vtype a)
  {
    std::unordered_map< Vtype, Etype> res;
    res.insert(std::make_pair(a, 0));
    for (size_t i = 0; i < size_ - 1; ++i) {
      for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it)//relax all edges
      for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
        if (res.find(it->first.val_) != res.end())
        if (res.find(jt->first->val_) != res.end()) {
          if (res[it->first.val_] + jt->second < res[jt->first->val_])
            res[jt->first->val_] = res[it->first.val_] + jt->second;
          else {}
        }
        else
          res.insert(std::make_pair(jt->first->val_, res[it->first.val_] + jt->second));
    }
    for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it)//relax all edges
    for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
    if (res.find(it->first.val_) != res.end())
    if (res.find(jt->first->val_) != res.end()) {
      if (res[it->first.val_] + jt->second < res[jt->first->val_])
        return std::unordered_map<Vtype, Etype>();
    }
    return res;
  }
  
  std::unordered_map<Vtype, Etype> dijkstra(Vtype a) {
    std::unordered_map<Vtype, bool> used;
    for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it)
      used.insert(std::make_pair(it->first.val_, false));
    used[a] = true;
    std::unordered_map<Vtype, Etype> res;
    res.insert(std::make_pair(a, 0));
    std::map<Etype, std::vector <std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >::iterator> queue;
    auto iter = listOfAdj_.begin();
    while ((iter != listOfAdj_.end()) && (iter->first.val_ != a))
      ++iter;
    if (iter != listOfAdj_.end())
      queue.insert(std::make_pair(0, iter));
    else
      return std::unordered_map<Vtype, Etype>();
    while (queue.size() != 0) {
      auto v = queue.begin()->second;
      Etype vLength = res[v->first.val_];
      for (auto it = v->second.begin(); it != v->second.end(); ++it) {
        Vtype newVertex = it->first->val_;
        Etype curEdgeLength = it->second;
        if (used[newVertex] == true) {//grey vertex
          if (curEdgeLength + vLength < res[newVertex])//relax
            res[newVertex] = curEdgeLength + vLength;
        }
        if (used[newVertex] == false) {//white vertex
          res.insert(std::make_pair(newVertex, vLength + curEdgeLength));
          iter = listOfAdj_.begin();
          while ((iter != listOfAdj_.end()) && (iter->first.val_ != newVertex))
            ++iter;
          if (iter != listOfAdj_.end())
            queue.insert(std::make_pair(vLength + curEdgeLength,iter));
          else
            return std::unordered_map<Vtype, Etype>();
          used[newVertex] = true;//paint grey
        }
        used.erase(v->first.val_);//paint black
      }
      queue.erase(queue.begin());
    }
    return res;
  }

  std::vector<edge<Vtype, Etype> > Prim() {
    std::unordered_set<Vtype> includedVertexes;
    std::unordered_set<Vtype> outVertexes;
    std::vector<edge <Vtype, Etype> > result;
    std::set<edge<Vtype, Etype> > curEdges;
    for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it) {
      outVertexes.insert(it->first.val_);
    }
    Vtype curVertex = *outVertexes.begin();
    includedVertexes.insert(*outVertexes.begin());
    outVertexes.erase(outVertexes.begin());
    while (includedVertexes.size() != size_) {
      auto curVertexInList = findInListOfAdj(curVertex);
      for (auto it = curVertexInList->second.begin(); it != curVertexInList->second.end(); ++it) {
        if (includedVertexes.find(it->first->val_) != includedVertexes.end()) {//cycle
          continue;
        }
        curEdges.insert(edge<Vtype, Etype>(curVertex, it->first->val_, it->second));

      }
      result.push_back(*curEdges.begin());
      auto curEdge = *curEdges.begin();
      curVertex = curEdge.getB();
      includedVertexes.insert(curVertex);
      outVertexes.erase(curVertex);
      curEdges.erase(curEdges.begin());

    }
    return result;
  }

  std::vector<edge<Vtype, Etype> > Kruskal() {
    std::set<edge<Vtype, Etype> > sortedEdges;
    for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it) {
      for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
        sortedEdges.insert(edge<Vtype, Etype>(it->first.val_, jt->first->val_, jt->second));
      }
    }
    std::vector<edge<Vtype, Etype> > result;
    std::unordered_set<Vtype> includedVertexes;
    std::unordered_set<Vtype> outVertexes;
    auto sortedEdgesIterator = sortedEdges.begin();
    while (sortedEdgesIterator != sortedEdges.end() || result.size() != size_ - 1) {
      if (includedVertexes.find(sortedEdgesIterator->getA()) ==
        includedVertexes.end() ||
        includedVertexes.find(sortedEdgesIterator->getB()) ==
        includedVertexes.end()) {
        result.push_back(*sortedEdgesIterator);
        includedVertexes.insert(sortedEdgesIterator->getA());
        includedVertexes.insert(sortedEdgesIterator->getB());
      }
      ++sortedEdgesIterator;
    }
    if (result.size() == size_ - 1) {
      return result;
    }
    return std::vector<edge<Vtype, Etype> >();
  }
  

  std::list<Vtype> topoSort() {
    std::vector<bool> used(size_, false);
    std::list<Vtype> res;
    for (size_t i = 0; i < listOfAdj_.size(); ++i)
    if (used[i] == false)
      topoSortRecurs(i, used, res);
    return res;
  }

  void topoSortRecurs(int i, std::vector<bool> & used, std::list<Vtype> & res) {
    used[i] = true;
    for (auto it = listOfAdj_[i].second.begin(); it != listOfAdj_[i].second.end(); ++it)
    {
      auto newVertex = it->first->val_;
      int j = 0;
      while ((j != listOfAdj_.size()) && (listOfAdj_[j].first.val_ != newVertex))
        ++j;
      if ((j != listOfAdj_.size()) && (used[j] == false))
        topoSortRecurs(j, used, res);
    }
    res.push_front(listOfAdj_[i].first.val_);
  }

  void transp() {
    graph<Vtype, Etype> res;
    for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it)
      res.AddVertex(it->first.val_);//add all vertexes
    for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it)
    for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
      res.AddEdge(jt->first->val_, it->first.val_, jt->second);
    *this = res;
  }

  std::vector< std::vector<Vtype> > Kosaraju() {
    if (size_ == 0)
      return std::vector<std::vector<Vtype> >();
    std::stack<Vtype> searchOrder;
    std::unordered_set<Vtype> inSearchOrder;
    while (searchOrder.size() != size_) {//the first dfs
      auto it = listOfAdj_.begin();
      while (it != listOfAdj_.end() && inSearchOrder.find(it->first.val_) != inSearchOrder.end())
        ++it;
      if (inSearchOrder.find(it->first.val_) == inSearchOrder.end()) {//vertex is not in stack
        int returnedColor = 0;//operation "++it" returns color of pointed vertex, 0 - grey, 1 - black
        for (auto jt = this->begin_dfs(it->first.val_); jt != this->end_dfs(); returnedColor = ++jt)
        if (returnedColor == 1 && inSearchOrder.find(*jt) == inSearchOrder.end()) {
          searchOrder.push(*jt);
          inSearchOrder.insert(*jt);
        }
      }
    }
    graph<Vtype, Etype> transpGraph(*this);
    transpGraph.transp();
    std::vector< std::vector<Vtype> > res;
    int numOfComp = -1;//number of SCC
    while (!searchOrder.empty()) {//the second dfs on transp graph
      auto curVertex = searchOrder.top();
      searchOrder.pop();
      res.push_back(std::vector<Vtype>());
      ++numOfComp;
      int returnedColor = 0;//operation "++it" returns color of pointed vertex, 0 - grey, 1 - black
      for (auto it = transpGraph.begin_dfs(curVertex); it != transpGraph.end_dfs(); returnedColor = ++it)
      if ((returnedColor == 0) && inSearchOrder.find(*it) != inSearchOrder.end()) {
        res[numOfComp].push_back(*it);
        inSearchOrder.erase(*it);
      }
      while (!searchOrder.empty() && inSearchOrder.find(searchOrder.top()) == inSearchOrder.end())
        searchOrder.pop();
    }
    for (size_t i = 0; i < res.size(); ++i)//lets make order
      std::sort(res[i].begin(), res[i].end());
    std::sort(res.begin(), res.end());
    return res;
  }

  std::vector< std::vector<Vtype> > Tarjan() {
    int time = 0;
    std::unordered_map<Vtype, bool> visit;
    std::unordered_map<Vtype, int> lowlink;
    int components = 0;
    std::vector<std::vector<Vtype> > res;
    std::stack<Vtype> stack_tar;
    while (visit.size() != size_) {
      for (auto it = listOfAdj_.begin(); it != listOfAdj_.end(); ++it) {
        Vtype curVertex = it->first.val_;
        if (visit.find(curVertex) != visit.end())
          continue;
        int returnedColor = 0;
        for (auto dfs_it = begin_dfs(curVertex); dfs_it != end_dfs(); returnedColor = ++dfs_it) {
          if (visit.find(*dfs_it) != visit.end() && visit[*dfs_it] == true)//if vertex was in previus dfs
            continue;
          if (returnedColor == 0) {//grey vertex
            visit.insert(std::make_pair(*dfs_it, false));
            lowlink[*dfs_it] = time++;
            stack_tar.push(*dfs_it);
          }
          if (returnedColor == 1) { //black vertex
            int isRoot = 1;
            auto verInList = findInListOfAdj(*dfs_it);
            for (auto jt = verInList->second.begin(); jt != verInList->second.end(); ++jt)
            if (lowlink[*dfs_it] > lowlink[jt->first->val_]) {
               lowlink[*dfs_it] = lowlink[jt->first->val_];
               isRoot = 0;
             }
            if (isRoot == 1) {
              res.push_back(std::vector<Vtype>());
              while (true) {
                Vtype u = stack_tar.top();
                stack_tar.pop();
                res[components].push_back(u);
                visit[u] = true;
                lowlink[u] = size_ + 1;
                if (*dfs_it == u)
                  break;
              }
              ++components;
            }
          }
        }
      }
    }
    for (size_t i = 0; i < res.size(); ++i)//lets make order
      std::sort(res[i].begin(), res[i].end());
    std::sort(res.begin(), res.end());
    return res;
  }
  
  Etype EdmondsKarp(Vtype source, Vtype target) {
    graph<Vtype, Etype> gr = *this;
    std::unordered_map<Vtype, Vtype> path = gr.findPath(source, target);
    Etype maxFlow = 0;
    while (path.size() > 0) {
      maxFlow += gr.pushFlow(path, source, target);
      path = gr.findPath(source, target);
    }
    return maxFlow;
  }

  //////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  class bfs_iterator{
  public:
    bfs_iterator() {}

    bfs_iterator(graph<Vtype, Etype> & g) : graph_(&g) {}

    void operator++() {
      if (queue_.empty()) {
        *this = bfs_iterator();
        return;
      }
      auto cur = ptr_;
      for (auto it = cur->second.begin(); it != cur->second.end(); ++it) {
        Vtype newVertex = it->first->val_;
        if (color_.find(newVertex) == color_.end()) {
          queue_.push(graph_->findInListOfAdj(newVertex));
          color_[newVertex] = false;
        }
      }
      color_[cur->first.val_] = true;
      queue_.pop();
      if (!queue_.empty())
        ptr_ = queue_.front();
      else
        ptr_ = graph_->listOfAdj_.end();
    }

    bool operator!=(bfs_iterator a) {
      if (a.queue_.size() == 0)
      if (queue_.size() == 0)
        return false;
      else
        return true;
      return (ptr_ != a.ptr_);
    }

    Vtype operator*() {
      return ptr_->first.val_;
    }

    friend class graph<Vtype, Etype>;
  private:
    typename std::vector<std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >::iterator ptr_;
    std::map<Vtype, bool> color_;
    std::queue<typename std::vector<std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >::iterator> queue_;
    graph<Vtype, Etype> * graph_;
   
  };

  bfs_iterator begin_bfs(Vtype v) {
    auto it = listOfAdj_.begin();
    while ((it != listOfAdj_.end()) && (it->first.val_ != v))
      ++it;
    if (it == listOfAdj_.end())
      return bfs_iterator();
    bfs_iterator res(*this);
    res.ptr_ = it;
    res.color_.insert(std::make_pair(v, false));
    res.queue_.push(it);
    return res; 
  }

  bfs_iterator end_bfs() {
    return bfs_iterator();
  }

  /////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////

  class dfs_iterator{
  public:
    dfs_iterator() {}

    dfs_iterator(graph<Vtype, Etype> & g) :graph_(&g) {}

    int operator++() {// returned value : 0 - grey , 1 - black
     
      if (color_[ptr_->first.val_] == true) {//black vertex
        stack_.pop();
        if (!stack_.empty())
          ptr_ = stack_.top();
        else
          ptr_ = graph_->listOfAdj_.end();
      }
      if (stack_.empty()) {
        *this = dfs_iterator();
        return 1;
      }
      auto cur = ptr_;
      int numOfNewVertex = 0;
      for (auto it = cur->second.begin(); it != cur->second.end() && numOfNewVertex == 0; ++it) {
        Vtype newVertex = it->first->val_;
        if (color_.find(newVertex) == color_.end()) {
          auto newPtr = graph_->findInListOfAdj(newVertex);
          stack_.push(newPtr);
          color_[newVertex] = false;
          ptr_ = newPtr;
          return 0;//return grey
        }
      }
      color_[ptr_->first.val_] = true;
      return 1;//return black
    }
    
    bool operator!=(dfs_iterator a) {
      if (a.stack_.size() == 0)
      if (stack_.size() == 0)
        return false;
      else
        return true;
      return (ptr_ != a.ptr_);
    }

    Vtype operator*() {
      return ptr_->first.val_;
    }

    friend class graph<Vtype, Etype>;
  private:
    typename std::vector<std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >::iterator ptr_;
    std::map<Vtype, bool> color_;
    std::stack<typename std::vector<std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >::iterator> stack_;
    graph<Vtype, Etype> * graph_;
  };

  dfs_iterator begin_dfs(Vtype v) {
    auto it = listOfAdj_.begin();
    while ((it != listOfAdj_.end()) && (it->first.val_ != v))
      ++it;
    if (it == listOfAdj_.end())
      return dfs_iterator();
    dfs_iterator res(*this);
    res.ptr_ = it;
    res.color_.insert(std::make_pair(v, false));
    res.stack_.push(it);
    return res;
  }

  dfs_iterator end_dfs() {
    return dfs_iterator();
  }



  friend class graph<Vtype, Etype>::bfs_iterator;
private:
  std::vector <std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >  listOfAdj_;
  size_t size_;

  typename std::vector<std::pair< vertex<Vtype, Etype>, std::list< std::pair< vertex<Vtype, Etype>*, Etype> > > >::iterator findInListOfAdj(Vtype v) {
    auto it = listOfAdj_.begin();
    while ((it != listOfAdj_.end()) && (it->first.val_ != v)) {
      ++it;
    }
    return it;
  }

  Etype getWeight(Vtype a, Vtype b) {
    auto aIt = findInListOfAdj(a);
    for (auto it = aIt->second.begin(); it != aIt->second.end(); ++it) {
      if (it->first->val_ == b) {
        return it->second;
      }
    }
    return NULL;
  }

  void changeWeight(Vtype a, Vtype b, Etype newValue) {
    auto aIt = findInListOfAdj(a);
    for (auto it = aIt->second.begin(); it != aIt->second.end(); ++it) {
      if (it->first->val_ == b) {
        it->second = newValue;
      }
    }
  }

  std::unordered_map<Vtype, Vtype> findPath(Vtype source, Vtype target) {
    std::queue<Vtype> q;
    q.push(source);
    std::unordered_map<Vtype, Vtype> path;
    while (!q.empty())
    {
      Vtype cur = q.front();
      q.pop();
      auto curInList = findInListOfAdj(cur);
      for (auto it = curInList->second.begin(); it != curInList->second.end(); ++it) {
        Vtype newVertex = it->first->val_;
        if (it->second > 0) { //increasing path exists
          if (newVertex == target) {
            path[target] = cur;
            return path;
          }
          if (path.find(newVertex) == path.end()) { //white vertex
            q.push(newVertex);
            path[newVertex] = cur;
          }
        }
      }
    }
    return std::unordered_map<Vtype, Vtype>();
  }

  Etype pushFlow(std::unordered_map<Vtype, Vtype> path, Vtype source, Vtype target) {
    Vtype cur = target;;
    Etype minWeightInPath = getWeight(path[cur], cur);
    while (cur != source)
    {
      minWeightInPath = std::min(minWeightInPath, getWeight(path[cur], cur));
      cur = path[cur];
    }
    cur = target;
    while (cur != source)
    {
      Vtype prev = path[cur];
      changeWeight(prev, cur, getWeight(prev, cur) - minWeightInPath);
      cur = prev;
    }
    return minWeightInPath;
  }
};





