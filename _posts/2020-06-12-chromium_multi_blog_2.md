---
layout: post
title: '[Chromium] Google chome 뒤에선 어떤 동작이 일어나는가? (ii)'
subtitle: 'Explore the Magic Behind Google Chrome'
date: 2020-06-12
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium 크로미움관련블로그
lastmod : '2020-06-12 17:10:00'
sitemap :
  changefreq : daily
  priority : 1.0
---
### Explore the Magic Behind Google Chrome
위의 내용이 잘 정리된 블로그가 있어 개인적으로 옮기고자 한다. 조금 옛날 지식이
많이 존재하지만, 그래도 큰 흐름을 알기 좋은 것 같다. 개인적으로 옮기면서 그대로
옮긴 것이 아닌 개인이 가진 지식과 흐름을 넣었기 때문에 조금 불편(?) 할수도 있다.
따라서, 원본을 읽기를 원하는 사람은 [여기](https://medium.com/@zicodeng/explore-the-magic-behind-google-chrome-c3563dbd2739) 클릭해서 읽기 바란다.

블로그 내용이 방대한 분량을 축약하다보니 그냥 번역을 하면 잘이해가 되지 않는다.
그래서 본인도 이해를 하고 올릴려고 노력을 한다. 따라서, 글이 글어질 수도 있다고
생각이 들어 포스팅을 두개로 나눠서 진행하고자 한다.

현재 posting은 [Google chome 뒤에선 어떤 동작이 일어나는가? (i)](https://nerdooit.github.io/2020/06/07/chromium_multi_blog_1.html) 포스팅의 후속편으로 앞선 포스팅을 읽고 읽는다면 이해가 더 쉬울 것이다.

---

### Zico Deng blog의 Browser, Renderer의 전체적인 구조 그림
![chromium overview](/img/chromium_overview.png)

위의 그림은 chromium 내 존재하는 Browser process와 Render process 간의
overview이다. 그림을 보면서 설명을 따라가면서 글을 읽으면 더 쉽게 이해할 수 있다.

### Component 전달 방식
Component간 전달방식에 대해 알아보자. (i)을 통해 우리는 Chromium에서 주 사용 프로세스인 Browser Process 와 Renderer에 대해 알아보았다. 위에서 주로 언급된 RenderProcessHost와 RenderProcess 간 데이터 전달은 어떤 방식으로 일어나는지 알아보자.

#### IPC
Browser 와 Renderer는 둘 다 Process이다. Process는 상호독립존재로 자신만의 고유한 메모리 영역을 갖고 있다. 따라서, 하나의 Process는 다른 Process에 접근을 할 수 없도록 구성되어져있다. 그렇다면, 어떻게 데이터를 주고 받을 것인가? Browser Process와 Renderer는 ***IPC (inter process communication)*** 을 활용해 데이터를 주고 받는다. 운영체제를 공부하다보면 IPC에 대해 접할 경우가 많이 있다. Chromium에서는 IPC를 named pipe를 이용해 구현하고 있다. Pipe는 Browser process내 channel(ChannelProxy 객체) 과 RenderProcess에 연결되어져 있다. 통신 같은 경우 Browser에서 Renderer에게 할 수 있고 Renderer에서 Browser로 할 수 있다. 따라서, 양방향으로 구현되어져있으며 필수적으로 listener interface를 구현하고 있다. [IPC chromium](https://www.chromium.org/developers/design-documents/inter-process-communication) 문서를 읽어보자 (해당 블로그에서 추후에 IPC 자료를 정리하고자 한다.)

#### Channel Proxy
RenderProcess에서는 Browser process의 main process와 직접적으로 통신하지 않는다.
앞 포스팅에서 봤듯이, I/O thread를 이용해 통신한다. 구체적으로 작업을 I/O
thread에서 접근하는 ChannelProxy에서 처리하도록 한다. Channel과 통신하는거
아닌가? 할 수 있지만, Channel 같은 경우 thread safe가 만족되지 않는다. 즉,
	Channel proxy는 browser 와 renderer thread 사이의 동기화를 만족한다. (동기화
			개념이 부족하다면, 시스템 쪽 동기화를 구글에서 검색해서 확인해보자.) 또한,
	Channel proxy는 message filter를 통해 network request에 대해 필터링을 하고
	ResourceDispatcher에게 network request를 전달하는 역할을 한다.

#### LPC (Local Procedure call)
LPC(Local Inter-Process Communication 또는 Local Procedure Calls)은 NT 커널에서
구현된 빠른 속도의 메시지 기반 통신 메커니즘이다. LPC는 두 유저모드 프로세스들,
	유저모드 프로세스와 커널 모드 드라이버 또는 두 커널 모드 드라이버간 통신을
	하는데 사용될 수 있다. Chromium 내부에서 사용하는 IPC는 LPC를 사용한다고는
	하는데 정확하게 이해가 돠지않는다.

Local Procedure call 같은 경우 browser process 내에서 사용한다고는 되어있으나,
			명확하게 왜 사용하는지 나와있지 않아 설명을 추가하지 못했다. 이해가
			완료되면 추가하도록 하겠다.

### Architecture 분석
#### Multi process 아키텍처는 어떤 아키텍처 디자인을 사용하는가?
##### Client and Server 구조
Chromium 구성을 전체적으로 본다면, Browser Process (server) 와 다수의 Renderer (Client)
	구조이다. Browser Process는 Renderer와 IPC 통신을 하지만 각각의 Renderer들은 서로
	통신을 할 수 없다. Browser process는 특정 요구에 따라서 Renderer의 사소한
	부분들까지 다루지는 않는다. 위의 같은 구조들은 Chromium이 server and client
	구조로 디자인 되어져있다는 것을 말해준다.

##### Layered 구조
어떻게 web page가 생성되어지는가의 관점에서 보자면, chromium의 아키택처 구조는
Layered 구조와도 유사하다. 아키텍처를 대략적으로 7 단계로 나눠서 생각해 볼 수
있다.구체적으로,  ***WebKit, RenderView, RenderProcess, RenderProcessHost, RenderViewHost, WebContents, and Browser (bottom-to-up order)***  단계로 나눌 수 있다. 각 layer 별로 책임지는 부분이 다르며, OSI 7계층을 떠올려서 생각해보면 쉽다. 각 Layer는 독립적으로 동작하며 의존성이 없다.

#### Multi process 아키텍처는 어떤 품질과 특성들을 갖고 있는가?
Multi process 아키텍처에서 각 renderer는 sandbox를 유지한다. 따라서,
			Renderer들은 system에 접근제한이 있다. 만약 Renderer가 network resource 를
			얻기 원한다면, 직접 접근하는 것이 아닌 Browser process에 먼저 호출한다.
Sandbox 기법의 특징 덕에 보안적으로 위험한 파일이 renderer에 접근할 경우 OS에
접근하는 것을 제한함으로 보안을 유지한다. 또한, Sandbox 기법은 안정화에도 큰
기여를 한다. 만약 하나의 Render process에서 crash가 발생할 경우 모든 Renderer가
다 종료되는 것이 아닌 해당 Renderer 만 종료하도록 한다. 즉, 시스템을 안정화
시킨다. Multi process 기법을 채택한 chromium은 Client-server 구조로 확장성에도 용이하다.

#### 어떻게 Multi process 아키텍처는 S/W 수정하는 기능에 어떤 영향을 미치는가?
Multi process 아키텍처의 가장 중요한 강점은 전체적인 S/W 수정을 쉽게할 수 있다는
점이다. Server client 구조로 이루어진 아키텍처에서 부분적으로 일어나는
행위들인데, Browser process (server) 와 Renderer (client)로 구성된
chromium에서도 적용된다. Multi process 아키텍처에서 수정을 용이하게 하는 가장 중요한 점은, Multi process는 event driven 방식으로
동작한다는 점이다.

아래의 문장이 전체적으로 이해 되지 않아 나머지는 영어로 적어둔다. 공부를 좀 더
하고 이부분은 보완하도록 하자.

> The browser process and the render process communicate via IPC. Specifically speaking, components involved in this communication are equipped with the IPC Channel Listener interface. This decouples sender component from listener component because they do not need to know the existence of each other. The sender component can just broadcast the message to the system. The message bus will then hand it to any components who are interested in this message. With this event-driven system, we can easily add or remove render processes.

### 개인적 총평
Zico Deng 블로그는 잘 쓰여진 것 같다. 군더더기 없이 필요한 부분만 적었지만,
		 초보자가 읽기에는 다소 무리함이 있다. 프로그래밍 디자인과 패러다임의 이해가
		 좀 더 있었다면 재밌게 읽었을 것이라 생각한다. 다만, 읽으면서 모르는
		 부분들을 구글로 찾아보면서 공부한 점들이 좋았다. 중간중간에 이해되지 않았던
		 부분들은 추후 문서나 소스코드를 더 보고 정리하도록 하자.

---
#### Reference
[Zico Deng 블로그](https://medium.com/@zicodeng/explore-the-magic-behind-google-chrome-c3563dbd2739)

---
#### Memorization
- dominant - 우세한
- proprietary - 소유권의
- engender - 낳다, 만들다
- impact - 영향을 주다
