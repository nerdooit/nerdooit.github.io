### Cloud server에서 Chromium 빌드
Chromium을 Cloud server에서 빌드한 후 산출된 결과물을 어떻게 볼 것인가?

결과를 확인하는 방법에는 두 가지가 존재한다. (이외 방법이 더 있다면, 댓글로
		공유부탁드린다.)

1. ssh -X 를 활용한 GUI 화면을 요청하기 (xtrem 필요)
	- 가장 쉽게 활용하는 방법이다. Ssh 에 -X 옵션을 추가해 cloud에 접속을 요청한
	후 chrome 산출물을 실행하면된다. (이때, 빌드 산출물은 chromium이라고 전제한다.)

2. Cloud server에서 빌드 산출물을 local directory로 옮긴 후 확인한다.

### Build 산출물 옮기기
Build 산출물을 옮기는 가장 간단한 방법은 out/Default 라는 산출물 directory를
전체 local로 옮기는 것이다. 하지만, local로 모든 library를 지속적으로 옮기기에는
시간이 오래 걸린다는 것을 알 수 있다.

본인 같은 경우 chromium 코드를 분석하고 동작성을 알아보기 위해 빌드함으로 chromium 실행파일을 수행하기 위한 library 들만 옮기면 된다. libcontent.so 와 같은 chromium 실행을 위한 library만 옮기면 되는데 어떤 library가 필요한지 솔직히 잘 알지 못한다. 따라서, 필요한 library를 정적으로 빌드한 후 chromium 실행파일을 local로 가져오는 방법을 채택하고자 한다.

Chromium은 기본적으로 ***dynamic linking***을 이용한다.

### Dynamic Linking
Chromium 은 기본적으로 Dynamic Linking을 채택하고 있다. 확인해보고자 한다면
아래의 명령어를 통해 확인해 볼 수 있다.

```bash
$ gn args out/Default --list=is_component_build

# 위의 명령어를 이용한다면 각종 build 설정을 검색(자세한 건 help를 통해보자.) 할 수 있다.
```

위의 명령어를 수행한다면, chromium에서 왜 dynamic linking을 채택했는지 나온다.

![dynamic linking](/img/dynamic_linking.png)

설명과 같이, chromium에서는 빌드 속도를 빠르게 하기 위해 dynamic linking을
사용하고 있고 필요시 변경도 가능하다. Cloud server에서 편하게 가져올 수 있는
방법으로 ***static library*** 설정하는 방법과 dynamic linking과의 차이를
알아보자.

### Static Linking
Chromium 빌드를 static으로 바꾸는 방법은 build 설정을 바꿔주면 된다.

기본적으로 dynamic 같은 경우 ***is_component_build*** flag가 ***true***로
설정되어있다. 이를 ***false*** 로 변경해주면 쉽게 static 빌드가 가능하다.

```bash
$ gn gen out/Default "--args=is_component_build=false"
```

Static linking 빌드를 한 후 결과를 본다면 dynamic linking 빌드와 차이가
존재한다.

1. chrome을 구성하기 위한 각 종 library들을 찾을 수 없다. (e.g. libcontent.so)
	- 아래의 사진을 본다면 ***out/Default*** 같은 경우 dynamic liking 빌드 산출물이고, ***out/Realese***
	같은 경우 static linking 산출물이다. 각 산출물에서 libcontent.so library를
	찾아보았다. 찾아본 결과 static linking에서는 찾을 수 없었다. (tab을 해도
			안나옴)

![dynamic vs static](/img/dynamicVSstatic.png)

2. 산출물의 크기가 다르다.
	- 당연 각 종 library를 포함한 static linking 빌드 산출물의 실행파일의 크기가
	더 컸다. 약 300mb 정도 더 많은 용량을 차지 했다. (빌드 속도차이는 비교못했지만
			좀 더 오래걸린다고 한다.)

![capacity](/img/dynamicVSstatic_capacity.png)

### Tip (faster 빌드)
Static build를 하고자 한다면 속도가 빌드 속도가 좀 더 오래걸릴수도 있다. 이
문제를 약간이나마 개선할 수 있는 방법을 공유하고자 한다. 만약 디버깅이 아니라
동작성 정돤 하고자 한다면, debug mode와 symbol을 최소화하자. Backtrace를 이용해
확인하고자 한다면 symbol은 남겨둬야할 것이다.

```bash
$ gn gen out/Default "--args=is_component_build=false is_debug = false symbol_level = 0"
```

---
#### Reference
[chromium document](https://www.chromium.org/developers/gn-build-configuration)
