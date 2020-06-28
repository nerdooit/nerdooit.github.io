## Blocking / Non Blocking / Synchronous / Asynchronous
위의 주제에 대해 다뤄보고자 한다. 평소에 많이 전달받아 익숙한 단어들이지만,
	실제로 어떻게 구별하는지 어떤 방식에서 차이가 있는지에 대해 잘 알지 못해
	정리를 해보고자 한다.

들어가기전, 아래의 그림을 이해하자.

![routine](/img/routine.png)

하나의 함수의 실행과정을 나타낸 것이다. 실모양은 thread라고 부르며, 하나의
thread가 함수 루틴을 끝낸 그림을 나타낸다.

---

### Synchronous / Asynchronous
아래의 동작에 대해 알아보기 전에, 문자의 어원을 보자. Synchronous는 Syn + chronous 이렇게 나눠져있다. ous 같은 경우 형용사형으로 품사를 변경한다 치고 크게
영향을 미치지 않는다. 중요한 것은 syn + chron이다. syn의 뜻은 ***together***를 뜻한다. chrono는 c++ 헤더 파일에도 존재하 듯, 시간을 의미한다. Synchronous는 ***함께 시간을 마추는*** 정도로 이해할 수 있다. 즉, 함께 시간을 맞춰 동작하는 이라고 프로그래밍 입장에서는 이해할 수 있다. A+Synchronous는 A라는 부정 즉, (!)의 의미를 갖고 있으므로 ***함께 시간을 마추지 않는*** 정도로 해석할 수 있다.

Synchronous (이하 sync) / Asynchronous (이하 async)는 어원에서 볼 수 있듯,
						***시간*** 확인하는 것이 중요하다. 프로그래밍 입장에서 생각해보자면,
						***어떤 대상*** 이 실행하는 것도 중요하다. "시간, 대상" 두 가지를
						중점에 두고 이야기 해보자.

#### Synchronous
Sync는 두 가지 이상의  루틴(function, thread 등)이 서로 시간을 맞춰 동작하는 것을
말한다. 시간에 초점을 맞추고 보는 것이 중요하다. 루틴을 수행하는 대상이 루틴들의
입력 / 출력 시간을 알고 있을 경우를 "Synchronous 하다" 라고 한다. 예를 들면,
Lock을 생각해보자. 하나의 구간에 두개의 루틴(thread) 가 ***동시에*** 수행할 경우
Synchornous하게 처리하는 기법이 있다. 다른 예시는 아래의 그림을 보자.

![sync](/img/sync.png)

루틴을 처리하는 대상에서 두 가지의 루틴에 대해 언제 시작하고 언제 끝나는지 알고
있으며, 이를 연속적으로 처리하기 위해 A루틴 이후 B루틴을 시작하게 한다 라는
방식으로 수행하는 것은 "Synchronous 하다" 라고 한다.

#### Asynchronous
Async 같은 경우 sync의 반대라는 것은 너무 자명하다. 즉, 서로 시간을 맞춰서
동작하지 않는 것을 의미하며, 루틴들의 시작 / 끝 시간을 알지 못하는 경우를
말한다.

![Async](/img/async.png)

루틴을 수행하는 대상에서 모든 루틴의 시작과 끝을 알 수 없는 경우가 존재한다. 위
그림과 같이, 하나의 대상에서 두 개의 루틴을 모두 관리하지 않고 B 루틴을 다른
대상에게 맡길 경우 B루틴이 언제 종료되는지 알 수 없다. B루틴이 종료된 후
***시그널, 콜백루틴*** 을 전달해야 A 루틴을 수행하는 ProcessA는 B루틴이
종료되었구나 를 알 수 있다. 이런 상황을 ***Asynchronous 하다*** 라고 한다.

Sync / Async는 하나의 시간의 관점에서 봐야한다. 시간의 관점이기 때문에 모든
대상이 동작을 하게 될 경우 Sync / Async한지가 붙게 된다. 이후 Blocking /
Non-blocking 동작에서도 이 동작들이 Sync / Async하게 동작하는지는 다 붙게 되어져
있다. 대상의 시간적 관점에서 보기 때문에 결합되어 의미가 해석 된다. 그러다 보니
햇갈리는 경우가 발생하게 된다. 이 부분을 주의하자.

### Blocking / Non-Blocking
Blocking(이하 블로킹) / Non-Blocking (이하 논블로킹)은 Sync / Async 동작과
구분이 되지 않고 같다고 생각하는 사람들이 많이 있다. (본인도 여기에 포함된다.)
	이는 잘못된 개념이며, 서로 관점이 다르다는 것을 기억해야한다. 블로킹 /
	논블로킹은 ***직접 제어할 수 없는 대상에 대한 처리*** 를 말한다. 직접 제어할
	수 없는 대표적인 모델은 OS이다. OS 기법 중 IO 동작에서 많이 사용한다. (IO 같은
			경우 속도차가 극명하게 나뉘기 때문에 위의 동작이 적절하게 사용됨.)

직접제어 하지 못하는 영역을 처리할 때, 두가지 방식이 존재한다.
- 기다린다 => Blocking
- 기다리지 않는다 => Non-Blocking

직접제어하지 못하는 루틴도 하나의 루틴이다. 이 루틴을 요청하고 이 요청을 기다려
끝나는 시점을 파악하면 Sync한 것이고 아닐 경우 Async하다고 볼 것이다. 즉, 시간적
관점은 어떤 루틴을 수행할 때 항상 붙어다닌다는 점에 유의하자!

#### Blocking
Blocking 직접 제어할 수 없는 대상에 대해 ***기다리는 경우***를 말한다. 대표적인
예제로 OS의 IO동작을 떠올릴 수 있다. IO 같은 경우 cpu에서 필요한 데이터를 memory
/ HDD 를 통해 읽어 오거나 쓰는 동작을 말한다. 만약 cpu에서 데이터가 필요해
read연산을 수행할 경우 데이터를 읽어오는 동작을 수행하는데, 데이터를 읽어오는
동안 cpu는 기다리는 경우가 많다. 이를 블로킹 된다라고 한다.

#### Non-blocing
Non-blocking같은 경우 blocking 동작의 반대되는 개념으로 무한정 기다리지 않는
것을 말한다. 즉, 직접 제어할 수 없는 대상에 대해서는 신경 쓰지 않겠다는 것을
의미한다.

위는 정의적 관점이고 이를 어떻게 해석하고 어떻게 사용하느냐에 따라 프로그램의
성능 혹은 적절한 사용을 할 수 있다. 프로그래밍 관점에서 어떻게 사용되는지 보자.








---
### Reference
- [개발 이야기](https://velog.io/@codemcd/Sync-VS-Async-Blocking-VS-Non-Blocking-sak6d01fhx)
- [컨텍스트 스위치](https://jins-dev.tistory.com/entry/%EC%BB%A8%ED%85%8D%EC%8A%A4%ED%8A%B8-%EC%8A%A4%EC%9C%84%EC%B9%98Context-Switching-%EC%97%90-%EB%8C%80%ED%95%9C-%EC%A0%95%EB%A6%AC)
- [김짱쌤](https://ozt88.tistory.com/20?category=123069)
-[AIO 정리](https://www.joinc.co.kr/w/Site/Network_Programing/AdvancedComm/AIO)

-[정리2](https://victorydntmd.tistory.com/8)
-[소켓 서버 개념](https://velog.io/@jyongk/TCP-Socket-Blocking-Non-Blocking)
