#include <unistd.h>

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <format>

#include "double_vector.h"

using namespace std;
class App {
 private:
  int c;
  int index_;
  string filename_;
  int argc_;
  char **argv_;
  bool c_flag = false;
  bool h_flag = false;
  bool i_flag = false;
  bool f_flag = false;
  double_vector dv;

 public:
  App(int argc, char *argv[]) {
    while ((c = getopt(argc, argv, "ihcf:")) != -1) {
      switch (c) {
        case 'i':
          i_flag = true;
          break;
        case 'h':
          h_flag = true;
          break;
        case 'c':
          c_flag = true;
          break;
        case 'f':
          f_flag = true;
          filename_ = optarg;
          break;
        case '?':
          if (optopt == 'f') {
            throw(runtime_error(
                "Error: -f flag requires a proceding filename\n"));
          }
      }
    }
    index_ = optind;
    argc_ = argc;
    argv_ = argv;
  }

  ~App() = default;

  void PrintHelp() {
    cout << "-h: Help Flag, Displays the help\n";
    cout << "-f: File Flag, Requires a filenam, used when wanting to create a "
            "double_vector from a starting file\n";
    cout << "-i: Input Flag, Prompts the user to input numbers to be added to "
            "the vector\n";
    cout << "-c: Command Line Flag, Creates a double_vector from the arguments "
            "passed from the command line by the user\n";
  }

  int GetInputFromUser() {
    double number;
    while (true) {
      cout << "Enter a number (or 'q' to quit): ";
      if (cin.peek() == 'q') {
        break;
      }
      cin >> number;
      if (cin.fail()) {
        cin.clear();
        string bad_data;
        cin >> bad_data;
        cerr << "Invalid Data Entry: " << bad_data << "\n";
        return -1;
      }
      dv.push_back(number);
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return 1;
  }

  /**
   * Credit GeeksForGeeks - https://www.geeksforgeeks.org/bubble-sort-algorithm/
   */
  void BubbleSort() {
    size_t n = dv.size();
    bool swapped;

    for (size_t i = 0; i < n; i++) {
      swapped = false;
      for (size_t j = 0; j < n - i - 1; j++) {
        if (dv[j] > dv[j + 1]) {
          swap(dv[j], dv[j + 1]);
          swapped = true;
        }
      }
      if (!swapped) break;
    }
  }

  void ArgsToVector() {
    for (int i = index_; i < argc_; i++) {
      dv.push_back(stod(argv_[i]));
    }
  }

  void ParseFile() {
    ifstream file_in(filename_);
    if (!file_in) {
      throw(runtime_error(format("Error: \"{}\" is not a valid filename\n", filename_)));
    }
    string line;
    while (getline(file_in, line)) {
      string value;
      stringstream stream(line);
      while (getline(stream, value, ',')) {
        try{
          double num = stod(value);
          dv.push_back(num);
        }catch(const exception& e){
          continue;
        }
      }
    }
  }

  void PrintVector() {
    for (double_vector::iterator iter = dv.begin(); iter != dv.end(); ++iter) {
      cout << *iter << " ";
    }
    cout << "\n";
  }

  double Average() {
    double sum = 0;
    for (double_vector::iterator iter = dv.begin(); iter != dv.end(); ++iter) {
      sum += *iter;
    }
    return sum / dv.size();
  }

  void Display() {
    cout << "Data: ";
    PrintVector();
    cout << "\tAverage: " << Average() << "\n";
    cout << "\tMaximum: " << dv.back() << "\n";
    cout << "\tMinimum: " << dv.front() << "\n";
  }

  int Run() {
    if (h_flag) {
      PrintHelp();
      return 1;
    }
    if (f_flag) {
      ParseFile();
    }
    if (i_flag) {
      if (GetInputFromUser() == -1) return -1;
    }
    if (c_flag) {
      ArgsToVector();
    }
    BubbleSort();
    cout << "\n";
    Display();
    return 1;
  }

};

int main(int argc, char *argv[]) {
  App app(argc, argv);
  app.Run();
}