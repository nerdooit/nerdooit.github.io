---
layout: post
title: '[Chromium] Linux 에서 Chromium 빌드하기'
subtitle: 'Ubuntu 환경에서 Chromium을 빌드하는 방법을 알아보자'
date: 2020-07-19
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium chromium_document
lastmod : '2020-07-19 08:05:00'
sitemap :
  changefreq : daily
  priority : 1.0
---

### Chromium Build on linux
Linux 환경에서 Chromium을 빌드하는 방법을 알아보자. Chromium은 다양한
platform에서 동작하며, 빌드 방법은 조금씩 차이가 있다. 자신이 선호하는 환경과
Chromium 빌드 방법을 구글한다면 쉽게 찾을 수 있을 것이다.

본인의 환경은 Linux이며, 다양한 Linux OS 중에서도 "Ubuntu" 를 이용해 빌드하고자
한다. Chromium 문서에서도 Ubuntu 기반으로 설명하고 있으며, 약간의 명령어 차이
정도는 존재할 수 있지만 기본적인 Linux OS에서는 동일한 원리로 빌드 할 수 있을
것이라 생각한다.

### 시스템 환경
#### 문서에서 제공하는 Chromium을 빌드하기 위한 필수 환경 조건

- 64 bit machine 과 8GB의 RAM 사용 (개인적으로 16 GB를 추천함)
- 최소 100GB 디스크 공간 (개인적으로 SSD 추천함)
- Git 과 python v2 설치

위의 시스템 조건 같은 경우 필수적으로 가능해야하는 조건이다. 다들 알겠지만,
***H/W 는 풍부할 수록 좋다*** 본인이 해본 결과 8GB 램으로 할 경우 메모리
부족으로 OS 자체에서 빌드를 kill 하는 경우가 많이 발생했다. 따라서 메모리는 정말
16GB를 추천한다.

Chromium 문서에서는 Ubuntu 16.04 를 기반으로 빌드했으며, 다른 배포 버전에
대해서는 명령어가 약간의 차이가 있을 수 있다고 언급한다.

#### 본인 Chromium 빌드 환경
아래는 본인이 Chromium을 빌드를 성공했을 때 환경이다.

Tip) Linux에서 시스템 환경을 검색하는 방법

```sh
보통 H/W 정보는 /proc 정보에 다 있다.

// CPU 정보
cat /proc/cpuinfo

// memory 정보
cat /proc/meminfo // 보기 어려움, 아래의 명령어를 통해 보자
free -m (or -g) // free는 memory 용량을 간단히 보여주는데, mega byte표현은 m
								// giga byte 표현은 g이다.
// disk 정보
cat /proc/diskstats // 보기 어려움, 아래의 명령어로 보자
df -h
```

- Intel(R) Core(TM) i5-8250U CPU @ 1.60GHz & 8GB
- 256GB disk space
- Ubuntu 16.04

빌드를 하면서 필요한 package가 없을 경우 fail이 뜨는데 ***당황하지말고 구글 검색
을 통해 package 설치해주자!***


### depot_tools 설치
depot_tools 란 Chromium을 설치하는데 필요한 package 들과 script들의 모음이다.
Chromium의 source code repo 관리와 개발 프로세스의 동작을 함에서 필요한
package들을 담고 있다.

가장 핵심적인 것은 ***gn빌드 시스템, gclient*** 두 가지 정도가 있다.

- gn 같은 경우Chromium에서 사용하는 빌드 시스템이다. Chromium은 닌자 기반으로 구성되어져
있으며 각종 recipe가 .gni or gn으로 작성되어있는 것을 볼 수 있을 것이다.
Recipe들을 모아 Chromium을 빌드할 수 있도록 하는 시스템이 depot_tools에
들어있다.

- gclient 같은 경우 chromium source code repo를 관리한다. 우리가 이후 볼 명령어
중 아무것도 하지 않았는데 소스코드가 fetch가 되네? 하는 경우 이 gclient가
동작했다고 보면된다.

개인적으로, depot_tools에 대해 깊게 알아보기 보다는 build 하는데 초점을 맞추는게
좋다고 생각한다.

#### 설치 가이드

- depot_tools를 본인의 home 디렉토리에 clone하자.

```sh
$ git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
```

- 환경 변수 설정 (shell 입장에서 어느 위치에서나 depot_tools에 접근하기 위한
		과정)

```sh
$ export PATH="$PATH:${HOME}/depot_tools"
```

- code를 fetch하자. (이 때 gclient가 사용된다.)

```sh
# chromium을 빌드하기 위한 디렉토리 생성
$ mkdir ~/chromium && cd ~/chromium

# fetch
$ fetch --nohooks chromium
```

