
### 메모리 회수
처음에도 언급했듯, chromium 에서는 memory를 최적화하는 것이 중요하다. 따라서, chromium을 동작할 경우에도 메모리를 어떻게 운용하느냐가 중요한 문제가 된다.

Render가 별도의 프로세스로 실행될 경우 숨겨진 텝들을 낮은 우선순위로 두는 것이 좋다. 일반적으로 사용하는 window화면을 떠올려보자. Window화면 같은 경우 최소한으로 사용되는 window들을 가용메모리 공간에 두고 관리한다. 이렇게 하는 이유는 메모리를 효율적으로 사용하기 위해서이다. 예를 들어보자.  운영체제같은 경우 메모리가 사용이 많이되어 없을 경우, Memory 공간에서 사용하고 있는 영역에 일부를 가상 disk로 바꾸는 동작을
 수행한다. 이를 Swap이라고 한다. 만약 가용공간을 사용하지 않는다면, 현재 사용자가 사용중인 프로세스의 메모리 일부를 swap하는 경우가 발생한다. 가용메모리 공간이 있을 경우 swap을 가용메모리 공간에 있는 메모리>를 하고 메모리를 유지시켜 사용중인 프로세스의 메모리를 swap하지 않을 수 있다. 이런 방법을 Chromium에서도 체택해서 사용한다. 우리가 일반적으로 tab을 계속해서 보고 있는 것이아니다. 사용하지 않는 tab의 메모리를 가용메모리 공간에 두고 관리하도록 한다. 좀 더 구체적인 동작은 memory 부분을 볼때 다루도록 하자.

### Plugin
Chromium에서는 plugin 기능을 사용하는데, 기존에는 NPAPI를 사용하였다. 지금은 PPAPI를 사용한다 정도만 알고 있자.




### Google Chrome의 백단에서는 어떤 작업을 할까?
- Chromium을 검색하다가 좋은 블로그를 발견해 내가 이해한대로 정리하고자한다.
- 혹, 정리가 마음에 들지 않는 분들은 [여기](https://medium.com/@zicodeng/explore-the-magic-behind-google-chrome-c3563dbd2739) 클릭해 원문을 읽도록 하자.

---
#### Memorization
- regard - 간주하다
- solely - 단독으로

---
#### Reference
[Zico Deng blog](https://medium.com/@zicodeng/explore-the-magic-behind-google-chrome-c3563dbd2739)

