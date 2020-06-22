---
layout: post
title: '[Chromium] How Chromium Displays Web Pages'
subtitle: 'Chromium은 어떻게 web page들을 보여주는지에 대해 알아보자'
date: 2020-06-18
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium chromium_document
lastmod : '2020-06-18 21:45:00'
sitemap :
  changefreq : daily
  priority : 1.0
---

### How Chromium Displays Web Pages.
이 문서 같은 경우 가장 밑단에서부터 어떻게 크로미움에서 웹페이지를 보여주는 가를 설명하는 문서이다. 문서의 내용을 이해하는데 도움이 줄만한 자료를 공유한다. [여기1](https://nerdooit.github.io/2020/06/03/chromium_multi_process.html) [여기2](https://www.chromium.org/developers/design-documents/multi-process-resource-loading) 를 클릭해  한번 읽어보기 바란>다.

문서 같은경우, 본인이 해석하고 이해한 부분을 바탕으로 작성하기 때문에, 본인 주관이 많이 들어간다. 어쩌면 틀린 부분이 존재할수도 있다. 다만, 최대한 많이 조사하고 이해하기 쉽게 작성하려고 노력했다는 점만 알아주길 바라며, 좀 더 확실한 이해를 원하는 사람은 [원문](https://www.chromium.org/developers/design-documents/displaying-a-web-page-in-chrome) 을 읽어>보기 바란다.

### Conceptual application Layer
아래의 그림은 개념적인 application layer들을 설명한다. 다소 오래된 문서랑 현재 다른점들이 존재한다. 다만, 주요한 골자는 변함이 없기 때문에 골자를 이해하는데 초점을 맞추자.

![application layer](/img/application_layer.png)

위의 그림에서 각 박스들은 추상적인 layer들을 나타낸다. layer는 상위 수준의
레이어에 대해 독립적이다. 즉, 의존도가 없다.

- Webkit : 랜더링 엔진으로 safari, chromium에서 사용한다. chromium 같은 경우
현재는 webkit이 아닌 자체적 웹 엔진인 blink 엔진을 사용한다. 하지만, webkit의
잔여물은 아직 남아있다.
- Glue : Webkit에서 사용하는 type들을 chromium 타입으로 변경하는 layer이다. 상위
레이어에 영향을 미치지 않기 위해 chromium type으로 변경하는 역할을 한다.
- Renderer / Render host : 우리가 앞서 배웠던 chromium의 multi process구조를
담당하는 부분이다. 가운데 경계선을 따라 명령을 전달하고 대신 처리하는 구조로
이뤄 진다.
- WebContents : View 내 contents를 구성할 때 사용한다. (Contents 부분은
		추가적으로 정리를 할 것이다.) 우선, 단순하게 tab 내 존재하는 contents를
다룰때 사용한다고 생각하자.
- Browser : 브라우저 윈도우를 나타내며, 다수의 Web Contents를 나타낸다.
- Tab Helpers : Web contents에 부착 될 수 있는 개별 객체이다. Browser 객체는
분류하여 붙이는 역할을 한다. (예를 들면, favicon, infobar 등)

### WebKit
Chromium은 web page를 구성하는 engine으로 ***Wekit (현재는 blink)***를 사용한다.
Webkit은 layer등을 다루는 기능인 webcore와 Javascript core로 구성되어져있다.
Javascript 엔진은 구글 open source로 제공되고 있는 v8을 사용한다. Chromium은
apple에서 사용하고 있는 webkit 부분을 사용하지 않고 일반적으로 사용할 수 있는
부분만 채택해 사용한다. apple 같은 경우 OSX 기반으로 api가 작성되기 때문에
chromium으로 가져올 수 없다.

현재는 blink로 구성되어 chromium에 최적화된 web engine을 사용한다. (history
		파악정도만 하자)

#### The WebKit glue
Chromium 같은경우 Webkit과 다른 코딩스타일 (chromium은 tab 2칸, webkit은 4칸)을
사용하며, code layout도 다르다. ***Webkit glue*** 같은 경우 Google의 코딩 규약과
스타일을 webkit에 적용해 Chromium 내부에서 Web engine 사용을 편리하도록 한다.
예를들면, webkit내 존재하는 WebCore::String 을 std::string으로 바꿔 주는 경우나
KURL 대신 GURL로 변경해준다. glue code는 /webkit/glue에 존재한다. (현재는
		존재하는 것으로 보이지는 않으며, blink화 되면서 왠만한 코드들이 다시 작성된 느낌이다.) glue 객체 같은 경우 webkit의 이름을 완전히 바꾸지 않고 최대한 비슷하게 유지하도록 한다. (가령, WebCore::Frame 같은 경우 WebFrame으로 변경)

Glue의 가장 큰역할은 편리성도 있지만, 호환성 문제를 최소화하는데있다. Webkit
내부과 chromium을 연결하는 역할을 하며, Webkit의 소스코드를 변경함으로
chromium에 영향을 미치지 않는 것을 목표화한다. WebCore의 데이터 타입들은
Chromium에서 사용되지 않는다. Webkit에 데이터나 함수가 추가 되더라도 glue만
변경하거나 추가하면 되고 chromium 소스코드를 직접 변경하지 않는다.

코드를 보면 "test shell" 이라는 application이 존재한다. 이 app 같은 경우 Webkit
port 와 glue 동작을 테스팅 하기 위해 사용된다. Test shell 같은 경우 chromium과
webkit이 glue를 사용하는 부분을 정확히 모사한다. Test shell은 단순하게
동작하도록 되어져 있으며, 개발자가 새로운 기능을 추가할 경우 쉽게 확인해볼 수
있다. browser 설정, thread, process 같은 복잡한 설정을 따로 할 필요가 없다.

Glue 같은 경우 말 그대로 "접착제" 역할을 한다. 호환성을 유지하기 위해서,
		 webkit과 chromium 중간에 붙어있다. 다만, blink로 바뀌면서 이런 부분들이
		 많이 필요하진 않는 것으로 보인다. blink 내부에서 사용하는 rendering이나
		 이런 부분들에서는 호환이 필요하지만, 더 높은 상위 계층에서는 필요하지
		 않아보이며, 실제 코드에서도 glue영역은 식별되지 않고 있다. 이전에는
		 이런것들이 있었으며, webframe과 같이 web이라는 prefix가 보이면 webkit에서
		 가져온 것이구나 정도만 생각하도록하자. 

### The render process
Renderer 의 대한 이야기는 이전 포스팅에 많이 다루었던 것 같다. 현재 포스팅을
작성하는 이유는 이전 보다 그림이 잘 나와있어서 추가하고자 한다. 이해가 잘 가지
않는다면 [이전 포스팅](https://nerdooit.github.io/2020/06/03/chromium_multi_process.html)을 참고하도록 하자.

![render process](/img/render_process_how.png)

위의 그림과 같이 Renderer 구조이다. Renderer는 크게 웹엔진 부분인 webkit (blink ) 부분과 Render process 부분으로 나뉜다. Render process의 코드는 그렇게 많지않으며, 주된 역할은 IPC를 이용해 browser 내 존재하는 IO thread와 통신하는 역할을 한다. 렌더러를 담당하는 객체들을 구체적으로 보자.

Renderer에서 중요한 객체는 3가지가 존재한다.
- RenderView
	- Renderer에서 가장 중요한 객체로 꼽을 수 있다. 이 객체같은 경우 하나의
	웹페이지를 처리하는 역할을 한다. Browser process에서 필요한 명령어를
	전달받거나 네비게이션 역할을 담당하며, 웹페이지를 구성하는 필수적 요소를
	한다고 생각하면 된다. 소스코드의 위치는 /content/renderer/render_view_impl.cc
	이며, header file로 가서 확인해보면 알겠지만, 많은 기능들이 render frame
	impl로 옮겨갔다는 것을 알 수 있다. preference 설정하는 부분은 남아있었던 걸로
	기억한다.

- RenderWidget
	- Widget 같은경우 따로 추출해 포스팅을 할 예정이다. 간단하게 이야기하자면,
	input event handling 역할과 painting을 담당한다. 소스코드 위치는
	content/renderer/render_widget.cc 이다.

- RenderProcess
	- Render process 같은 경우 위의 언급과 같이, global renderer process를 이용해
	browser process와 통신하는 역할을 한다. 소스코드의 위치는
	content/renderer/render_process.cc 이다.

위의 내용을 보면 의문점이 생기는 것들이 몇 가지 존재할 수 있다. 그 중 가장
의문점이 많이 생기는 부분은 ***RenderView와 RenderWidget의 차이는 무엇인가?***
이다. 문서에도 언급되어있고, 개인적으로도 궁금했던 부분이다.

RenderWidget은 내부적으로 Webcore::Widget을 가지고 있다. RenderWidget같은 경우
기본적으로 screen에 나타나는 input event handling을 하고 window 창 관련된 painting 작업을 한다.
RenderView 같은 경우 위의 그림과 같이, RenderWidget을 상속받고 있으며 탭 내의
content를 구성하거나 window popup등을 처리한다. widget의 input과 painting
처리요청을 widget에 전달하는 역할도 한다. 따라서, Widget 같은 경우 View에 의해
관리 된다고 볼 수도 있는데, 관리 되지 않는 경우가 하나 존재한다. Web page 내
존재하는 select box (아래 화살표 방향을 눌러 리스트를 보는 박스)는 widget
독단적으로 처리한다. 이 부분은 View에 의해 구성되는 것이 아닌 native window를
통해 구성되어지도록 되어져있다. (옛 문서라 지금은 다르게 구성될수도 있을 것
		같다는 생각을 한다..)

#### Threads in the renderer
Renderer에는 main thread / render thread 두 가지 중요한 thread가 존재한다. 이
부분은 [chromium 관련 블로그](https://nerdooit.github.io/2020/06/07/chromium_multi_blog_1.html)를 통해 자세하게 다뤘다. 복습차원으로 한번 보자. 우선, render thread는 rendering 동작 중 메인이라고 불릴 수 있는 곳인 RenderView, Webengine(webkit, blink)을 수행하는 역할을 한다. 그 외의 처리는 main thread가 담당하는데, 대표적으로 browser와 통신을 담당한다. Browser에게 메세지를 RenderProcess를 이용해 main thread가 전달받고 전달하는 역할을 한다. 일례로 Render process의 메세지를 browser process에 동기적으로 보내는 경우가 존재하는데, browser가 계속 결과를 요청하는 케이스가 존재한다. 따라서, browser process가 필요하다고 요청을 하게 되면 render process가 보내는 역할을 한다. 구체적인 사례는 cookie를 떠올리면 된다.

- cookie의 전달과정
- JS 에 의해 cookie가 요청됐을 경우, page에 대한 쿠키를 browser 에게 전달한다. 그 경우에
render thread는 block되고 main thread는 관련된 모든 message들을 browser에게
메세지가 올 때까지 queue에 넣고 대기한다. 이후 메세지를 전달받으면 block을
풀고 정상적으로 render thread가 동작한다.

### The browser process
Browser process는 low / high level로 나누어 볼 수 있다. 결국에는 I/O thread와
main thread로 나뉘는 것이며, 이 부분도 지난 포스팅을 통해 자세하게 다뤘다. 다만,
		 소스코드 위주로 IPC에 대한 내용을 중점적으로 확인해보자.

![browser process](/img/browser_process_how.png)

#### Low-level browser process objects
IPC를 이용한 Renderer와의 통신은 해당 부분에서 처리가 된다. 또한, 사용자에게
보여주는 부분에 대한 방해를 제거하기 위해 network 처리도 담당한다.

객체 단위로 어떻게 동작하는지 확인해보자.
browser내 main thread가 RenderProcessHost를 처음 초기할 때, render process와
channel proxy가 named pipe로 함께 구성되어진다. 해당 객체들은 I/O thread에
의해 동작되고 renderprocess에 의해 데이터를 전달받거나 해당 데이터를
RenderProcessHost로 전달하는 역할을 한다. RenderProcessHost는 main(UI) thread에서
동작하고 있다. 그림에서 보이는 것과 같이, message filter가 channel내 생성되게
되는데 I/O thread가 처리할 수 있는 부분, 예를들면 network request 등과 같은
처리를 담당하게 된다. network resource에게 전달하는 역할을 한다고 보면 된다.
해당 filtering 동작은 ResourceMessageFilter::OnMessageReceived 함수에서
발생한다.

Main(UI) thread에서 동작하는 RenderProcessHost는 view-specific한 메세지들을
적절하게 RenderViewHost로 전달하는 역할을 한다. 이 전달하는 동작들은
RenderProcessHost::OnMessageReceived 함수에서 발생한다.

#### High-level browser process objects
앞서 본 것과 같이 대부분의 view-specific한 메세지들은 RenderViewHost로 전달된다.
대부분은 여기서 처리되는데, 처리되지못해 남겨진 것들은 RenderWidget에서
처리된다. 각 플랫폼 별 자신의 view class를 처리하기 위해 native view system을
구축한다. 즉, chromium 과 호환적으로 동작하기 위해 platform에서는 개별적인
renderviewhost를 구축한다. 이 부분은 통합된 것으로 알고 있다. 확인되면
갱신하도록 하겠다.

RenderView / Widget 위에는 WebContents 객체가 있으며 대부분의 메시지는 실제로 해당 객체에 대한 함수 호출로 종료된다. WebContent는 탭 내 웹페이지를 나타낸다. content module에서 최상위 레벨 오브젝트이며, 직사각형보기에서 web 페이지를 표시한다.

---

#### Memorization
- appropriate - 적절한
- Among other things - 그중에서
- downside - 단점

#### Reference
[chromium document](https://www.chromium.org/developers/design-documents/displaying-a-web-page-in-chrome)

