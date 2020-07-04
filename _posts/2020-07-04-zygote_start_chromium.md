---
layout: post
title: '[Chromium] Zygote를 활용한 Chromium의 시작'
subtitle: 'Web page (chromium engine) 는 어떻게 zygote를 활용해 시작되는지 알아보자.'
date: 2020-07-04
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium chromium_document
lastmod : '2020-07-04 21:45:00'
sitemap :
  changefreq : daily
  priority : 1.0
---

### WebPage의 시작
Webpage가 처음 구동될 때 어떻게 동작할까? 가장 많이 사용되고 있는 web engine, open source인 chromium을 기준으로
알아보자.

Chromium은 WebPage가 처음 켜질 경우 크게 3가지 동작을 한다

1. Browser process 생성
2. Zygote process초기화 및 동작
3. Child process 생성 (e.g. render process etc.)

![chromium_start](/img/chromium_start.png)

위의 그림은 chromium의 처음 시작 됐을 경우를 나타낸 것이다. 대략적으로 표현한
것이기 때문에 내부적으로는 훨씬더 많은 일을 한다는 것을 감안하자. 예를들면
content thread생성 sandbox구성 gru process cc 등 다양한 일들을 내부적으로
처리하나 기본 패턴은 위와 같다. Browser process를 생성하고 zygote 생성 후 child
process를 생성한다. Browser process와 Child process인 render process는 잘
알겠는데, zygote에 대해선 생소하다. 아래에서 zygote에 대해 알아보도록 하자.

### Zygote란
프로세스 시작을 fork()로 처리해 시작시간과 메모리 용량을 최적화 하기 위해 사용하는 Library이다. Chromium, Android에서 사용되고 있는 것으로 확인된다. Chromium 같은 경우 browser process 생성 이후 나머지 process (e.g. render, gpu process etc.) 등을 생성할 때 최적화를 위해 사용한다. Android 같은 경우 가상머신 생성과 메모리 최적화를 위해 사용한다.

#### Android zygote 사용
안드로이드 관련한 Zygote 같은 경우 [dev-ahn blog](https://dev-ahn.tistory.com/category/Programing/Android?page=2) 를 통해 확인해보자. 아주 상세히 설명이 잘되어있다.

![zygote_start](/img/zygote_start.png)

위의 그림은 zygote가 어플리케이션을 어떻게 실행하는지 확인할 수 있는 그림이다. zygote는 시스템 리소스 혹은 preload 되어야 하는 정보 및 메모리
 참조 주소 등을 다 갖고 있는 일종의 패키지를  그대로 복사한다. 이후 어플리케이션에 필요한 정보를 담아 수행하도록 한다.

#### Chromium zygote 사용
안드로이드는 위와 같은 이유로 사용하지만, Chromium에서는 왜 Zygote를 사용하는가?

안드로이드에서 사용하는 이유와 비슷하지만, 크로미움은 달빅을 활용한 jni 해석이
필요 없기 때문에 가상머신을 로딩할 필요가 없다. chromium zygote를 사용하는 이유는
***멀티프로세스 환경에서 다양한 프로세스***를 생성할 때 ***시간 절약과 공유 메모리***를
활용해 메모리 용량을 최소화 하기위해 사용한다. 구체적으로, zygote를 사용할 경우 공유 메모리를 사용함으로 6MB ~ 60 ms / GHz 를 절약한다. 또한, 각종 라이브러리를 (예를들면, v8 javascript lib, icu localize lib, nss network service lib )먼저 초기화해 snapshot으로 만들어 프로세스를 fork함으로 메모리와 시간을 절약할 수 있다.

Chromium에서 zygote를 어떻게 활용하는지 구체적으로 확인해보자.

![zygote_launch](/img/zygote_launch.png)

위의 그림과 같이, Chromium에서는 browser process가 생성된 이후 Zygote process를
fork와 exec함수를 활용해 load 시킨다. 이 동작 같은 경우 <span class="evidence">pid_t
ZygoteHostImpl::LaunchZygote </span> 를 통해 확인할 수 있다. 이후 각종 프로세스
같은 경우 zygote를 fork해 생성되도록 한다. zygote에서 초기화 된 snapshot을
가지고 있으며 그 부분을 fork한 이후 다른 프로세스가 수행된다는 점을 기억하자.

소스코드를 분석하면서, 신기했던 점은 Render, GPU 프로세스 같은경우 child process
helper를 통해 생성되는 것 같았다. 나머지 process들은 content thread를 통해 생성
되는 것으로 보이는데, 이 부분은 부족한 것 같다. (아시는 분은 댓글 남겨주세요.)

> 소스코드 상에는 Render I/O thread에서 U/I thread를 blocking 하는 동작을 막고자
> child process helper를 통해 생성한다고 한다.

- 참고용 (Render process host 에서 Init 동작 수행 중 발생함)
	```java
	1793     // Spawn the child process asynchronously to avoid blocking the UI thread.
	1794     // As long as there's no renderer prefix, we can use the zygote process
	1795     // at this stage.
	1796     child_process_launcher_ = std::make_unique<ChildProcessLauncher>(
	1797         std::make_unique<RendererSandboxedProcessLauncherDelegate>(),
	1798         std::move(cmd_line), GetID(), this, std::move(mojo_invitation_),
	1799         base::BindRepeating(&RenderProcessHostImpl::OnMojoError, id_),
	1800         GetV8SnapshotFilesToPreload());
	1801     channel_->Pause();
	1802
	```

위의 내용들은 소스코드와 각종 자료를 통해 알아본 내용이다. Chromium이 어떻게
동작하는지 소스코드 단위로 알아보고 싶다면 [여기]()를 클릭해 확인해보기 바란다.

### Zygote 수행 방법
Zygote를 수행하기 위해서는 아래의 명령어를 통해 수행한다.

```java
--type=zygote // zygote 사용
--zygote-cmd-prefix // 디버깅 용
```

실제 코드에서 보면 zygote build flag가 존재한다

```java
 818 #if BUILDFLAG(USE_ZYGOTE_HANDLE)
 819     if (process_type.empty()) {
 820       // The sandbox host needs to be initialized before forking a thread to
 821       // start the ServiceManager, and after setting up the sandbox and invoking
 822       // SandboxInitialized().
 823       InitializeZygoteSandboxForBrowserProcess(
 824           *base::CommandLine::ForCurrentProcess());
 825     }
 826 #endif  // BUILDFLAG(USE_ZYGOTE_HANDLE)
```

간단하게 언급하자면, USE_ZYGOTE_HANDLE 이라는 flag 설정 시, zygote가 수행된다.
Browser process 인 경우만 Zygote를 생성할 수 있도록 하는 부분의 소스코드
발췌이다.

---

#### Reference
[In Daddy's space](http://swamful.blogspot.com/2014/11/zygote-in-chromium.html)
[dev-ahn](https://dev-ahn.tistory.com/category/Programing/Android?page=2)
[zygote readme](https://chromium.googlesource.com/chromium/src.git/+/master/docs/linux/zygote.md)
[chromium blog 정리](http://chromium-kr.blogspot.com/2012/03/content-shell-shellmaindelegate-1.html)


#### Copyright
본 게시물 관련해 공유하실 경우 댓글 하나만 남겨주시면 감사하겠습니다 (__)

> 부족한점이 많으니, 다양한 의견과 잘못된 점 겸허히 받아드리겠습니다.


