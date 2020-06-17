---
layout: post
title: '[Opensource] Android Framework source'
subtitle: 'Android의 singleton 패턴을 분석해보자'
date: 2020-06-17
author: nerdooit
cover: 'img/osc_cover.png'
tags: Opensource DesignPattern
lastmod : '2020-06-17 20:24:00'
sitemap :
  changefreq : daily
  priority : 1.0
---
### Singleton pattern
우리는 singleton 디자인 패턴을 통해 singleton 을 일반화 하는 방법까지
알아보았다. 아래의 코드는 singleton 기법을 일반화한 소스코드이다.

```java
#include <iostream>
using namespace std;

template<typename TYPE> class Singleton
{
  int x,y;
protected:
  Singleton() {}
  Singleton(const Singleton&) = delete;
  void operator=(const Singleton&) = delete;
public:
  static TYPE& getInstance()
  {
    static TYPE instance;
    return instance;
  }
};

class Mouse : public Singleton < Mouse >
{

};

int main()
{
  Mouse& c1 = Mouse::getInstance();
}
```

singleton 소스코드의 설명을 보고 싶다면 [singleton1](https://nerdooit.github.io/2020/06/11/design_pattern_sigleton.html) , [singleton2](https://nerdooit.github.io/2020/06/17/design_pattern_sigleton_2.html) 두개의
포스팅을 읽어보자.

### 안드로이드 singleton pattern

아래는 [안드로이드 singleton pattern](https://android.googlesource.com/platform/frameworks/native/+/jb-dev/include/utils/Singleton.h)을 발췌한 소스코드이다.

아래의 코드를 보면 우선 DCLP 기법은 적용되어있지 않는 것으로 보인다. 다만,
	Lock을 통해 동기화 문제를 해결 하고 있는 것으로 보이고, Template을 통해 CRTP
	기법을 사용하는 것을 보인다. 오픈소스지만 충분히 해석이 가능하다고 볼 수 있다.
	Chromium 은 안드로이드보다 복잡하게 작성되어있어 Template trait을 연구하고
	작성하도록 하겠다.

```java
namespace android {
// ---------------------------------------------------------------------------
template <typename TYPE>
class ANDROID_API Singleton
{
public:
    static TYPE& getInstance() {
        Mutex::Autolock _l(sLock);
        TYPE* instance = sInstance;
        if (instance == 0) {
            instance = new TYPE();
            sInstance = instance;
        }
        return *instance;
    }
    static bool hasInstance() {
        Mutex::Autolock _l(sLock);
        return sInstance != 0;
    }
protected:
    ~Singleton() { };
    Singleton() { };
private:
    Singleton(const Singleton&);
    Singleton& operator = (const Singleton&);
    static Mutex sLock;
    static TYPE* sInstance;
};
/*
 * use ANDROID_SINGLETON_STATIC_INSTANCE(TYPE) in your implementation file
 * (eg: <TYPE>.cpp) to create the static instance of Singleton<>'s attributes,
 * and avoid to have a copy of them in each compilation units Singleton<TYPE>
 * is used.
 * NOTE: we use a version of Mutex ctor that takes a parameter, because
 * for some unknown reason using the default ctor doesn't emit the variable!
 */
#define ANDROID_SINGLETON_STATIC_INSTANCE(TYPE)                 \
    template class Singleton< TYPE >;                           \
    template<> Mutex Singleton< TYPE >::sLock(Mutex::PRIVATE);  \
    template<> TYPE* Singleton< TYPE >::sInstance(0);
// ---------------------------------------------------------------------------
}; // namespace android

```
