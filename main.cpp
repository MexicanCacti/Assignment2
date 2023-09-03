#include <iostream>
#include <vector>

using namespace std;

struct Data {
  int value = 0;
  bool direction = true; // true for <-- || false for -->
  Data(int);
};

Data::Data(int val) {
  this->value = val;
}

float Total(float); // function for finding total permutations, 25 too big to be represented using int, so used float
void get_Set(ostream&, vector<Data>); // prints the passed in permutation
int findLargestMobile(vector<Data>&); // finds largest mobile element k
void Johnson_Trotter(vector<Data>&, vector<vector<Data>>&);    // follows Johnson-Trotter algo to manipulate given vector, adds to list of permutations

int main() {
  float size = 3; // use numbers 1 to size
  vector<Data>Numbers;
  vector<vector<Data>>Permutations;

  for (int i = 1; i <= size; i++) { // initializes initial permutation
    Numbers.push_back(Data(i));
  }

  cout << "There are " << Total(size) << " Permutations of the set ";
  get_Set(cout, Numbers);
  cout << ":\n";
  Johnson_Trotter(Numbers, Permutations);
  
  return 0;
}

float Total(float size) {
  float Permutations = 1;
  while (size != 0) {
    Permutations = Permutations * size;
    size--;
  }
  return Permutations;
}

void get_Set(ostream& out, vector<Data> Numbers) {
  out << "{";
  for (int i = 0; i < Numbers.size() - 1; i++) {
    out << Numbers[i].value << ", ";
  }
  out << Numbers[Numbers.size() - 1].value << "}";
}

int findLargestMobile(vector<Data>& Numbers) {
  int largest = -1;        // if -1 returned, found all permutations
  int index = 1;          // start search at index 1 since special rule for index 0
  int next = index + 1;   // next points to element after index, when next is == size, we know index points to final element. Final element has special rules so need to do seperate from while loop
  
  if (!Numbers[0].direction) { // first element points right, compare with next element. If points left, can't be mobile
    if (Numbers[0].value > Numbers[index].value) {
      largest = 0;
    }
  }
  
  while (next != Numbers.size()) {
    if (Numbers[index].direction) {     // current element points left
      if (Numbers[index].value > Numbers[index - 1].value) {
        largest = index;
      }
    }
    else {                              // current element points right
      if (Numbers[index].value > Numbers[next].value) {
        largest = index;
      }
    }
    index++;
    next++;
  }
  if (Numbers[index].direction) {    // last element points left, compare with prev element. If points right, can't be mobile
    if (Numbers[index].value > Numbers[index - 1].value) {
      largest = index;
    }
  }
  return largest;
}

void Johnson_Trotter(vector<Data>& Numbers, vector<vector<Data>>& Permutations) {
  get_Set(cout, Numbers);
  cout << "\n";
  if (Numbers.size() == 1) { // single element contained in Numbers, all permutations just single element
    return;
  }
  int indexOfLargestMobile = 0;
  int valueOfLargestMobile = 0;
  while (true) {
    indexOfLargestMobile = findLargestMobile(Numbers);    // find largest mobile element
    cout << indexOfLargestMobile << endl;

    if (indexOfLargestMobile == -1) {                     // if return -1, found all permutations
      return;
    }
    valueOfLargestMobile = Numbers[indexOfLargestMobile].value; // store the value contained in the largest mobile element
    Data temp = Numbers[indexOfLargestMobile];                  // have to swap largest mobile element and what its pointing to, temp stores one of the objects while swapping

    // logic to manipulate Largest Mobile Element from algorithm goes here
    // as well as logic to reverse direction of values less that the largest mobile element
    
    Permutations.push_back(Numbers);
    get_Set(cout, Numbers);
    cout << "\n";
  }
  return;
}
