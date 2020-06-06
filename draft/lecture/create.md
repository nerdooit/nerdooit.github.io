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

 ```c
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
