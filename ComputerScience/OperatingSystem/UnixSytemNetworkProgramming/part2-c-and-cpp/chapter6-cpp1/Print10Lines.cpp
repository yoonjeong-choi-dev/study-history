#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "파일명을 입력하세요" << endl;
    exit(1);
  }

  // 파일을 읽기 위한 ifstream 객체 생성
  ifstream inputFile(argv[1]);

  if (!inputFile.fail())
  {
    char lineData[256];
    char lineNum = 0;

    // getline을 이용하여 한줄씩 읽는다
    while (!inputFile.eof())
    {
      inputFile.getline(lineData, sizeof(lineData));

      if (inputFile.good())
      {
        cout << (int)lineNum << "\t" << lineData << endl;

        lineNum++;

        // 10행마다 사용자 입력을 기다린다
        if (lineNum % 10 == 0)
        {
          cout << "엔터를 치세요" << endl;
          cin.get();
        }
      }
    }
  }
  else
  {
    cerr << "파일 열기 실패" << endl;
    exit(1);
  }

  inputFile.close();

  return 0;
}