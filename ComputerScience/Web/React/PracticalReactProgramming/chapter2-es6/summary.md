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
* 매개변수 기본값
  * 일반적인 프로그래밍 언어에서 지원하던 기능
  ```
  function func(a = 1) {
    console.log(a);
  }
  func();   // 1
  ```
  * 기본 값으로 함수 호출을 가능 i.e 입력값이 undefined인 경우에만 함수가 호출
  ```
  function getDefault() {
    return 1;
  }
  function func(a = getDefault()) {
    console.log(a);
  }
  func();   // 1
  ```
* 나머지 매개변수(rest parameter)
  * 입력된 인수 중에 정의된 매개 변수를 제외한 나머지 변수들을 배열로 만들어줌
  ```
  function print(a, ...rest) {
    console.log(a, rest);
  }
  print(1, 2, 3); // {a: 1, rest: [2, 3]}
  ```
  * ES5에서는 `argument` 키워드가 비슷한 역할
* 명명된 매개변수(named parameter)
  * 객체 비구조화를 이용하여 구현 i.e 매개변수들로 구성된 객체를 함수의 인자로 넘김
  * 함수 호출 시, 매개변수의 이름과 값을 동시에 적을 수 있음
  * example
  ```
  // function prototype : clipValue(numbers, greaterThan, lessThan)
  const arr = [1, 2, 3, 4, 5];
  const min = 2;
  const max = 1;
  const minClip = clipValue({numbers: arr, lessThan: min});
  const maxClip = clipValue({numbers: arr, greaterThan: max});
  ```
  * 고려할 점
    * 착각 : 함수 호출 시, 매번 객체가 생성되어 비효율
    * 팩트 : JS 엔진이 최적화를 통해 객체를 새롭게 생성 X

### 함수를 정의하는 새로운 방법 : 화살표 함수
* 화살표 함수를 정의하는 방법
  * 중괄호를 사용하지 않으면 오른쪽의 계산 결과가 반환
    ```
    const add = (a, b) => a+b;
    console.log(add(1, 2));   //2
    ```
  * 매개 변수가 하나인 경우, 왼쪽 소괄호 생략 가능
    ```
    const plusOne = a => a+1;
    console.log(plusOne(2)); //3
    ```
  * 함수 본문이 여러 줄인 경우 중괄호로 묶어서 사용
* 일반적인 함수(function 키워드)와 다른점
  * this와 arguments가 바인딩 되지 않음
    * 화살표 함수 안에서 참조하는 this와 argments는 자신을 감싸는 가장 가까운 일반 함수 참조
    * 화살표 함수에서 arguments가 필요하면 나머지 매개변수(rest argument) 사용
  * 요약
    * 일반 함수는 기본적으로 this가 window 객체를 참조
    * 화살표 함수는 상위 함수의 this를 참조
* 일반 함수의 this 바인딩에서 발생하는 문제
  * 일반 함수는 this가 호출 시점에 사용된 객체에 바인딩
    ```
      const obj = {
        value: 1,
        // increase 함수는 일반 함수여서 this는 obj로 바인딩
        increase() {
          this.value++; 
        }
      };

      obj.increase();
      console.log(obj.value); // 2

      const increase = obj.increase;  
      increase(); // 객체 없이 호출하는 경우, 전역 객체(현재는 window)에 바인딩
      console.log(obj.value); // 2
    ```
  * setInterval의 콜백에서의 bind
    * setInterval은 window 객체의 메서드 => this는 window를 가리킴
    * 콜백을 일반 함수가 아닌 화살표 함수를 사용함으로써, this의 컨텍스트 유지 가능
    * example
      ```
      function somethingWrong() {
        this.value = 1;
        setInterval(function callback() {
          this.value++;   // this === window
        }, 1000);
      }

      function somethingRight() {
        this.value =1;
        setInterval(() => {
          this.value++; // this === somethingRight
        }, 1000);
      }

      const wrong = new somethingWrong();
      const right = new somethingRight();
      setInterval(()=>{
        console.log(wrong.value);   // 1 -> 1 -> 1 -> 1 ..
        console.log(right.value);   // 2 -> 3 -> 4 -> 5 ..
      }, 1000)
      ```
      
## Section 4. 비동기 프로그래밍(1) 프로미스
* 프로미스 
  * 비동기 상태를 값으로 다룰 수 있는 객체
  * 비동기 프로그래밍을 동기 프로그래밍 방식으로 코딩 가능
* 프로미스 보급전에는 비동기 프로그래밍을 위해 콜백 패턴이 많이 사용

### 프로미스 이해
* 콜백 패턴의 문제
  * 콜백 패턴은 코드의 흐름이 순차적이지 않음
  * 콜백 지옥 발생
  * (BUT) 프로미스를 사용하면 코드가 순차적으로 실행되게 작성 가능
* 프로미스의 3가지 상태
  * 대기(pending) : 결과를 기다리는 중
  * 이행(fulfilled) : 수행이 정상적으로 끝나서 결과값을 가진 상태
  * 거부(rejected) : 수행이 비정상적으로 끝남
* 프로미스의 처리됨(settled) 상태
  * 프로미스가 이행 or 거부된 상태
  * 처리됨 상태에서는 더 이상 다른 상태로 변경 X
* 프로미스 생성 방법
  * new 키워드로 생성
    * `new Promise((resovle, reject) => { ... } );`
    * 생성자는 (resolve, reject)를 인자로 갖는 콜백 함수를 매개변수로 갖는다
    * 수행이 성공한 경우 resovle를 호출하고, 수행이 실패한 경우 reject 호출
  * Promise.reject : 거부됨 상태의 프로미스 생성
  * Promise.resolve(arg)
    * 입력값 arg가 프로미스인 경우, arg 자체를 반환
    * 입력값 arg가 프로미스가 아닌 경우, 이행됨 상태의 프로미스 반환
* 프로미스의 then 메서드
  * 처리됨 상태가 된 프로미스를 처리할 때 사용하는 메서드
  * 처리됨 상태가 가지는 결과값을 인자로 가짐
  * then은 항상 프로미스 반환 
    * 연속적으로 then 메서드 반환 가능
    * 프로미스의 파이프라인 구성 가능
  * 중요한 특징
    * then 파이프라인은 항상 연결된 순서로 호출
    * 비동기 프로그래밍을 동기 프로그래밍 방식으로 코드 작성 가능
* 프로미스의 catch 메서드 
  * 프로미스 수행 중 발생하는 예외를 처리하는 메서드
  * 항상 Error 객체를 인자로 받음
  * then의 콜백으로 (null, err)을 매개변수로 하는 콜백 함수로 설정해도 같은 기능 수행
    * 가독성을 위해 catch 메서드를 사용하는 것이 좋음
    * example
      ```
      fetch('api/user')
        .then(data => {
          console.log(data);
        })
        .then(null, err => {  // .catch(err=>{...}) 와 동일
          console.error('ERROR!!! : ', err)
        })
      ```
* 프로미스의 finally 메서드
  * 프로미스가 이행됨/거부됨 상태일 때 호출 i.e 처리됨 상태(settled)가 될 떄 호출
  * 처리됨 상태의 프로미스의 데이터(결과 or 에러)를 건드리지 않고 추가 작업을 할 때 유용
  * 데이터 요청에 대한 성공/실패 여부 상관없이 특정 작업을 수행할 때(ex 로그) 유용

### 프로미스 활용
* Promise.all : 병렬로 처리
  * 여러 개의 프로미스를 병렬로 처리할 때 사용되는 함수
    * 비동기 함수 간에 서로 의존성이 없는 경우, 병렬 처리가 더 빠름
    * example
      ```
      Promise.all([fetch('/api/data/1'), fetch{'/api/data/2'}])
        .then(([data1, data2]) => {
          console.log(data1, data2);
        });
      ```
  * 비동기 함수간 의존성이 있어 순서가 중요한 경우 사용 불가
    * 순차적으로 실행해야 되는 경우, then 메서드를 이용한 프로미스 파이프라이닝 필요
    * example
      ```
      fetch('api/user')
        .then(ret => {
          const userId = ret.json().id;
          return fetch('api/user/userId');
        })
        .then(ret = .{
          console.log(ret);
        });
      ```
  * 프로미스를 반환
    * 인자로 받은 모든 프로미스가 처리됨 상태인 경우에 처리됨 상태가 됨
    * 인자로 받은 프로미스 중 하나라도 거부되면, 반환되는 프로미스도 거부됨 상태
* Promise.race : 가장 빨리 처리된 프로미스 반환
  * 인자로 받은 프로미스 중 가장 빨리 처리됨 상태가 된 프로미스 반환


### 프로미스 사용 시 주의할 점
* return 키워드
  * then 메서드의 인자는 이전 then의 콜백 함수에서 반환하는 값에 대한 프로미스
    * 프로미스인 경우, 프로미스 자체를 반환
    * 프로미스가 아닌 경우, 반환값을 가지고 이행됨 상태의 프로미스 반환
  * return을 생략하는 경우 다음 then에서 받는 인자는 undefined
* 프로미스 자체는 불변성을 가짐
* 프로미스를 중첩해서 사용하지 않기
  * 프로미스를 중첩하는 것은 콜백 패턴의 단점을 그대로 가져가는 행위
  * 프로미스를 중첩하는 것은 결국 순차적으로 실행되어 함을 뜻하므로, 순차적 처리 패턴을 사용
  ```
    fetch('api/user')
      .then(ret => {
        const userId = ret.json().id;
        return fetch('api/user/userId');
      })
      .then(ret = .{
        console.log(ret);
      });
  ```



## Section 5. 비동기 프로그래밍(2) async/await
* 비동기 프로그래밍을 동기 프로그래밍으로 작성할 수 있도록 함수에 추가된 기능
* 프로미스의 then 메서드의 체이닝보다 가독성이 좋아진다

### async/await 이해
* async await 함수
  * 프로미스는 객체로 존재하지만, async/await은 함수에 적용되는 개념
  * async 키워드로 정의된 함수
  * 항상 프로미스 반환
    * async await 함수 호출 후, 프로미스 메서드(then/catch/finally) 사용 가능
    * 함수 내부에서 프로미스를 반환하면, 그 프로미스 객체 그대로 반환
* await 키워드
  * async await 함수 내부에서 사용
  * await 오른쪽에 프로미스를 입력
    * 해당 프로미스가 처리됨 상태가 될 때까지, 해당 코드 블럭 대기
    * 비동기 처리를 순차적으로 작성 가능
* async await와 프로미스는 비동기 프로그래밍을 동기 프로그래밍 방식으로 작성 가능하게 함
  * 비동기 함수 간 의존성이 높아질수록 async/await의 가독성 개선 차이가 더 드러남
  * 즉, 비동기 함수들의 순차적 호출에서 유용


### async/await 활용
* 비동기 함수 병렬 실행
  * 여러 비동기 함수에 대해 각각 await 키워드를 사용하면 순차적으로 실행됨
    ```
      async function fetchData() {
        const data1 = await fetchData1();
        const data2 = await fetchData2();
      }
    ```
  * 실행할 비동기 함수들 사이에 의존성이 없는 경우 동시에 병렬로 실행시키는 게 더 좋음
  * 프로미스는 생성과 동시에 비동기 코드가 실행
  * 병렬로 실행할 프로미스를 먼저 생성하고 await 키워드는 나중에 사용하여 병렬 처리
    ```
      async function fetchData() {
        const p1 = fetchData1();
        const p2 = fetchData2();

        const data1 = await p1();
        const data2 = await p2();
        ...
      }
    ```
  * 병렬 실행의 경우, Promise.all이 더 간편
* 예외 처리
  * async await 함수 내부에서 발생하는 예외는 호출자가 try-catch로 예외 처리
  * try 블록 내부에서 발생하는 동기/비동기 함수의 예외는 catch 블록에서 처리
* Thenable 
  * 프로미스처럼 then 메서드를 가진 객체
  * ES6 이전부터 프로미스 방식처럼 작동하는 라이브러리 다수 존재
  * ES6의 프로미스가 아니더라도, then 메서드를 가진 객체를 Thenable이라 부름




## Section 6. 템플릿 리터럴
* 변수를 이용하여 동적으로 문자열을 **생성**하는 문법
  * 템플릿 리터럴은 백틱(`)을 이용
  * 표현식(expr)을 사용할 때는 `${expr}` 형식으로 입력
* 여러 줄의 문자열을 생성하기 쉬움
  * 템플릿 리터럴 내부에서의 엔터는 문자열의 개행을 표현
* 태그된 템플릿 리터널(tagged template literals)
  * 템플릿 리터럴을 확장한 기능으로 함수로 정의
    * 태그된 템플릿 리터널 함수는 함수명과 함께 템플릿 리터널을 붙여서 사용
  * 오른쪽 템플릿 리터널의 파싱 결과가 strings 및 expressions 매개변수로 들어감
    * 템플릿 리터럴의 표현식을 기준으로 문자열이 분할
    * 표현식 리스트는 expressions에 해당
    * 표현식으로 분할된 문자열들은 strings에 해당
    * 맨 왼쪽이나 오른쪽이 표현식으로 끝나는 경우, 빈 문자열이 strings에 들어감
      => strings의 길이는 expressions의 길이보다 항상 1이 크다
  * example
  ```
  function taggedFunc(strings, ...expressions) {
    console.log(strings, eppressions);
  }
  const v1 = 10;
  const v2 = 20;
  taggedFunc`a-${v1}-b-${v2}-c`;  // ['a-', '-b-', '-c'], [10, 20]
  taggedFunc`a-${v1}-b-${v2}`;  // ['a-', '-b-', ''], [10, 20]
  taggedFunc`${v1}-b-${v2}-c`;  // ['', '-b-', '-c'], [10, 20]
  ```
  * styled-component 패키지에서 태그된 템플릿 리터널 함수가 리액트 컴포넌트를 반환


## Section 7. 실행을 멈출 수 있는 제너레이터
* 함수의 실행을 중간에 멈추고 재개할 수 있는 독특한 기능
* 실행을 멈출 때 값을 전달할 수 있어 반복문에서 제너레이터가 전달하는 값을 하나씩 꺼내 사용 가능
* 제너레이터는 값을 미리 만들어 놓지 않음
  * 필요한 순간에 값을 계산하여 전달
  * 메모리를 필요할 때만 사용하여 효율적
* 실행을 멈추고 재개하는 기능 때문에 다른 함수와의 협업 멀티태스킹 가능

### 제너레이터 이해
* 제너레이터의 구성
  * 별표와 함께 정의된 함수
  * 그 함수가 반환하는 제너레이터 객체
  ```
    function* f1() {  // 1) 별표와 함께 정의된 함수
      yield 10;
      yield 20;
      return 'finished';
    }
    const gen = f1();  // 2) 함수가 반환하는 제너레이터 객체
  ```
* 제너레이터 객체
  * next 메서드
    * yield 키워드를 만날 때까지 함수가 실행되고 데이터 객체 반환
    * 반복자를 암시하는 메서드
  * 데이터 객체의 두 속성
    * done 
      * yield를 만나서 반환되는 경우 false
      * return이나 더이상의 yield가 없는 경우 true
      * 한번 참이 된 경우, next를 계속 호출하여도 true
    * value
      * yield나 return이 반환하는 값
      * done이 참이 되고, next를 호출하면 undefined
* 반복자 및 반복 가능 객체
  * 제너레이터는 반복자이자 반복 가능한 객체
  * 반복자의 3가지 조건
    * next 메서드를 가진 객체
    * next 메서드는 value 및 done 속성값 반환
    * done 속성값은 작업이 끝났을 때 참
  * 반복 가능한 객체의 2가지 조건
    * Symbol.iterator 속성값을 함수로 가지고 있음
    * Symbol.iterator 속성값에 대한 함수를 호출하면 반복자 반환
      ```
      // function* f1() {};
      const gen = f1();
      console.log(gen[Symbol.iterator]() === gen);  //true
      ```
  * for of 문과 전개 연산자
    * 반복 가능한 객체에서 유용
    * for of 문과 전개 연산자는 반복 가능한 객체에서 반복자를 얻음
    * done 속성값이 참일 때까지 해당 반복자의 next를 호출하면서 구성 요소들 접근

### 제너레이터 활용
* 제너레이터로 구현한 함수형 프로그래밍의 대표적인 함수들
  * map
    ```
      function* map(iter, mapper) {
        for (const v of iter) {
          yield mapper(v);
        }
      }
    ```
  * filter
    ```
      function* filter(iter, test) {
        for (const v of iter) {
          if (test(v)) {
            yield v;
          }
        }
      }
    ```
  * take
    ```
      function* take(n, iter) {
        for (const v of iter) {
          if (n <= 0) return;
          yield v;
          n--;
        }
      }
    ```
  * 위 세 함수는 제너레이터로 구현되어, 새로운 배열 객체를 생성하지 않음
    * 함수 자체를 호출하면, 제너레이터 객체만 생성하고 실제 연산은 수행 X
    * 값이 필요한 순간에 제너레이터 객체를 통해 다음 값을 요청하는 방식
    * 지연 평가(lazy evaluation) : 필요한 순간에만 연산하는 방식
* 제너레이터 함수끼리 호출
  * yield*
    * 키워드 오른쪽에는 반복가능한 객체가 올 수 있음
    * 제너레이터는 반복 가능한 객체이기 때문에 해당 키워드를 통해 제너레이터 함수 호출이 가능
  * example
    ```
      function* g1() {
        yield 2;
        yield 3;
      }

      function* g2() {
        yield 1;
        yield* g1();
        yield* [4,5,6];
        yield 7;
      }

      console.log(...g2()); // 1, 2, 3, 4, 5, 6, 7
    ```
* 제너레이터 함수로 데이터 전달
  * 제너레이터 함수는 외부로부터 데이터를 받아와 소비 가능
  * next 메서드를 호출하는 쪽에서 인자를 통해 데이터 전달
  * next의 역할은 다음 yield로 이동하는 것
    * rhs에 yield가 있는 경우 next 호출 시, 데이터 전달후 다음 yield로 이동
  * example
    ```
      function* g1() {
        const data1 = yield;
        yield data1 + 1;
        const data2 = yield;
        yield data2 + 2;
      }

      const gen = g1();
      gen.next();   // 제너레이터 함수의 실행이 시작되어 yield로 이동
      console.log(gen.next(1)); // { value: 2, done: false }
      gen.next();
      console.log(gen.next(1)); // { value: 3, done: false }
    ```
* 협업 멀티태스킹
  * 멀티태스킹
    * 여러 개의 태스크를 실행할 때, 하나의 태스크가 종료되기 전에 멈추고 다른 태스크를 실행하는 것
    * 협업 : 제너레이터가 실행을 멈추는 시점을 자발적으로 선택
  * 제너레이터 함수는 yield 키워드를 이용하여 자발적으로 자신의 실행을 멈춤
  * next 메서드를 호출하는 일반 함수는 next 메서드를 이용하여 제너레이터를 다시 실행
    * 이 때, 호출자인 일반 함수는 자신의 실행을 멈추는 효과
