#include <iostream>
#include <stdlib.h>
using namespace std;

/*
사용 방법 
- 빌드한 실행 파일은 capsfile이라고 가정
- capsfile < "변환할 텍스트파일이름" > "변경할 텍스트파일이름"
- main 함수의 표준 입출력 리다이렉션을 통한 파일 변환
*/

int main()
{
  char data;
  long istate;
  long ostate;

  // EOF일때까지 cin.get으로 표준입력 수행
  while (!cin.eof())
  {
    data = cin.get();

    if (cin.fail())
    {
      istate = cin.rdstate();
      cerr << "istate 에러검출, 값: " << istate << endl;
    }

    // 변환 후 표준 출력
    cout.put((char)toupper(data));

    if (cout.fail())
    {
      ostate = cout.rdstate();
      cerr << "ostate 에러검출, 값: " << ostate << endl;
    }
  }

  return 0;
}