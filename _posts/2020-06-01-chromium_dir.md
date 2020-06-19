---
layout: post
title: '[Chromium] Getting Around the Chromium Source Code Directory Structure'
subtitle: 'Chromium의 소스코드 디렉토리에 대해 알아보자'
date: 2020-06-01
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium  chromium_document
lastmod : '2020-06-01 21:30:00'
sitemap :
  changefreq : daily
  priority : 1.0
---

### Chromium source code directory 전반적인 부분
#### Chromium 핵심 2가지 부분
- Browser process
  - Browser process는 main process 로 UI / IO의 전반적인 부분을 담당한다.
- Rendering process
  - Rendering process 는 tab 별로 존재하는 sub process 개념으로 보면 된다.  다만, tab 별로 process가 하나 일수도 있고 아닐수도 있다.) Browser process에 의해 IO 동작을 전달받는다
. Rendering동작의 핵심 부분을 담당하는 web engine 동작을 수행한다. Chromium에서 web engine을 blink라 부른다.

#### Top-level 프로젝트
Chromium 소스를 다운 받아 확인해보면 다양한 디렉토리들이 존재한다. 최상위 각 디렉토리가 어떻게 범주화 되어져 있는지 확인해보자.

***android\_webview***
- Android 소프트웨어의 web view를 나타내는 부분을 간략화해 interface로 제공해주는 소스들을 모아둔 곳이다(facade). 개별적인 android의 application 개발에 필요한 것에 대한 정보는 >여기에 들어있지 않다.

***apps***
- Chrome 관련된 packaged app들이 존재한다.

***base***
- Chromium 내 모든 프로젝트에서 공유하는 부분이다. base 디렉토리에는 일반적인 string이나 일반적인 utility들이 존재한다. base 내 존재하는 코드들은 C++ 능력을 향상시키에 좋은 교보재들이다.

***breakpad***
- Google open source 크래쉬 리포팅 프로젝트이다. 최신 버전에는 이 디렉토리가 존재하지 않는다. 이름이 변경되었는지는 히스토리를 파악할 필요가 있다.

***build***
- Build 와 연관된 설정들이 존재한다.

***cc***
- Chromium 내 compositor를 담당하는 부분이다. (impl side painting동작에서 자세하게 언급할 필요가 있다.)

***chrome***
- 디렉토리 이름과 같이, chrome 브라우저 내 필요한 것들이 존재한다.

***component***
- Content module이 가지고 있는 모듈들이 저장된 곳이다. 가장 최상된에서 사용되는
부분들이 여기에 저장되며, 공용으로 사용되는 것들이 많다.

***content***
- sandbox로 구성된 browser process에서 multiprocessing 동작을 수행할 수 있는
핵심 코드가 구성된 부분이다.

***device***
- Cross-platform을 위한 부분이다.

***net***
- network 라이브러리를 개발하는 부분이다.

***skia + third_party/skia***
- Google에서 개발한 skia graphic library가 존재하는 부분이다.

***sql***
- 파일기반 데이터 베이스인 SQLite의 wrapper함수들이 존재하는 부분이다.

***third_party***
- 크고 작은 외부 라이브러리들이 존재하는데, 여기에는 압축, 디코딩, web engine 부분들이 존재한다. (당시, web engine은 webkit에서 fork한 후 third\_party directory에 두고 수정한 방식으로 진행해왔다. 근래에 코드를 보면, blink라는 부분이 있으며, web engine은 blink 부분에 존재한다.)
	- .../blink/renderer
		- web engine의 핵심 부분이다. web engine이 무엇을 하는지 잘 모르는 사람들이
		있는데, 간단히 말하면 우리가 흔히 작성한 HTML을 화면에 뿌려주는 역할을
		한다고 생각하면 된다. (실은 더 복잡하지만..)

***ui/gfx***
- 공유 graphic class 들이 존재한다. Chromium의 UI를 기반의 형태를 갖추고 있다.

***ui/views***
- 추후 view의 구조를 알아보겠지만, UI 관련된 모든 것들이 존재한다고 보면 된다.
(event 처리, UI 개발, rendering을 위한 부분 까지 다 포함)

***url***
- Google의 open source인 url parsing 동작을 하는 소스코드가 들어있다.

***v8***
- Javascript 파싱 및 동작을 위한 부분들을 담당한다. 이 또한 구글에서
opensource로 제공한다.

#### Chromium Directory 도식화
![chromium_dir](/img/chromiumDir.png)

- 위의 그림은 전체적인 도식화 그림을 나타낸 것이다. 다만, 위의 그림이 정확하게 지금의 chromium source code와 일치하다고 이야기 할 수 없다. 자료가 꽤 오래전에 작성된 점을 감안하고 확인해야한다. 앞으로 chromium 소스코드를 분석하고 정리하면서, 이 부분에 대한 update를 주기적으로 할 것이다. 

---
#### Reference
- [getting-around-the-chrome-source-code](https://www.chromium.org/developers/how-tos/getting-around-the-chrome-source-code)
- [component source code tree](https://chromium.googlesource.com/chromium/src/+/master/components/)

---
#### Memorization
- facade - 허울, 표면
- uppermost - 가장 높은
