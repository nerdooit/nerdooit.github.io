---
layout: post
title: '[C++] Setprecision()'
subtitle: 'Setprecision에 대해 알아보보자'
date: 2020-06-14
author: nerdooit
cover: 'img/cpp_reference_cover.png'
tags: C++문법 C++
lastmod : '2020-06-14 12:10:00'
sitemap :
  changefreq : daily
  priority : 1.0
---
### Setprecision 함수
Setprecision 함수는 출력연산을 부동소수점 값을 형식화 하는데 사용되는 10진수
정밀도를 사용해 표시해준다. 쉽게말해, C++에서 자리수를 조절해주는 함수이다.
우리가 C를 공부했다면, printf("%.2f", variable); 에서 .2f와 같은 효과를 가진다.
이런 함수를 ***조작자***라 부르며 스트림을 조작하여 그다음 입력/ 출력 스트림이 정해진
자리수를 유지하도록 부른다.

Setprecision(n); 으로 precision을 n만큼 조작하는 동작을 요청 할 경우 입력 / 출력
스트림을 조작하여 n만큼 자리수를 유지하도록 한다.

조작자관련 함수나 데이터는 iomanip 헤더파일에 존재한다.

### Setpresion의 특징
Setprecision의 예시를 보기 앞서 몇가지 특징들 혹은 팁을 이해하고 본다면 좀 더
쉽게 이해할 수 있다.
- Setprecision 같은 경우 적용 후 다음 라인의 입출력에서 적용이 된다.
- precision의 변경 같은 경우 n자리를 기준으로 출력하며, 소수점에서는
***반올림***된다.
- precision은 자리를 출력하는 부분을 조작하는 것이지, ***소수점 자체의 내용을
조작 하는 것이 아니다***.
	- 이 부분을 이해하는 것이 중요하다. 즉, 내부적으로 float 같은 경우 scientific
	정밀도를 적용하여 출력한다 (과학적 수치에 따라 가장 근사값으로 계산한다는 뜻).
	precision을 적용한다면, scientific기준으로 계산한 값을 기준에서 자리수 만큼
	출력하겠다는 의미이다.

### Example
아래의 예제를 통해 setprecision 사용법에 대해 알아보자. 아래의 예시는
cppreference.com 에서 발췌했다.

```java
// setprecision example
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision

int main () {
  double f =3.14159;
  std::cout << std::setprecision(5) << f << '\n';
  std::cout << std::setprecision(9) << f << '\n';
  std::cout << std::fixed;
  std::cout << std::setprecision(5) << f << '\n';
  std::cout << std::setprecision(9) << f << '\n';
  return 0;
}
```
위 소스코드의 결과이다.

```output
3.1416
3.14159
3.14159
3.141590000
```

위의 코드를 보자면, setprecision를 사용하기 위해서는 iomanip 헤더파일이
필요하고, 조작을 통해 아웃풋이 조작되는 것을 확인할 수 있다. 다만, cout이
다음줄로 넘어갈 경우 적용되는 것을 확인했다. 이 코드에서 재밌는 점은 fixed를
적용했을 때, 바로 적용되는 점이다. fixed로 소수점을 5자리로 고정할 경우 소수점은
5자리까지 출력되고 9자리로 늘려도 이후 0000 이 출력되는 것을 확인할 수 있다.
fixed 관련해서는 ***Tip*** 부분에 정리를 해뒀으니 확인을 해보기 바란다.

### Tip
Fixed에 대해 알아보자.

Fixed 같은 경우 ios 헤더 파일에 존재하며, 내부적으로 float / double 연산에서
소수점 자리를 조절하도록 한다. 입출력 내에서 float / double을 출력하기 앞서
flag를 확인하는데, scientific / fixed 유무에 따라 출력이 달라진다. Default는
scientific 으로 설정되어져있고, 사용자가 원할 경우 fixed로 설정가능하다. 다만,
					 fixed로 할경우 사용자가 precision으로 설정을 해줘야한다. 얼마만큼
					 변화시킬 것인지.

***즉, fixed 이후 setprecision을 기준으로 소수점의 자리수가 결정된다.***

```java
void setFixed()
{
	cout << fixed << setprecision(n); // n만큼 소수점을 고정해라
	/* 소수점 비트 세팅방법 */
	cout.setf(ios::fixed);  // setting
	cout.unsetf(ios::fixed); // unsetting

	// 위와 같이 세팅 후 자리수를 설정해준다면, 자리수에 맞게 소수점이 출력됨.
	// 만약 설정하지 않는다면, 내부적인 default 값으로 세팅됨
}
```

해당 부분을 자세하게 알고 싶다면, [cpp 레퍼런스](http://www.cplusplus.com/reference/ios/ios_base/precision/)  를 확인해보자.

---

#### Reference
[부동 소수점 stack overflow](https://stackoverflow.com/questions/45084317/what-is-the-role-of-stdsetprecision-without-stdfixed-in-c)
[setprecision cpp 레퍼런스](http://www.cplusplus.com/reference/iomanip/setprecision/)
[pmoncode 블로그](https://pmoncode.tistory.com/20)
[블로건 블로그](https://bluegun.tistory.com/19)
[그림그리는 개발자 블로그](https://imagej.tistory.com/66)
