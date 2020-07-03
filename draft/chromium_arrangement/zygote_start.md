### Zygote란
프로세스 시작을 fork()로 처리해 시작시간과 메모리 용량을 최적화 하기 위해 사용하는 Library이다. Chromium, Android에서 사용되고 있는 것으로 확인된다. Chromium 같은 경우 browser process 생성 이후 나머지 process (e.g. render, gpu process etc.) 등을 생성할 때 최적화를 위해 사용한다. Android 같은 경우 가상머신 생성과 메모리 최적화를 위해 사용한다.

안드로이드 관련한 Zygote 같은 경우 [dev-ahn blog](https://dev-ahn.tistory.com/category/Programing/Android?page=2) 를 통해 확인해보자. 아주 상세히 설명이 잘되어있다.

![zygote_start](/img/zygote_start.png)

위의 그림은 zygote가 어플리케이션을 어떻게 실행하는지 확인할 수 있는 그림이다. zygote는 시스템 리소스 혹은 preload 되어야 하는 정보 및 메모리
 참조 주소 등을 다 갖고 있는 일종의 패키지를  그대로 cop 한다. 이후 어플리케이션에 필요한 정보를 담아 수행하도록 한다.

그럼 Chromium 에서는 zygote가 어떻게 동작하는가?

