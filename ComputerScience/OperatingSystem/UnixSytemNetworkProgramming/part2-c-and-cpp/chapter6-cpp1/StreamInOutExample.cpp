#include <iostream>
#include <string>

using namespace std;

int main()
{
  string inputData;
  int outputLine = 0;

  while (inputData != "quit")
  {
    cout << "데이터 입력(종료-quit): ";
    //cin >> inputData;
    getline(cin, inputData);
    cout << ++outputLine << ": " << inputData << endl;
  }

  return 0;
}