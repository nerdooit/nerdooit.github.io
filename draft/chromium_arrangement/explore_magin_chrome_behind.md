### Chromium이란
 Web browser 같은 경우 하루평균 사람들이 가장 많이 사용하는 S/W이다. 대략 60% 의
 사람이 하루에 chrome을 접속한다. Chrome은chromium을 기반으로한 S/W이다.
 Chromium은 현재 구글에서 관리하는 open web browser project 중 하나이다. Open
 source로 모든 사람들에게 공개되었으며, 상업적으로도 많이 사용되고 있다. 최근 MS
 edge browser에도 chromium을 기반으로 만들어졌다고 발표했다. Chromium에서
 지향하는 목표는 빠르고 안전하며 견고한 web browser를 만드는 것이다. Chromium 을
 분석함으로 chrome에서 어떤 일들이 일어나는지 대략적으로 확인해보자.

### Chromium 개요
 잠시 과거로 돌아가보자. 옛날 브라우저에서 tab을 열고 잘못된 사이트 접근하였을 때, 어떤 반응을 보였는지 잠시 기억을 더듬어보자.
하나의 잘못된 페이지에 접근할 경우 브라우저가 전체적으로 종료되는 것을
기억하는가? 이는 우리가 들어갔던 모든 사이트들이 한번적 꺼진다는 것을
의미한다. 요즘 같이 브라우저가 잘되어있는 세상에서는 "복귀" 라는 아름다운
버튼이 있지만 예전에는 그런 버튼 조차 없었다. Chromium은 이런 문제를 막기위해
처음으로 ***multi process architecture 구조*** 를 도입했다. (이전 포스팅에서 좀
		자세하게 다뤘다.)

Chromium에서 multi process architecture를 구성하기 위해서는 두가지 구조를
기억해야한다. 한 부분은 ***Browser part*** 와 다른 한 부분은 ***Renderer part*** 이다. 일반적으로 하나의 브라우저 프로세스와 다수의 렌더러 프로세스의 구조라고 칭한다.

### Browser process
#### Browser process란 무엇일까?
Browser process는 단순하게 browser 라고 칭한다. 여기서 칭하는 browser는 우리가
통상적으로 말하는 browser (e.g. chrome, edge, safari) 가 아니다. browser
process를 말한다. Browser process는 renderer를 다루고 UI를 어떻게 보여주는지를 관리한다. 이를 하기 위해서는 핵심 thread가 두 개 (***main / UI trhead and I/O thread***)가 존재하는데, 이를
자세하게 알아보자.

#### Main / UI tread


---
#### Memorization
- proprietary - 소유권의
