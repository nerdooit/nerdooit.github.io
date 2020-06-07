---
layout: post
title: '[Design Pattern] 객체를 생성하는 방법'
subtitle: 'C++ 에서 객체를 생성하는 방법을 알아보자'
date: 2020-06-07
author: nerdooit
cover: 'img/design_pattern_cover.png'
tags: C++ DesignPattern
lastmod : '2020-06-07 14:24:00'
---

### 객체를 만드는 방법
 우리가 흔히 사용하는 객체를 만드는 방법에는 크게 4가지가 존재한다.
- Stack / Heap 영역에 할당받아 생성 (자유로운 방법)
- Static 멤버함수를 활용한 생성
- Factory를 활용한 생성
- 객체 복사를 이용한 생성

지금부터 이 4 가지 생성 방법에 대해 알아보자.

#### Stack / Heap 영역에 할당받아 생성
 위 방법은 다소 자유로운 방법이다. 우리가 흔히 사용하는 방법으로, 일반적인 생성
 또는 동적할당을 통한 생성을 말한다.

 ```java
class shape
{
public:
	virtual ~Shape() {}
};

class Rect : public shape
{
public:
};

class Rect : public shape
{
public:
};

int main() {
	Rect r; // 일반적인 생성
	Shape *p = new Rect; // 동적할당을 통한 생성
}
```

위의 소스코드에서 나타난 것처럼 일반생성과 동적할당 생성은 우리가 흔하게
사용하는 것이다. 비교적 자유로운 방법이지만 ***객체 생성에 제약이 없다***

우리 가정을 한번 해보자.

만약, 내가 Rectangle 클래스를 10개 이상 만들지 못하게 제약을 주고싶다. 이럴 경우
어떻게 해야하는가? 지금과 같은 방법에서는 제약할 수 있는 방법이 없다. 왜냐하면
사용자가 아무곳에서나 객체를 생성할 수 있기 때문이다. 그렇다면, 객체
생성을 제약하기 위해서는 어느 ***한 곳***을 정해 그 곳에서만 객체를 만들 수 있게
해야한다.

#### Static 멤버함수를 활용한 생성
한 곳으로 정해 객체를 생성하기 가장 쉬운 방법은 생성자를 private으로 만들고
pulic 영역에 실제 객체를 생성할 수 있도록 만들면 된다. 코드를 보자

```java
// 소스코드는 위와 거의 동일하며, 공간활용을 위해 Rect 클래스만 적도록 하겠다.

class Rect : public Shape
{
	Rect() {}
public:
	static Shape* Create() { return new Rect; }
}

int main()
{
	Shape* p = Rect::Create();
}
```

위의 코드와 같이, private 영역 (c++에서는 class 내 정의를 하지 않으면 private
		영역으로 간주한다) 에 생성자를 만든다. private 영역에 생성자를 만들면
외부에서 객체 생성이 불가능해진다. 객체를 생성하기 위해서는 생성자를
호출해야하나, 생성자를 외부에서 부를 수 없기 때문에 생성자체가 불가능해진다.
이럴 경우, 어떻게 생성을 해야하나?

코드에 나와있는 것과 같이, static함수를 하나 생성해 그 내부에서 객체를 생성해
반환하도록 한다. static을 선언하는 이유는 ***객체가 생성되야 하는 멤버함수 로는
객체 생성 불가능*** 하기 때문이다. 따라서, Create 함수 자체를 staic으로 선언해
메모리 일정영역을 잡아둔다. 이후 외부에서 호출 할 경우 new 연산자로 새롭게 할당
받아 반환해준다.

static을 통한 생성을 하면 뭐가 좋은가?
- 객체의 생성을 한곳에서 수행
	- 다양한 제약조건을 만들 수 있음.
		- 객체 생성 제한
		- 자원 공유 -> 객체를 지속적으로 생성하는 것이 아닌 풀을 만들고 필요할 때
		전달해주는 즉, 공유하는 방식이 가능해짐.
- 객체 생성함수를 함수 인자로 전달

##### 객체 생성함수를 함수 인자로 전달
"제목에서 보이는 말은 무슨말인가?" 하는 의문이 들수 있다. 예시를 보자.

예시) 도형을 만들어서 그림을 그리는 함수를 하나 만들고 싶다. CreatedAndDraw() 를
만들어보자.

만들기 위해서는 내부에서 객체를 생성해야하는데 구별을 해야한다. 그렇다면 어떻게
구별할 것인가?
- CreateAndDraw(int type)
- CreateAndDraw(string type)
- ...

보통 위와 같이 함수로 구현해 type으로 switch case문으로 구성하려고한다. 이럴
경우 모든 케이스별로 함수를 만들어야하며, OCP(추후 디자인 패턴 포스팅에서
		정리하겠다)를 만족하지 않는다. 이런케이스를 방지하기 위해서는 보통 함수의
포인터를 이용해야한다. ***CreateAndDraw(Shape*(*f)())*** 이런식으로
구현해야한다. 만약 static create 함수가 존재한다면 아래와 같이 쉽게 해결된다.

```java
// 이번 소스도 공간의 절약을 위해 일부만 나타낸다.

void CreateAndDraw(Shape* (*f)())
{
	Shape* p = f();
	p->Draw();
}

int main()
{
	createAndDraw(shape::Create());
}
```

위의 소스코드를 보면, Create 함수를 통해 객체를 생성하고 Draw함수를 통해 그림을
그린다. 이때, Create가 static을 선언이 되어있어야 전달이가능하다. 이 기법은 현재
open source에서도 많이 사용되고 있다. 나중에 chromium을 분석하다 만나면
reference로 걸어두겠다.

너무 어려워 하지 말자. 추후 다른 포스팅에서 더 자세하게 다룰 수 있으니 지금은 아
이런게 있구나 정도만 이해하자.

#### Factory를 활용한 생성
Factory 활용한 생성은 Design pattern에서 자세하게 다루겠지만 어떤 구성인지
대략적으로 여기서 알아보자. Factory는 말 그대로 공장이다. 객체를 생성하는
공장이라고 생각하면 된다. 객체를 만드는 공장이 왜 필요한가? 아래를 통해
확인해보자.

```java
class Rect : public Shape
{
	Rect() {}
public:
	friend class ShapeFactory;
};

class ShapeFactory
{
public:
	Shape* CreateShape(int type)
	{
		switch(type)
		{
			case 1: p = new Rect; break;
			case 2: ..
		}
		return p;
	}
};

int main()
{
	ShapeFactory factory;
	Shape* p = factory.CreateShape(1);
}
```

위의 소스코드를 보자. 쉽게 해석이 가능할 것이라 생각한다. Factory를 이용해
객체를 생성하는 것이 포인트이다. 기존에는 Shape 클래스에서 만들어지는 Create를
가졌다면, Create기능을 따루 추출한다. Factory에서 생성을 담당하고 ***Shape는
본연의 Shape기능만 하도록한다*** 이 부분이 중요하다. Object 같은 경우 자신의
역할을 충실히 이행해야한다. Dependency를 최소화 하는 것이 객체지향에서 중요한
부분인데, 이 부분을 만족하도록 만든다. (추후 좀 더 자세히 다루겠다)

#### 객체 복사를 이용한 생성
지금까지 객체를 만든 방법을 생각해보자. 전부 새로운 객체를 만드는 방법이 아닌가?
새로운 객체를 만드는 방법이 아닌 객체를 만드는 방법에는 기존의 객체를 이용해 복사하는 방법도 있다.
아래의 소스코드를 보자

```java
class Shape
{
public:
	virtual Shape* Clone() =  0;
	virtual ~Shape() {}
};

class Rect : public Shape
{
public:
	virtual Shape* Clone() { return new Rect(*this); }
};

int main()
{
	Shape *p = new Rect;
	Shape *p2 = p->Clone();
}
```

소스코드를 분석해보자. 만약 Shape라는 공통 기반 클래스에서 ***Clone***이라는
것을 순수가상함수를 통해 무조건 구현하도록 했다고 해보자. 그럴 경우 추후
상속받는 경우에 Clone을 구현해야한다. Clone 동작을 보면 이름과 같이 자기 자신을 복사하도록
되어져있다. main 문을 통해 보면 쉽게 p2 객체가 생성되는 것을 볼 수 있다.

---
#### Reference
[강석민의 Design pattern](https://www.ecourse.co.kr/course/design_pattern_in_cpp/)

위의 강의를 통해 들은 내용을 정리하였다. 다만, 강의 내용 + 본인의 개념이 같이
들어가기 때문에 온전한 강의를 듣고 이해하길 원한다면, 위의 링크를 통해서 강의를
듣는 것을 추천한다. 강의력이 장난아니다 :)
