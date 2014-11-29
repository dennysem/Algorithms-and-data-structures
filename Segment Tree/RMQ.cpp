#include "SegmentTree.h" 
#include <vector>
#include <iostream>
#include <string>

std::vector<std::string> split(std::string s, char a);
int toInt(std::string s);

struct sum {
  static int accept(int a, int b) {
    return a + b;
  }
};

struct max {
  static int accept(int a, int b) {
    if (a < b) {
      return b;
    }
    return a;
  }
};

struct min {
  static int accept(int a, int b) {
    if (a < b) {
      return a;
    }
    return b;
  }
};


int main() {
  std::vector<int> arr;

  SegmentTree<std::vector<int>, sum, int, int> stsum(arr, arr.size(), sum());
  SegmentTree<std::vector<int>, max, int, int> stmax(arr, arr.size(), max());
  SegmentTree<std::vector<int>, min, int, int> stmin(arr, arr.size(), min());

  std::string s;
  while (true) {
    std::getline(std::cin, s);
    std::vector<std::string> cmd = split(s, ' ');
    if (cmd[0] == "UPDATE") {
      for (size_t i = 1; i < cmd.size(); ++i) {
        arr.push_back(toInt(cmd[i]));
      }
      stsum = SegmentTree<std::vector<int>, sum, int, int> (arr, arr.size(), sum());
      stmax = SegmentTree<std::vector<int>, max, int, int> (arr, arr.size(), max());
      stmin = SegmentTree<std::vector<int>, min, int, int> (arr, arr.size(), min());
    }
    else if (cmd[0] == "SET") {
      int index = toInt(cmd[1]);
      int value = toInt(cmd[2]);
      stsum.Update(index, value);
      stmax.Update(index, value);
      stmin.Update(index, value);
    }
    else if (cmd[1] == "MAX") {
      int left = toInt(cmd[2]);
      int right = toInt(cmd[3]);
      std::cout << stmax.Query(left, right);
    }
    else if (cmd[1] == "MIN") {
      int left = toInt(cmd[2]);
      int right = toInt(cmd[3]);
      std::cout << stmin.Query(left, right);
    }
    else if (cmd[1] == "SUM") {
      int left = toInt(cmd[2]);
      int right = toInt(cmd[3]);
      std::cout << stsum.Query(left, right);
    }
    std::cout << std::endl;
  }
    return 0; 
}
  



std::vector<std::string> split(std::string s, char a) {
    std::vector<std::string> result;
    std::string newString;
    for (size_t i = 0; i < s.length(); ++i) {
      if (s[i] == a) {
        result.push_back(newString);
        newString.clear();
      }
      else {
        newString.push_back(s[i]);
      }
    }
    if (newString.size() != 0) {
      result.push_back(newString);
    }
    return result;
  }

int toInt(std::string s) {
  int result = 0;
  int count = 1;
  for (int i = s.size() - 1; i >= 0; --i) {
    if (s[i] == '-') {
      result *= -1;
    }
    else {
      result += (s[i] - '0') * count;
      count *= 10;
    }
  }
  return result;
}