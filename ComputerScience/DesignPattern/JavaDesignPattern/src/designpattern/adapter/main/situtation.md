# Adapter Pattern 상황
* Banner
  * 이미 제공되어 있는 것
  * 특정 문자열에 대한 출력 기능 제공
    * showWithParen : 문자열 앞뒤에 괄호 문자를 붙여 출력 
    * showWithAster : 문자열 앞뒤에 * 문자를 붙여 출력
* Print
  * Banner 클래스와 비슷한 역할을 하는 인터페이스 
  * 특정 문자열을 출력하는 인터페이스
    * printWeak
    * printStrong
* Goal
  * Banner 클래스를 사용하여 Print 인터페이스를 충족시키는 클래스 PrintBanner 구현
    * Print.printWeak 메서드는 Banner.showWithParen 메서드에 대응
    * Print.printStrong 메서드는 Banner.showWithAster 메서드에 대응