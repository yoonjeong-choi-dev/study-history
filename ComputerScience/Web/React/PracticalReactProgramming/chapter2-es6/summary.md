# Chapter 2. ES6+를 품은 자바스크립트

## Section 1. 변수를 정의하는 새로운 방법 : const, let

### var의 문제점
* 문제 1 : 스코프 제약
  * 정의된 변수가 함수 스코프를 가짐
  * 함수 내 코드 블럭(for/while/if etc)에서의 스코프는 가지지 않음
* 문제 2 : 호이스팅
  * 호이스팅 : 정의된 변수는 그 변수가 속한 스코프의 최상단으로 끌어올려짐
  * example :
    ```
    console.log(variable); // undefined : 정의되지 않은 변수에 대해 에러 발생 x
    var variable = 123;
    ```
  * 호이스팅은 직관적이지 않고, 일반적인 프로그래밍 언어에서 찾아보기 힘든 성질
* 기타 문제
  * 정의된 변수 재정의 가능
    * ```
        var variable = 123;
        var variable = 12;
      ```
    * 메모리가 할당된 변수에 대해서 다시 정의가 가능한 직관적이지 않은 방식이 허용
  * 상수 할당 불가능


### const/let의 특징
* 블록 스코프
  * var과 다르게 블록 스코프를 가짐
  * 일반적인 프로그래밍 언어와 사용되는 스코프 개념
* const/let의 호이스팅
  * 변수 정의 전에 해당 변수를 사용하려 하면 참조 에러 발생(var과 다른점)
  * 다음과 같은 상황에서 에러 발생
    ```
    const foo = 1;
    {
      console.log(foo); // 참조 에러
      const foo = 3;
    }
    ```
* const 변수는 재할당 불가능
  * 재할당이 불가능한 변수는 프로그래밍의 복잡도를 낮추므로 되도록 const 변수 사용하는 것이 좋음
  * 변수가 객체인 경우 내부 속성값은 수정이 가능
    * 내부 속성값을 수정 불가능하게 만드는 외부 패키지
      * immer.js, immutable.js
      * 객체 내부를 수정하려 하면, 새로운 객체를 생성하는 패키지
    * 수정만을 차단하기 위해서는 js의 내장 함수 이용
      * Object.preventExtesions
      * Object.seal
      * Object.freeze



## Section 2. 객체와 배열의 사용성 개선
* 단축 속성명 및 계산된 속성명을 이용하여 쉽게 객체/배열을 생성/수정 가능
* 전개 연산자와 비구조화 할당을 이용하여 객체/배열의 속성값을 쉽게 추출 가능

### 객체/배열을 간편하게 생성/수정하는 방법
* 단축 속성명(shorthand property name)
  * 객체 리터널 코드를 간편하게 작성하기 위할 목적으로 만들어진 문법
  * 2가지 특징
    * 객체의 속성값을 이미 정의한 변수 이름만 적어주면, 속성명이 변수 이름과 같아짐
    * 객체의 속성값이 함수일때 function 키워드 없이 적어주면, 함수 이름이 속성명과 같아짐
  * example
    ```
    const name = 'yj';
    const myObj = {
      age: 21,
      name,
      getName() { return this.name }
    }
    console.log(myObj.name);      // yj
    console.log(myObj.getName()); // yj
    ```
* 계산된 속성명(computed property name)
  * 객체의 속성명을 동적으로 결정하기 위한 문법
  * 리액트의 form tag의 입력값들의 상태값을 관리 할 때 유용
  * example
    ```
    function makeObj(key, value) {
      return { [key]: value };
    }
    ```

### 객체/배열의 속성값을 간편하게 가져오기
* 전개 연산자(spread)
  * 배열이나 객체의 모든 속성을 풀어 놓을 때 사용
  * 새로운 객체나 배열 생성 예제
    ```
    const arr = [1, 2, 3];
    const obj = { name: 'yj', age: 30 };
    const arrCopy = [...arr];
    const objCopy = [...obj];
    ```
  * 리액트 상태 관리(useState)의 불편성을 유지하면서 상태 변경에 유용
    * example
      ```
      const [info, setInfo] = useState({name: null, age: null});
      setInfo({...info, name: 'yj', age: 30});
      ```
    * 위 예제에서 중복된 속성명 사용이 가능한 것은 ES6 부터
* 배열 비구조화(array destructing)
  * 배열의 여러 속성값을 변수로 쉽게 할당 가능
    ```
    const point = [1, 2];
    const [x, y] = point;
    ```
  * 두 변수의 swap을 간단하게 구현 가능
    ```
    let a =1, b= 2;
    [a, b] = [b, a];
    ```
  * 리액트의 useState 훅에서 자주 사용되는 문법
    ```
    const [state, setState] = useState('');
    ```
* 객체 비구조화(object destructing)
  * 객체의 여러 속성값을 변수로 쉽게 할당 가능
    ```
    const point = { x: 1, y:2 };
    const {x, y} = point;
    ```
  * 배열의 경우 변수 할당 시 배열 순서가 중요하지만, 객체의 경우 순서는 무의미
  * 배열의 경우 할당할 변수의 이름을 자유롭게 설정가능하지만, 객체의 경우 속성명을 그대로 사용해야 함
    * 별칭을 사용하여 속성명과 다른 변수 생성 가능
    * example
      ```
      const obj = { name: 'yj', age: 30};
      const {age: yjAge, name } = obj;
      console.log(yjAge); // yj
      ```
  * 중첩된 객체의 비구조화 예제
    ```
    const nested = { name: 'yj', career: { position: 'developer' } };
    const { name, career: {position: job }} = nested;
    console.log(name);  // yj
    console.log(job);   // developer
    console.log(career);  // 참조 에러
    ```


## Section 3. 강화된 함수의 기능
### 매개변수에 추가된 기능


### 함수를 정의하는 새로운 방법 : 화살표 함수



## Section 4. 비동기 프로그래밍(1) 프로미스
### 프로미스 이해


### 프로미스 활용


### 프로미스 사용 시 주의할 점



## Section 5. 비동기 프로그래밍(2) async/await
### async/await 이해


### async/await 활용



## Section 6. 템플릿 리터럴



## Section 7. 실행을 멈출 수 있는 제너레이터
### 제너레이터 이해


### 제너레이터 활용