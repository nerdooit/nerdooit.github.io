---
layout: post
title: '[C++] sync_with_stdio() 와 cin.tie()'
subtitle: 'C++에서 IO 동작을 빠르게 하는 방법을 알아보자.'
date: 2020-06-20
author: nerdooit
cover: 'img/cpp_reference_cover.png'
tags: C++문법 C++ boj
lastmod : '2020-06-20 21:10:00'
sitemap :
  changefreq : daily
  priority : 1.0
---

### Fast IO 동작
백준 문제와 같이, 알고리즘 문제를 풀다보면 다양한 입출력을 만날 경우가 존재한다.
특히 시간초과가 나는 경우가 많이 존재하는데, 예를들어 데이터가 너무 많아 질 경우
시스템에서 처리하지 못해 시간 초과가 발생한다.

아래의 백준에서 입출력 속도를 정리해 둔 것을 발췌해왔다. 순위로 잘린 부분의
대부분은 파이썬 언어이다.

![io 스피드 측정](/img/io_speed.png)

위의 그림을 통해 보자면, mmap이 가장 빠르다고 나온다. mmap은 운영체제 상으로도
가장 빠른 속도로 나와있다. 해당 코드는 첨부는 하지만, 개인적으로 설명을 하지
않겠다. 필요한 사람은 mmap에 대해 공부한 후 사용하길 바란다.

mmap을 통해 입력을 받아오는 코드이다. [doocong 블로그](http://doocong.com/algorithm/fast-input-mmap/) 참조해 발췌하였다.

```java
#include <sys/stat.h>
#include <sys/mman.h>
class fio {
  size_t rsize;
  unsigned char* rbuf;
  int ridx;

  public:
  fio() : ridx(0) {
    struct stat rstat;
    fstat(0, &rstat);
    rsize = rstat.st_size;
    rbuf = (unsigned char*)mmap(0,rsize,PROT_READ,MAP_FILE|MAP_PRIVATE,0,0);
  }

  inline bool isBlank() {
    return
      rbuf[ridx] == '\n' || rbuf[ridx] == '\t' || rbuf[ridx] == '\r' ||
      rbuf[ridx] == '\f' || rbuf[ridx] == '\v' || rbuf[ridx] == ' ';
  }
  inline void consumeBlank() { while (isBlank()) ridx++; }

  inline int readInt(){
    int res = 0, flag = 0;
    consumeBlank();
    if (rbuf[ridx] == '-'){
      flag = 1;
      ridx++;
    }
    while (!isBlank() && ridx < rsize)
      res = 10 * res + rbuf[ridx++] - '0';
    return flag ? -res : res;
  }
};
```

우리가 중점적으로 볼 부분은 ***빨간색 표시*** 한 부분이다. C++에서 가장 많이
사용하는 ***cin***연산에 대해 알아보고자 한다. 기본적으로 cin연산을 사용하게 될
경우 데이터 10,000,000 기준 약 2초 정도 소요된다. 하지만 여기에
ios_base::sync_with_stdio(false); cin.tie(NULL); 2개의 옵션이 추가될 경우
***1.5초*** 정도 감소되는 것을 확인할 수 있다.

어떻게 된일인가? 알아보자.

### sync_with_stdio()
C++ 같은 경우 기본적으로 C를 품고 구현되어졌다. 따라서, C와 거의 완벽(?) 한
호환을 이뤄야한다는 점이 중요했다. 이런점에서 입출력 같은 경우 C와 C++이
호환적으로 이뤄져야했는데, stream을 이중으로 유지해 입력과 출력
스트림을 따로 유지했다. 즉, C 스트림과 C++ 스트림이 따로 유지가 되었고, 개행
문자를 통해 구별하는 입출력인 printf와 같은 것은 C 스트림 그리고 cout, cin 과
같은 객체를 이용한 입출력은 C++ 스트림으로 구별되었다. 그리고 출력하기 전에
동기화를 맞춰 출력하도록 했다.

```java
#include <iostream>
#include <cstdio>

int main()
{
	cout << "haha";
	printf("%s\n",hoho);
}
```

위와 같이 출력을 해도 잘 출력이 되는 것을 볼 수 있다. 즉, stream은 달리
들어가지만, 출력 시 동기화를 맞춰 출력을 하도록 내부적으로 구현되어져 있기
때문이다. 동기화를 잘 유지하기 위해 thread-safe하게 동작한다. 이런 동작은
***이용은 편리하지만, 속도를 저하시킨다*** 는 문제가 존재한다.

생각해보면, 동기화를 위해 thread간 순서를 유지하는 동작은 정말 큰 overhead이다.
그렇다면 이 동작들을 하지 않는다면(?) 속도는 월등하게 상승할 수 있다.

```java
ios_base::sync_with_stdio(false);
```

위의 문법과 같이, 입출력의 sync를 맞추지 않겠다고 C++에서 명령한다면, C++ 자체는
"아.. 이제 C stream에 대해 관리할 필요가 없구나를 생각한다. " 즉, C++ 자체
버퍼만 이용하면 되는구나. thread 동기화를 생각할 필요 없구나 생각하게 된다.
위와같이 설정을 하게 된다면, stream 관리가 필요 없고 독립적인 stream 버퍼만 운영하기 때문에 입출력에서는 ***속도 향상***을 시킬 수 있다.

다만, 주의해할 점이 있다.
앞서 말했듯, stream을 C++ 기준으로만 하기 때문에 ***C언어 관련 입출력연산(scanf/printf/puts/getchar/putchar 등)들을
사용하지 못한다.*** 이 부분을 꼭 기억해야한다.

### cin.tie()
cin 과 cout은 tie() 즉, 묶여있다. tie() 동작은 std::cin 통해 입력을 받기전에 std::cout을 flushing 하도록 한다. tie() 동작은 상호작용을 요하는 console 프로그램에서 유용하지만, large I/O 동작을 할 때 속력이 느려지는 단점이 있다. 만약 아래의 코드와 같이, Null을 인자로 전달하게 된다면, utie 동작을 수행할 수 있다.

```java
cin.tie(NULL);
```

위의 코드를 사용하면, 단점인, 다수의 데이터가 들어올 경우 속도가 빨라질 수 있다.
백준 문제를 생각해보면, 지속적으로 출력을 하는 것이 아닌 결과를 모아서 한번에
출력하면 되도록 되어져있다. 따라서, tie() 동작을 굳이 할필요가 없으며, tie()
	동작을 제거하고 flushing을 제거하게 된다면 속도가 빨라질 수 있다.

아래의 예시를 보자.

```java
#include <iostream>
int main()
{
	std::cout << "Enter name:";
	std::cin >> name;
}
```
output 

```java
#include <iostream>
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	std::cout << "Enter name:";
	std::cin >> name;
}
```

---
#### Reference
- [뽕뽑기 블로그](https://codecollector.tistory.com/381)
- [GeeksforGeeks](https://www.geeksforgeeks.org/fast-io-for-competitive-programming/)
