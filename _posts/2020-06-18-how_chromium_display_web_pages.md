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





#### Reference
[chromium architecture](https://www.chromium.org/developers/design-documents/multi-process-architecture)

