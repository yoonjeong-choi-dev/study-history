#include <iostream>

using namespace std;

/*
- 빌드한 실행 파일은 addlinefile이라고 가정
- addlinefile이라고 < "변환할 텍스트파일이름" > "변경할 텍스트파일이름"
- main 함수의 표준 입출력 리다이렉션을 통한 파일 변환
*/

int main()
{
  char buf[256];
  long istate;
  int line_number = 0;

  // EOF일때까지 cin.getline() 수행 
  while(!cin.eof())
  {
    cin.getline(buf, sizeof(buf));
    
    if (cin.fail())
    {
      istate = cin.rdstate();
      cerr << "istate 에러검출, 값: " << istate << endl;
    }
    else
    {
      line_number++;
      cout << line_number << '\t';
      cout << buf << endl;
    }
  }

  return 0;
}