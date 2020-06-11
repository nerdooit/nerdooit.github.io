---
layout: post
title: '[Design Pattern] Singleton pattern'
subtitle: 'C++로 Singleton을 디자인 하는 방법을 알아보자'
date: 2020-06-11
author: nerdooit
cover: 'img/design_pattern_cover.png'
tags: C++ DesignPattern
lastmod : '2020-06-11 14:24:00'
sitemap :
  changefreq : daily
  priority : 1.0
---
### Singleton pattern
클래스를 디자인 할 경우 인스턴스는 오직 하나임을 보장하여 접근 어디에서든
하나로만 통합되어져 있는 디자인 기법을 말한다. 즉, 쉽게 생각해보면, 오직 하나의
객체만 존재해야한다는 말이다.

### Singleton 예시
Singletone을 이해하기 위해 예시를 보자. 백마디 말보다 코드 한 줄이 때론 이해하기
쉽다. 예시를 보자.

```java
class Cursor
{
	  int x,y;
};

int main()
{
	  Cursor& c1;
		Cursor& c2;
}
`````

위의 소스코드는 Cursor 클래스를 엄청나게 간단하게 구현한 것이다. Cursor란 우리가
마우스를 사용했을 때, 화면에 나타는 포인터를 말한다. 일반적으로, 마우스를 두개
사용한다고 해서 Cursor가 두개가 되는 것은 아니다. 즉, Cursor class는 오직 하나만
있어야한다. 이를 위해 고안된 디자인 기법이 ***Singletone pattern***이다.

우리는 문제점을 통해 왜 Singletone pattern을 사용해야하는지 예시와 함께 알아보았다. 그렇다면, Singletone은 어떻게 구현해야할까
? 가장 단순하게 생각할 수 있는 방법은 ***객체생성기법 2번째***를 이용하는 방법이다. 객체생성기법 2번째 방법은 생성자를 private에 놓고, 외부에서는 생성하지 못하도록 한다. 이후 Create라는 함수를 public으로 열어줘 사용자가 오직 Create()를 통해 객체생성을>하도록 한다. 코드로 확인하자.

```java
class Cursor
{
  int x,y;
  Cursor() {};
public:
  static Cursor& getInstance()
  {
    static Cursor instance;
    return instance;
  }
};

int main()
{
  Cursor& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();
}
```

위의 코드는 저번 포스팅에 대략적으로 다루었다. 이번에는 왜 이렇게 작성했는지 조금 디테일하게 보자. 우선, Private에 생성자를 두
게 될 경우 외부에서는 선언이 불가능해진다. 따라서, 사용자는 무분별하게 객체 생성이 불가능해진다. 그리고 getInstance()라는 함수
를 호출할 경우 Cursor의 객체를 생성한다. 여기서 중요한 점은 static 변수와 함께 객체가 생성되어졌기 때문에 이후의 호출에 대해서
는 무시한다는 점이다. 즉, 객체가 한번만 생성된다는 점이다. 왜 static을 썼는지에 대한 이야기는 아래에서 다루도록 한다.

정말 동일한 객체가 존재하는지는 어떻게 알아봐야하지? 라는 의문이 생길 수도 있다. 그럴경우 아래와 같이 작성해 확인해보자. (객체
 생성 유무를 알아볼 때 많이 사용하는 팁이다)

```java
int main()
{
  Cursor& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  cout << &c1 << endl;
  cout << &c2 << endl;
}
```

위와 같이 코드를 작성한다면, 객체의 주소값을 출력할 수 있다. ***주소가 동일***한지를 통해 객체가 동일하다를 판단한다. 이는 대>형 소스코드를 분석할 때도 많이 사용되니 꼭 알아두자.

### Singleton의 일반적인 구현
위의 코드는 Singleton의 일반적인 구현방법이다.
- 생성자를 private에 둔다
- static 멤버함수를 통해서 오직 하나의 객체를 생성한 후 참조를 반환한다.

이 두가지 방법이 끝일까? 다음 예시를 하나 보자.

```java
int main()
{
  Cursor c1 = Cursor::getInstance();

  Cursor c3 = c1;
}
```

위의코드를 보면 좀 충격적일 수도 있다. (개인적으로 실력이 아직 부족하여 충격적이였다.) 당연하게 getInstance로만 하면 되지라고 생각했지만, ***복사생성자, 대입연산자*** 를 통한 생성에 대한 예외 처리를 해줘야한다. 만약 하지 않는다면, 위와 같이 c3라는 새로운 객체가 무분별하게 생성된다. 즉, Cursor가 두개가 만들어지는 것이다. (끔찍하기도하다..) 이에 대한 예외처리는 아래의 코드를 보자.

```java
class Cursor
{
	Cusro() {}
	Cursor(const Cursor&) = delete;
	void operator(const Cursor&) = delete;
}
```

위의 코드와 같이, ***복사 생성자, 대입연산자***를 만들지 않는 것의 핵심은
***delete***연산이다. Delete연산 같은 경우 C++11 부터 도입되었으며, 생성자를
생성하지 않을 때 사용한다. (추후 자세하게 다뤄보겠다)

그렇다면, 일반적인 Singleton 정리를 다시한번 보자
- 생성자를 private에 놓는다
- static 함수를 통해서 생성할 수 있도록 한다
- 복사생성자와 대입연산자를 사용할 수 없도록 한다

### singleton의 다른 방법들
Singleton을 구현할 때, 위의 일반적인 방법 말고 다른 방법들이 존재한다. 어떤
방법들이 있는지 알아보자.

#### Static 멤버 데이터 사용 구현
일반적으로 객체를 생성하는 방법을 생각해보자. 객체 내에서 객체를 선언해 유지할
수 있을까? 일반적으로 불가능하다. 따라서 우리는 객체를 유지하기 위해서 일반적인
멤버 데이터가 아닌 ***static data***를 통해 객체를 유지해야한다. 아래의 코드를
보자

```java
class Cursor
{
	Cursor() {}
	Cursor(const Cursor&) = delete;
	void operator=(const Cursor&) = delete;

	// Cursor c; 이렇게 쓸 수 없다. 객체 내에서 객체를 생성할 수 없다.
	// 따라서, static 멤버데이터가 필요함
	static Cursor c;
public:
	Static Cursor& Create() {
		return c;
	}
}
Curor Cursor::c;
```

위의 코드에서 보는것과 같이 static 멤버데이터를 선언한 후 Create에 반환하는
방법으로 singleton을 구현할 수 있다. (위의 일반적인 방법은 static 멤버데이터를
		활용하지 않는다.) 다만, 위 방식으로 디자인 할 경우 큰 문제가 있는데
***사용자가 singleton 객체를 안부르면 어떻게 되나?*** 라는 문제가 생긴다. 즉,
	static 멤버데이터는 singleton 객체를 사용자가 부르는 것과 관계없이 먼저
	생성되어져있다. 이후 사용자가 요청하면 생성된 static 객체를 반환해주는
	원리이다. 사용자가 singleton 객체를 호출하거나 생성하지 않는다면 무의미한
	객체가 메모리 상에 남아있는 것이다. (현재는 하드웨어가 좋아서 크게 느끼지
			못하겠지만, 예전에는 메모리의 용량이 작아서 메모리를 최대한 아끼는
			방향으로 디자인했다.) 이 문제를 해결하기 위해 우리가 일반적으로 사용하는
	방법인 지역 변수 static 생성 및 할당을 사용한다.

#### Static 지역 변수 생성 및 할당 (Mayer's Singleton)
	일반적인 static 멤버데이터로 구현할 경우 내가 만들지 않았는데, 메모리 공간을 차지하는 문제가 발생한다. 이를 해결하기 위해, Static 지역 변수 생성 및 할당 기법을 활용하고자한다. 이 방법은 Scott Mayer에 의해 처음 언급되어졌다. Mayer는 C++를 한다면 한번 쯤 들어봤을 Effective C++의 저자이다. 이 방법의 기본 원리는 ***사용자가 객체를 원할 경우 static 객체를 생성해 전달한다*** 즉, lazy initialization이라고 보면 된다. 사용자가 요청할 때까지 초기화를 미루고 후에 사용자가 요청하면 그때 초기화하는 기법이다. 해당 소스는 ***일반적인 기법***으로 위에서 너무 많이 설명하였기 떄문에, 공간절약을 위해 생략하고자한다. 궁금하신분은 스크롤을 올려 한번 더 읽어보길 바란다.


#### new를 활용한 생성
	Mayer 방법이외에도 lazy initialization 기법이 존재한다. Pointer를 활용해
	사용자가 필요할 떄, 전달하는 방법이다.

```java
class Cursor
{
	Curosr() {}
	Cursor(const Cursor&) = delete;
	void operator=(const Cursor&) = delete;

	static Cursor* p;
public:
	static Cursor& Create()
	{
		if (p == 0)
			p = new Cursor;
		return *p;
	}
}

Cursor* Cursor::p = 0;
```

위의 코드와 같이, pointer를 멤버 데이터로 갖고 있으며, 사용자가 Create()를
요청할 경우 그 때, 생성 유무를 판단하고 없다면 new 연산자를 활용해 생성 후
반환해준다. 위 방법도 많이 쓰이는 방법이다. 다만, 위 방법에서는 생각해야할
문제가 있다. 어떤 문제일까?

바로, ***동기화 문제***이다. 일반적으로 잘 생각하기 힘든 문제이지만, 시스템을
다루는 사람들에게는 많이 흔하다 (최근에는 코어가 많아져 어플제작에도 동기화
		문제를 많이 고려해야하는 것으로 안다). pointer 를 검사하는 부분에서 atomic
한 동작이 이뤄지지 않으면, 동시에 객체가 생성 될 수 있는 문제가 존재한다. 이
문제를 어떻게 해결해야할까? 너무 길어지니 다음 포스팅에서 알아보자 :)

### 정리
오늘 다양한 정보를 배운 것 같다. 따라서 기억해야하는 부분을 정리하자.
Singleton은 인스턴스가 하나임을 보장하여, 접근을 어디에서 해도 하나로
통합되어지는 디자인 패턴이다.

Singleton을 작성하는 여러가지 방법 (더 있을 수도 있다)
- Static 멤버데이터
- Static 지역 변수
- Pointer 활용

---
#### Reference
[강석민의 Design pattern](https://www.ecourse.co.kr/course/design_pattern_in_cpp/)
