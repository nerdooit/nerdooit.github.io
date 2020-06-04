---
layout: post
title: '[Chromium] Chromium 멀티 프로세스 아키텍쳐'
subtitle: 'Chromium의 핵심 아키텍쳐에 대해 알아보자'
date: 2020-06-03
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium c++ 'web browser engine'
lastmod : '2020-06-03 23:30:00'
---

## Multi-process Architecture
Chromium에서 작성된 2008년에 작성된 자료로 지금과 다른 점이 많다. 다만, 기본 골자는 비슷하다고 생각한다.

### 기존 시스템의 문제
Bug가 존재하지 않고 crash가 생기지 않는 rendering engine을 만드는 것은 물리적으로 불가능하다. 즉, 완벽하게 동작하는 web engine을 만드는 것은 불가능하다. 생각해보면, 2006년 경의 웹브라우저는 컴퓨터시스템의 특징을 모방했다. 웹브라우저는 당시 시스템 중 하나인  단일 사용자, 협력식 멀티 테스킹 운영체제 방식 (non-preemptive multitasking, 선점형식이 아닌 스케쥴링 즉, 작업을 순차적으로 진행함 을 고수해왔다. 이 방식은 웹 브라우저에서 오작동 할 경우 웹페이지가 전체적으로 다운 될 수 있다는 것을 의미한다. 즉, 지금은 생각해볼 수 없지만 하
나의 텝에서 오작동 할 경우 모든 텝들이 꺼지는 경우가 생길 수도 있다는 말이다.

이런 문제점을 해결하기 위해, 컴퓨터 시스템에서는 멀티프로세스 동작방식을 고안했다. 멀티프로세스 같은 경우 쉽게 말해 다수의 프로세스 별로 시스템을 동작시키고 하나의 시스템으로 인해 모두가 다운되는 방식을 막을 수 있는 방식이다. 웹브라우저에서도 멀티프로세스 동작방식을 도입해 하나의 시스템의 다운으로 다른 프로세스에 영향을 미치지 무결성) 않도록 한다. 그렇다면 이런 의문을 가질 수 있다. 왜? 이렇게 좋은 방식을 옛날에는 도입하지 않은건가? 예전에는 하드웨어 성능이 지금보다 좋지 못했다. 따라서, 1bit라도 아껴서 사용하는 코딩을 사용할 정도로 메모리를 아끼고자 했다. 하지만 최근들어서는 하드웨어 성능이 향상되고 하드웨어 가격이 많이 떨어짐에따라 멀티프로세스를 도입하기 좋은 세상이 왔다. 멀티프로세스를 동작하기 좋은 세상이지만 메모리공간은 늘 문제가 된다. 멀티프로세스 방식을 도입할 경우 메모리 용량을 많이 차지하기 때문에 문제(프로세스는 독립적인 메모리 공간을 가져야함.. 가 된다. Chromium 개발자들도 메모리를 줄이기 위해 엄청난 노력을 하고 있다는 것을 안다.

### 아키텍트 개요
- Browser process를 위해 탭 별 개별 프로세스 관리
  - 버그나 작은 결함으로 인해 어플리케이션 전체가 다운되는 것을 막기위해 텝 별 관리한다.
  - 탭 별 랜더러 프로세스가 존재하는 것은 아니다. 이 부분은 추후 공부를 하면서 다루도록 한다.

- 각 Rendering engine이 다른 프로세스나 나머지 프로세스들에 직접 접근 제한
  - 프로세스는 상호 독립적 객체로 프로세스간 데이터 공유는 엄격하게 제한 한다.
  - 핵심적으로 메모리보호 와 OS 접근을 제한하기 위함이다.

- Main process는 Browsering 역할
  - Browser process라고 불리는 main process는 UI, Tab을 관리하고 Plugin process를 관리한다.
  - 최근들어 GPU 프로세스도 관리하는 것으로 알고있다.  추후 정리)

- Rendering 동작은 Rendering process가 담당
  - Rendering동작을 담당하는 프로세스가 존재한다. (Renderer라고 부름)
  - Blink open source layout engine을 사용한다.
  - HTML, CSS, layout, compositing 등을 담당한다.

![multiprocess](/img/chromiumMultiProc.png)

### Renderer 관리
- 각 Render process ***전역(Global) Render process***를 포함
  - Render process는 Browser process와 통신관리를 하고 상태를 유지 관리한다.

- Browser process는 ***RenderProcessHost*** 객체를 통해 Renderer와 통신함
  - Chromium IPC (현재는 mojo로 변경된 것으로 안다 를 사용해 Browser proc. 과 Renderer는 통신을 한다.
  - Renderer에서 다른 Renderer에 데이터를 요청하기 위해서는 Browser process를 거쳐야한다.

### View 관리
- 각 Renderer는 하나 또는 다수의 View 객체 (RenderView object)를 포함
  - RenderView는 tab 내의 컨텐츠와 일치하며, Renderer에 의해 관리된다.
  - View를 이용한 Browser process와의 통신은 RenderViewHost를 통해 관리한다.
    - RenderView <-> RenderViewHost (view 관리)
    - RenderProcess <-> RenderProcessHost (process 통신관리)

- View는 ID로 관리
  - View는 같은 랜더러 내 여러개가 존재할 수 있다. (e.g. 텝 내 여러개의 이미지 혹은 여러개의 컨텐츠가 포함된 웹사이트)
  - Renderer는 view를 관리하기 위해 viewID를 부여한다.
  - Renderer에서 부여한 ViewID 같은 경우 Renderer 내에서는 유효하지만 Browser process에서는 유효하지 않다. (다수의 Renderer 존재)
  - Browser process에서 view를 식별하기 위해서는 RendererID와 ViewID를 알고 있어야한다.
  - 위의 두가지를 안다면, RenderProcessHost를 통해 Renderer 와 RenderView로 메세지 보내는 방법을 알 수 있다.

### Component와 Interface
- Renderer 에서 Browser process로
  - Renderer는 Browser process에 존재하는 RenderProcssHost 객체를 이용해 IPC 통신을 수행한다.
  - Renderer 당 RenderProcess가 존재하며, RenderProcess와 RenderProcessHost간의 IPC 통신을 통해 데이터를 주고 받는다.

- Browser process에서 Renderer로
  - Browser object는 Browser에서 가장 최상단을 말한다.
  - Browser process 내 존재하는 RenderProcessHost는 통신을 담당한다.
  - RenderProcessHost 는 연결이 구성된 Renderer수만큼 존재한다.
  - RenderView 객체는 RenderProcessHost객체를 통해 RenderViewHost객체와 통신한다.
    - 이 부분은 view를 다룰 때 자세하게 보도록하자.
  - Input 관련된 처리는 RenderWidget이라는 객체를 통해 대응한다. browser에서는 RenderWidgetHost라는 객체를 이용해 처리한다.
    - view를 다루는 부분에서 widget관련된 정보도 함께 다루도록 하자.

### Renderer 공유
일반적으로, 각 창이나 텝을 열 경우 하나의 프로세스가 만들어진다. Browser process는 하나의 새로운 Render process를 만들고 RenderView 객체를 생성하라 요청한다.

가끔 하나의 process가 만들어지지 않고 renderer를 공유하는 경우가 생긴다.
- 웹 어플리케이션이 새로운 윈도우를 열 경우
  - Javascript를 이용해  ***window.open***을 요청함.
  - 위와 같은 함수를 호출할 경우 새로운 window or tab을 생성한다.
  - 새로운 window or tab을 생성할 때, 기존의 domain에 진입한 process있으면 재활용한다.
  - process의 개수가 너무 많아도 재활용한다.

#### 망가진(?) Renderer 식별
Browser process에 존재하는 각 IPC는 process의 상태를 확인한다. 만약 renderer가 crash나 bug로 인해 망가진다면, Browser process는 IPC를 통해 signal을 전달받는다. 현재로는 signal을
 전달받으면, user에게 sad tab을 띄워 지금 process가 망가졌다(?) 라고 알려준다. 알려 줄 때, reload버튼을 같이 전달함으로 새로운 navigation을 수행하도록 하거나 reload를 통해 web page를 다시 구동시켜볼 수 있도록 한다.

#### Renderer sandboxing
Multi process 동작을 구현하기 위해선, 각 Renderer들이 sandboxing 되어야한다. 프로세스는 상호 독립객체로 개별적 메모리를 소유한다. 프로세스간 데이터 공유가 불가능함으로 Renderer 별로는 접근이 불가능한 Sandboxing 모델로 구축되어야한다.

Chromium Sandboxing for renderer
- Network 동작 제한 (browser process를 통해 networking 함)
- File system 동작 제한 (OS를 통해 file 접근 권한 요청)
- Window object 접근 제한 (Display를 위한 window 객체도 접근이 제한 된다.)
    - 사용자에게 보여주는 화면과 관련된 객체들은 window 객체라고 칭한다. window 객체에 접근을 제한 할 경우 손상된 Renderer(by hacker..?)가 새창을 열거나 키 입력을 캡처하지 못한다.

### 메모리 회수
처음에도 언급했듯, chromium 에서는 memory를 최적화하는 것이 중요하다. 따라서, chromium을 동작할 경우에도 메모리를 어떻게 운용하느냐가 중요한 문제가 된다.

Render가 별도의 프로세스로 실행될 경우 숨겨진 텝들을 낮은 우선순위로 두는 것이 좋다. 일반적으로 사용하는 window화면을 떠올려보자. Window화면 같은 경우 최소한
으로 사용되는 window들을 가용메모리 공간에 두고 관리한다. 이렇게 하는 이유는 메모리를 효율적으로 사용하기 위해서이다. 예를 들어보자.  운영체제같은 경우 메모리가 사용이 많이되어 없을 경우, Memory 공간에서 사용하고 있는 영역에 일부를 가상 disk로 바꾸는 동작을
 수행한다. 이를 Swap이라고 한다. 만약 가용공간을 사용하지 않는다면, 현재 사용자가 사용중인 프로세스의 메모리 일부를 swap하는 경우가 발생한다. 가용메모리 공간이 있을 경우 swap을 가용메모리 공간에 있는 메모리를 하고 메모리를 유지시켜 사용중인 프로세스의 메모리를 swap하지 않을 수 있다. 이런 방법을 Chromium에서도 체택해서 사용한다. 우리가 일반적으로 tab을 계속해서 보고 있는 것이아니다. 사용하지 않는 tab의 메모리를 가용메모리 공간에 두고 관리하도록 한다. 좀 더 구체적인 동작은 memory 부분을 볼때 다루도록 하자.

### Plugin
Chromium에서는 plugin 기능을 사용하는데, 기존에는 NPAPI를 사용하였다. 지금은 PPAPI를 사용한다 정도만 알고 있자.

---
#### Memorization
spawn - 낳다.
For now - 현재로는. (지금까지 아니다..)

---
#### Reference
[chromium architecture](https://www.chromium.org/developers/design-documents/multi-process-architecture)

