### Chromium을 활용한 Javascript API 만들기
Javascript에서 사용할 수 있는 내부 API를 구축 해보자. 일반적으로 우리는
Javascript에서 제공되는 API를 활용해 script를 구성한다. script에 적은 API들이
어떤 방식으로 동작하고 새로운 API를 추가해 사용하기 위해선 어떤 동작들을
해야하는지 알아보도록 하자.

### Chromium과 v8 관계 overview
Chromium에서는 Javascript를 해석하고 동작시키기 위해 v8 이라는 Javascript (이하
		JS)
engine을 사용한다. v8 도 google에서 제공하는 open source이며, chromium 소스코드
내 포함되어있다.

![v8 overview](/img/v8_overview.png)

전체적인 동작을 아주 간소화해 생각해보자면, User가 Chromium에 document를 요청할
경우 Chromium은 document를 보여주기 위해 해석한다. 해석하는 과정에서 JS 코드를
만나게된다면 JS 를 해석하기 위한 JS engine인 v8에게 해석 요청을 한다. (v8 같은
		경우 JS를 해석하기 위한 JIT compiler를 소유하고 있음) v8 은 말그대로 JS를
해석하기 위한 용도이며, 해석된 결과를 binding을 통해 client (즉, chromium)에게 전달하며
후속처리를 하도록 한다.

간단하게 예시를 들어보자.

getElementById() 라는 함수를 많이 봤을 것이다. 이 함수를 사용하는 script가 포함
된 document를 요청할 경우 Chromium에게 요청했다고 가정해보자. Chromium은 코드를
해석하면서 JS코드를 발견하고 JS는 내 영역이 아니다 판단 후 v8에게 함수가 포함된 스크립트를 넘긴다.
v8은 script를 해석 후 "이 함수는 getElementById 함수다. 후속처리는 각자 client (여기서는 chromium)에서 알아서 해 라고 넘긴다."
이 때, 넘기기 위해서 미리 v8 에게 어디로 넘길지 알려줘야한다. 이 과정을 "binding"이라고 한다.

Chromium에서는 binding을 위해 IDL을 이용한다.

### WebIDL 이란
Web IDL을 사용하는 이유를 설명하기 앞서, JS 객체와 client의 인터페이스를
연결하는 binding이라는 개념을 설명했다. Binding
같은 경우 JS에서 해석된 결과물에 후속처리를 위해 하는 동작이다. 기존에 Binding을
하기 위해서는 User가 interface를 만들고 type converting을 포함해 v8의 핵심 부분인 isolate,
	context등을 조정해 관리해야했다.

Binding 부분을 자동화해 좀 더 편리하게 사용하는 것이 ***WebIDL*** 이다. IDL 이란 Interface Definition Language를 뜻하며, 각 종
 interface들을 쉽게 정의할 때 사용한다. 그렇다면 WebIDL은 무엇일까?

> Web IDL은 웹 플랫폼에서 공통 스크립트 객체의 동작을보다 쉽게 지정할 수있는 여러 가지 기능을 갖춘 IDL 변형이다.

자세한 내용을 알기 위해서는 [WebIDL](https://heycam.github.io/webidl/) 스펙
문서를 참고해 확인해보자. 기억 해야할 부분은 ***WebIDL 을 이용해 interface를
생성하고 binding을 쉽게하는 구나***이다.

### Chromium Binding overview (Binding 부분 디테일)
Chromium이 어떻게 WebIDL을 이용해 native 코드와 연결하는지 좀 더 자세하게
알아보자.

![webIDL](/img/webIDL_overview.png)


### Helloworld API 만들기 소스코드 구성 설명

### Console 출력 (결과 화면)
