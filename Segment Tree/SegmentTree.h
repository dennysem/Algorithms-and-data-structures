#include <vector>



template <typename Container, typename action, typename returnedType, typename dataType > // Some container, such as vector, list.
class SegmentTree {
public:
  
  SegmentTree (Container & container, size_t size, action act) {
    if (size == 0) {
      return;
    }
    act_ = act;
    containerSize_ = size;
    tree_.resize(4 * size);
    build(container, 1, 0, size - 1);
  }

  SegmentTree(SegmentTree<std::vector<int>, action, int, int> & st) {
    tree_ = st.tree_;
    containerSize_ = st.containerSize_;
    act_ = st.act_;
  }

  void operator=(SegmentTree<std::vector<int>, action, int, int> & st) {
    tree_ = st.tree_;
    containerSize_ = st.containerSize_;
    act_ = st.act_;
  }

  returnedType Query(int l, int r) {
    if (l < 0 || r > containerSize_ - 1) {
      return NULL;
    }
    return QueryRecurse(1, 0, containerSize_ - 1, l , r);
  }

  void Update(int pos, dataType val) {
    updateRecurse(1, 0, containerSize_ - 1, pos, val);
  }

private:
  std::vector<returnedType> tree_;
  size_t containerSize_;
  action act_;

  void build (Container & container, int v, int tl, int tr) {
    if (tl == tr)
      tree_[v] = container[tl];
    else {
      int tm = (tl + tr) / 2;
      build(container, v * 2, tl, tm);
      build(container, v * 2 + 1, tm + 1, tr);
      tree_[v] = act_.accept(tree_[2 * v], tree_[2 * v + 1]);
    }
  }
    
  returnedType QueryRecurse(int v, int tl, int tr, int l, int r) {
    if (l > r)
      return 0;
    if (l == tl && r == tr)
      return tree_[v];
    int tm = (tl + tr) / 2;
    return act_.accept(QueryRecurse(v * 2, tl, tm, l, min(r, tm)), QueryRecurse(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  void updateRecurse(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
      tree_[v] = new_val;
    else {
      int tm = (tl + tr) / 2;
      if (pos <= tm)
        updateRecurse(v * 2, tl, tm, pos, new_val);
      else
        updateRecurse(v * 2 + 1, tm + 1, tr, pos, new_val);
      tree_[v] = act_.accept(tree_[v * 2], tree_[v * 2 + 1]);
    }
  }

  int min(int a, int b) {
    if (a > b) {
      return b;
    }
    return a;
  }

  int max(int a, int b) {
    if (a < b) {
      return b;
    }
    return a;
  }
};