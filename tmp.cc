// 객체를 생성하는 방법 3
//

class Shape
{
public:
  virtual ~Shape() {}
};

// Rect는 본연의 기능만 해야한다. 즉, 본연의 기능 + 만드는 기능이 되면 복잡해짐
// 만드는 기능은 따로 추출해서 관리하도록 하자.
class Rect : public Shape
{
  Rect() {}
public:
  friend class ShapeFactory;
};

class Circle : public Shape
{
  Circle() {}
public:
  friend class ShapeFactory;
};



// factory에서 다른 클래스에 접근을 해서 만들게 하기 위해서는 => friend를 사용해야한다.
class ShapeFactory
{
public:
  Shape* CreateShape( int type )
Factory를 활용한 생성  {
    Shape* p = 0;
    switch (type)
    {
      case 1: p = new Reck; break;
      case 2: p = new Circle; break;
    }
    return p;
  }
};

int main()
{
  ShapeFactory factory;
  Shape* p = factory.CrateShape(1); // 공장을 만드는 공간이 한 곳으로 몰림.
                                    // 객체를 맵을 이용해 자원을 공유할 수 있음.
                                    // rect, circle은 자신의 고유의 기능을 하면됨.
                                    //
  // 객체 생성을 위한 전용 클래스
  // 객체의 생성을 한 곳에 집중시키지만, 객체 본래의 기능과 객체 생성을 위한 코드를 분리
  // 추상 팩토리 (Abstract Factory) 패턴
}


