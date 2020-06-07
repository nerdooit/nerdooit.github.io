// 객체를 생성하는 방법 4
//

class Shape
{
public:
  virtual ~Shape() {}

  virtual Shape* Clone() = 0;
};

class Rect : public Shape
{
public:
  virtual Shape* Clone() { return new Rect(*this); };
};

class Circle : public Shape
{
public:
  virtual Shape* Clone() { return new Rect(*this); };
};

int main()
{
  Shape *p = new Rect;
  // 지금까지 만든 방법은 새로운 객체를 만드는 방법
  // 기존에 존재하던 객체를 복사해서 새로운 객체를 생성하는 방법을 알아보자.
  //

  Shape* p2 = p->Clone(); // prototype pattern
  // clone 가상함수 사용
  // 활용도가 높다.
}

