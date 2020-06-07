---
layout: post
title: '[Chromium] Google chome 뒤에선 어떤 동작이 일어나는가?'
subtitle: 'Explore the Magic Behind Google Chrome'
date: 2020-06-07
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium 크로미움관련블로그
lastmod : '2020-06-07 13:10:00'
---

### Explore the Magic Behind Google Chrome
위의 내용이 잘 정리된 블로그가 있어 개인적으로 옮기고자 한다. 조금 옛날 지식이
많이 존재하지만, 그래도 큰 흐름을 알기 좋은 것 같다. 개인적으로 옮기면서 그대로
옮긴 것이 아닌 개인이 가진 지식과 흐름을 넣었기 때문에 조금 불편(?) 할수도 있다.
따라서, 원본을 읽기를 원하는 사람은 [여기](https://medium.com/@zicodeng/explore-the-magic-behind-google-chrome-c3563dbd2739) 클릭해서 읽기 바란다.

블로그 내용이 방대한 분량을 축약하다보니 그냥 번역을 하면 잘이해가 되지 않는다.
그래서 본인도 이해를 하고 올릴려고 노력을 한다. 따라서, 글이 글어질 수도 있다고
생각이 들어 포스팅을 두개로 나눠서 진행하고자 한다.

---

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

#### Main / UI tread 연관된 객체들
##### RenderProcessHost
RenderProcessHost는 browser process에서 하나 이상을 소유하고 있다.
RenderProcessHost은 Render process(Renderer)와 상호작용하는 역할을 담당하며,
	주된 역할은 RenderViewHost의 view content 내용에 specific한 정보를
	renderer에 존재하는 RenderViewHost에게 전달하거나 non-view 관련된 정보를
	처리한다.

참고하고 넘어갈 부분은 RenderVeiwHost와 RenderView 간의 송신을 담당하지만,
	생각해보면 browser process에서는 RenderView가 어느 Renderer에서 왔는지 알
	필요가 있다. 왜냐하면, Browser process같은 경우 하나이지만, 다수의 Renderer가
	존재할 수 있고 Renderer들이 View 처리를 위해 RenderViewHost에 어떤걸 요청 할 수 있다. 그럴 경우 view관련된 정보가 어떤 Renderer에게 알아야 후속 처리가 가능하다. 결론적으로 ***Brwoser process에서는 Renderview 관련된 id*** 가지고 있으며 id를 가지고 view들을 관리한다. (view posting을 할 때, 소스코드와 함께보자.)

##### RenderViewHost
위에서 언급된 것과 같이, View관련 처리를 할 때 사용된다. Renderer 내
존재하는 RenderView와 서로 상호작용하기 때문에 1:1 mapping되어 동작한다. 따라서,
	RenderViewHost는 하나가 존재할 수 있지만, RenderViewHost는 여러개가 생길 수
	있다. 이 개념을 잘 이해해야한다. RenderView 가 생길 때마다
	후속 처리나 명령을 위해 RenderViewHost가 만들어져야한다. 하나의 웹페이지에서
	여러개의 View들이 생길 수 있기 때문에 다수가 생길 수 있다. 또한, 이런
	상호소통을 RenderProcessHost를 통해하기 때문에 1:n의 관계가 완성된다. 이
	객체의 주된 업무는 네비게이션 명령, input 이벤트 핸들링 그리고 web page 페인팅
	작업등을 담당한다.

##### WebContents
하나의 웹페이지를 담당한다고 생각하면 쉽다. 우리가 흔히쓰는 탭 내 존재하는
웹페이지를 떠올리자. (우선 추상적으로 생각하자) 약간 구체적으로는 View 내 존재하는 content를 말한다고 생각하면 된다.

#### Browser
non-client 영역을 담당한다. (non-client 내용은 우리가
			흔히 볼 수 있는 content를 표기하는 외의 부분을 이야기한다. 아래의 그림을
			참고하자)

non client 부분은 나중에 추가 토픽으로 추출해 다루도록 한다. 우선 대략적으로
이런 것들을 말하는구나만 알고 넘어가자

![non-client view](/img/non-cilent.png)

#### I/O thread 연관된 객체들
##### Channel
Pipe를 통해 Process간 통신을 담당한다. 구체적으로 IPC를 통해 Renderer와 Browser
process 간 통신을 도와준다. 다만, Renderer, Browser 뿐만아니라 다양한 Process
(e.g. GPU) 등에서도 Channel을 많이 이용한다.


##### ResourceDispatcherHost
Network를 통해 데이터를 인터넷으로 내보내는 역할을 한다. 사실상 외부로 나가는
게이트 웨이 역할을 한다고 보면 된다. 만약, Renderer가 인터넷을 이용하고 싶다면,
	RenderProcessHost를 이용해 network요청을하게 된다. 이후 RenderProcessHost는
	request를 만들어 ResourceDispatcherHost에 전달해 internet에 접속한다.

### Render Process (Renderer)
#### Renderer Process란 무엇인가?
Renderer로 잘 알려진 Render process는 browser와 마찬가지로 2가지 주요한 thread를
가진다. 또한, Renderer에서 가장 중요한 것은 web page를 구성한다는 점이다.
- Main thread
- Renderer thread

Main thread 같은 경우 오직 RenderProcess 객체만 다룬다. 위에서 많이 언급했듯이
Browser와 상호작용을 하는데 사용한다. 구체적으로 Browser process의 I/O thread를
통해 Renderer에서 필요한 부분을 전달하고 전달 받는 역할을 한다.

Render thread 같은 경우 web page들을 구성하고 만드는 역할을 한다. 자세하게
알아보자.

#### Render thread 연관된 객체
##### ResourceDispatcher
때로는 webpage를 다른 서버에 요청해 가져올 경우가 있다. (e.g. naver.com 에
		접속하면 naver 서버에 접근해 얻어온다.) 위에서 언급했듯이, Renderer는
인터넷에 직접적으로 접근할 수 없다. Browser process에 요청해
ResourceDispatcher로 인터넷에 접근한다.

##### Webkit
Chromium에서 사용하는 rendering engine이다. (이 자료가 오래되어서 현재 진행이
		반영되지 않은 듯하다. 현재는 webkit 이 아닌 blink이다.) Web engine 같은 경우
DOM tree를 구성하고 layout 작업을 온전히 담당한다. Webkit 내 주요한 역할을
담당하는 두가지가 존재한다.
- webcore
- javascript engine (v8)

---
#### Reference
[Zico Deng 블로그](https://medium.com/@zicodeng/explore-the-magic-behind-google-chrome-c3563dbd2739)

---
#### Memorization
- proprietary - 소유권의
