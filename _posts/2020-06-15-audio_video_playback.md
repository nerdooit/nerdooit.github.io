---
layout: post
title: '[Chromium] Audio / Video Playback'
subtitle: 'Chromium의 Audio / Video 재생 동작을 알아보자'
date: 2020-06-15
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium chromium_document web_media
lastmod : '2020-06-15 19:10:00'
sitemap :
  changefreq : daily
  priority : 1.0
---
### Audio / Video 재생
지금 작성된 [chromium Audio / Video 문서](https://www.chromium.org/developers/design-documents/video) 같은 경우 다소 오래 되었다. 따라서 좀 더 최신의 글을 읽고 싶은 사람은 [Readme]() 를 클릭해 보도록 하자.

현재 작성되는 문서는 내가 이해한 기준으로 작성되며, 흐름이 명확하지 않을 수
있다. 혹, 원문으로 보고 싶은 분들은 [chromium Audio / Video
문서](https://www.chromium.org/developers/design-documents/video) 링크를 클릭해
원문을 참고하도록 하자.

### Overview
Chromium media를 구성하는데 몇 가지 중요한 componenet들이 존재한다. Component의
역할을 간략히 알아보자.

- pipeline
	- chromium 의 media 재생 엔진의 구현
	- Audio / video 동기화와 resource fetching 처리
- FFmpeg (Demuxer, Audio decoder, Video decoder)
	- Audio / video의 sw 디코딩 및 파싱을 담당
	- open source로 제공되어짐
- Blink's HTMLMediaElement
	- WHATWG (단체)에 의해 지정된 HTML 과 Javascript를 바인딩 하는 역할
	- user agent의 렌더링 동작 제어

위의 내용들을 좀 더 자세히 알아보자.

### Pipeline
Pipeline은 pull based system (사용자가 요청할 때 제공하는 시스템, 자세한 것은
		Memorization 부분 참고)이다. 앞서 언급한 것과 같이 pipe line은 재생처리 하는
엔진이다. 내부적으로는 총 6개의 다른 filter로 나눠져있다.
- 6개의 filter
	- data source
	- demuxer
	- video decoder
	- video renderer
	- audio decoder
	- audio renderer

pipeline은 renderer의 수명을 관리하고 thread-safe한 interface를 외부에 노출 시켜
접근하도록 만드는 역할을 한다. Filter는 연결되어 서로 Filter graph를 형성한다.

![크로미움 필터 그래프](/img/chromium_filter_graph.png)

#### Pipeline의 design
Pipeline을 design 관점에서 보자. 어떻게 구성되어졌을까?
- pipeline의 디자인
	- chromium 의 thread를 활용한다 (task_runner 문서를 보자)
	- 각 filter들은 thread 모델을 결정하지 않는다. (thread 모델은 다양하다. 구글에 검색해보자.)
	- 모든 filter는 비동기적으로 동작하며 signal 완성을 callback으로 한다.
	- 상위 filter는 하위의 filter에 개입하지 않는다. (독립적)
	- 명시적인 타입과 함수를 선호한다. (사람들이 명확하게 알 수 있게 해야함)
	- sandbox security를 채택한다
	- window, mac, linux에서 동작하며, arm 프로세스나 x86 관계없이 동작한다
	- audio / video 코덱의 추상화를 지원한다.

pipeline에서는 위의 디자인 관점을 지향하고 구성됐다. 또한, 디자인이 고려되지
않는 부분들도 있다.

- pipeline 디자인 미고려
	- 공유라이브러를 이용한 필터의 동적 로딩을 고려하지 않는다.
	- Buffer 관리를 하지 않는다.
	- filter graph의 순서를 보장하지 않고 만든다
	- media 재생동작을 넘어서는 filter기능에 대해 지원하는 것을 고려하지 않는다.

위의 관점은 지양하는 것인지 고려되지 않는 것인지는 확실하지 않다. 이 부분은
소스코드를 직접 보면서 확인해보자. (추후 소스코드를 다루는 부분에서 확실시 할 수
		있을 것이라 생각한다)

pipeline을 구축하기 전에 다양한 media pipeline들이 존재했다. 2008년 기준 6개의
pipeline들이 존재했는데, chromium에 적합하지 않아서 채택하지 않고 새로
구현했다고 한다. (2008년 기준이라 너무 오래되서 이 부분은 다루지 않도록 한다)

### Filter graph
Chromium은 자체적으로 만든 media를 통해 audio / video 코덱에 관계없이 미디어를
재생하는 것을 목표로 했다. Open source로 제공되는 FFmpeg를 통해 사요화 되었거나
상품화된 미디어 코덱의 사용을 최소화했다. FFmpeg 사용을 통해 chromium 미디어
엔진 즉, pipeline에게 build시 option을 이용해 다양한 포멧을 지원하도록 했다.

![filter grpah](/img/chromium_filter_graph_1.png)

앞서 언급한 것과 같이, chromium 미디어 재생동작은 pull-base 방식 (요청시
		처리)이고 사운드 같은 경우 사운드 카드를 이용해 동작하도록 한다. 사운드
카드를 이용해 요청하는 부분을 확인해보자. 위의 그림과 함께보자

사운드 카드는 추가적인 데이터를 Audio renderer를 통해 요청한다. 또한, 연쇄적으로
Audio renderer는 요청받은 데이터를 Decoder에게 요청하게 되고 demuxer,
			datasource, internet등등으로 요청된다. 즉, 상위 레이어에 요청을 연쇄적으로
			한다. 디코딩 된 데이터는 결국 soundcard로 돌아오게 되고 처리가 완료됐다는
			의미로 ***pipeline's global clock*** 를 갱신한다.

Video renderer 같은 경우 약간 다르게 동작한다. 

비디오 렌더러는 각각의 vsync에 대해 글로벌 클록을 폴링하여 비디오 디코더로부터 디코딩 된 프레임을 요청하는시기 및 비디오 디스플레이에 새로운 프레임을 렌더링 할시기를 결정한다. (이 부분은 소스코드를 통해 이해하도록 하자.) Audio card 또는 audio track이 없을 경우 글로벌 클록에 대해 사용할 수 없다. 따라서, system clock을 이용해 video renderer가 동작하도록 한다. 연관된 소스코드는 media 디렉토리에 존재한다. (소스코드를 보면서 video renderer는 이해할 필요가 있다.)

Pipeline은 재생 또는 각 종 이벤트 처리를 위해 상태머신을 사용한다. 상태머신이 사용하는 상태 전이는 일반적으로 이벤트의 모든 필터에 알리고 전이를 완료하기 전에 완료 콜백을 기다리는 것으로 구성됩니다 (pipeline_impl.h의 다이어그램을 보자)

Pull-based 디자인 같은 경우 재생을 즉시 멈추는 동작을 rate = 0으로 함으로 가능하다. 이후 audio / video renderer들은 상위 필터에게 중지를 요청함으로 가능하다.

아래의 그림은 통합적으로 media의 구성요소를 나타낸 것이다. 이 부분의 흐름의
골자는 비슷하다. 비교적 최근 소스코드로 통합적인 그림을 수정해 추가하도록
하겠다. 우선 그림을 통해 아 이런식으로 흘러가는구나 정도만 파악하자

![크로미움 media 통합](/img/chromium_filter_intergration.png)

---

#### Memorization
- oblivious - 의식하지 않는
- be unaware of  - ~대해 알지 못하다
- agnostic - 애그노스틱 기술((작동 시스템에 대한 지식 없이도 기능을 수행할 수 있게끔 하는 기술))
- proprietary -  [등록 전매] 상표가 붙은
- feed into something - to have an effect on something or help to make it happen
- gist - 골자

pull based system
- 실제 소비자의 주문이 발생할 경우 그에 맞춰 제품을 생성하거나 재고를 보충하는 방식을 말한다. 실제 고객 수요에 반응해야 하기 때문에 반응적 프로세스라고도 불린다. Pull process는 장기적인 수요를 예측할 필요가 없어 상대적으로 리드 타임이 짧아져 수요 변동에 대체가 빠르고 대량재고나 채찍효과가 발생할 가능성이 거의 없다.

리드 타임
- 상품의 주문일시와 인도일시 사이에 경과되는 시간

### Reference
- [chromium 문서](https://www.chromium.org/developers/design-documents/video)
