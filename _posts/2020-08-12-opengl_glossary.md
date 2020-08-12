---
layout: post
title: '[OpenGL ES] Graphic 관련 용어정리'
subtitle: 'OpenGL ES 학습 전 필요한 용어 정리'
date: 2020-08-12
author: nerdooit
cover: '/img/openGLES_cover.png'
tags: openGL openGLES chromium_media
lastmod : '2020-08-12 12:15:00'
sitemap :
  changefreq : daily
  priority : 1.0
---

### OpenGL ES 란
OpenGL ES (OpenGL for Embedded Systmes)는 휴대 단말기기와 Embedded Systems (이하
		ES 장치)에 초점을 둔 향상된 3D 그래픽을 위한 API (Application Promgramming
			Interface) 이다. OpenGL ES 같은 경우 대부분의 스마트폰에서 Graphic API로
		사용되고 있으며 Desktop 까지 확장되어 사용되고 있다. Open GL ES를 지원하는
		플랫폼 목록은 iOS, Android, blackberry, linux, windows 등을 포함한다. 또한,
		OpenGL ES는 Web Browser 기반 3D 그래픽스를 위한 Web 표준인 WebGL 기능을
		포함하고 있다.

OpenGL ES 3.0 이후 부터는 큰 변화보다는 추가적인 API 추가하는 정도의 변화이기
때문에 3.0 기반으로 학습해보고자 한다.

### OpenGL ES Overview
OpenGL ES를 처음 접하는 사람으로 정보가 많이 부족해 다소 어려움이 있다. 따라서,
우선 Graphic에서 사용하는 용어와 Graphic pipline에 대해 학습하고 책을
따라 가고자한다.

### Graphic Glossary
#### Shader
Graphic에서 사용하는 명령어의 집합이다. 스크린에서 하나의 Grpahic 단위를
표현하기 위해서는 다수의 pixel을 동시에 표현해야한다. 이 때, 표현하기 위한
명령어의 집합을 "shader" 라고 말한다. 구체적인 예시를 생각해보자. 우리의
스크린은 다수의 픽셀로 이루어져 있다는 것을 알고 있다 (e.g. 1920 x 1080). 만약
우리가 삼각형을 표현하기를 원한다면 삼각형 크기의 다수의 pixel이 동시다발적으로
표현되어져야 한다. 즉, 낱개의 pixel이 위치, 색상 등이 다 다르며, 이를 한번의
명령어로 처리해야 삼각형이 표현될 수 있다. 이를 처리하기 위한 집합을 우리는
"shader"라고 칭한다.

좀 더 자세한 설명은 [여기](https://thebookofshaders.com/01/?lan=kr) 를 클릭해서 읽어보자. 아주 쉬운 예시와 함께
설명하고 있다.

#### Vertex
우리가 자료구조를 공부하다보면 많이 마주 쳤을 것이다. Vertex는 Graph
자료구조에서 많이 나오는데 "점" 이라는 뜻을 가지고 있다. Graphic에서도 통요되게
사용되는데 하나의 pixel을 나타내기 위한 것 (그렇다고 Vertex == pixel 생각하면 안된다!) 이라고 생각하면 편한다. Vertex는 2D,
	3D를 기반으로 가지고 있는 데이터가 다른데, 2D 일 경우 x, y 를 3D 일 경우 x, y, z 를 가지고 있다. 또한 위치정보를 비롯해 하나의 정점이 나타낼 수 있는 color 값을 가진 RGBA 데이터를 가지고 있다. 이외 다양한 데이터를 갖고 있지만, 핵심적으로 ***위치 정보와 색상 정보*** 가 있다는 것을 기억하자.

#### Polygon
한국어로 표현하자면 다각형이라는 뜻으로, 우리가 Vertex를 연결해 만들 수 있는
면을 의미한다. 예를들어, 우리는 Vertex 3개를 이용해 삼각형이라는 면을 만들 수
있다. OpenGL ES에서는 이런 면을 primitive 라고 칭하고 있다 (추후 등장할 것).

#### Shader program
우리가 말한 Vertex를 가지고 우리가 원하는 어떤 것을 Screen상에 표현할 수 없다.
Screen 상에서 표현할 수 있는 명령어로 변경해줘야 하는데, 이를 위해 사용하는
도구를 Shader Program이라 한다. Shader는 위에서 언급한 것과 같이 다수의 명령어의
집합이고, 다수의 명령어를 처리하는 프로그램을 "Shader Program"이라 한다.

Shader program에는 핵심적인 두 가지 program이 존재한다.
- Vertex Shader Program
- Fragmental (Pixel) Shader Program

#### GLSL
위에서 언급한 Shader Program을 작성할 때 사용되는 Programming language 이다.
GLSL은 OpenGL Shading Language의 줄임말이다. C 언어를 기반으로 작성된 언어이며,
	Shading programming할 때 사용한다 정도만 알아두자.

#### Vertex Shader
GLSL로 작성된 Vertex 처리를 위한 Shader program이다. Vertex 정보를 2D 혹은 3D로
공간배치 할 때 사용된다. 모든 Vertex를 처리해야하기 때문에 다수의 명령어의
집합(Shader)를 호출해 내부적으로 처리할 것이다.

#### Rasterization
Vertex Shader를 통해 나온 작업물을 Fragment Shader program에 전달하기 이전에
수행하는 단계로 ***보간법*** 을 적용하기 위해 사용한다 (뒷 부분에서 자세히
		다루겠다). 이 단계를 거치게 되면 Fragment shader의 input이 output로 나오게
되며 Shader 작업을 처리하게 된다.

#### Fragment Shader
Vertex 데이터들을 Shader를 통해 공간 배치를 완료하고 Rasterization 단계를 거쳐
실제 pixel 값을 결정하는 단계에 도달한다. 이 단계를 Fragment Shader 단계라고
부르며 마찬가지로 GLSL 언어로 작성되어져있다. 실제 표현되어야하는 pixel 값이
결정되는 단계라고 보면된다.

#### Graphic pipeline
뒷 부분에서 자세하게 다루겠지만, 현재까지 다룬 것을 통해 정리해보자면, Vertex >
Vertex Shader > Rasterization > Fragment Shader > pixel 로 표현되는 단게를
***Graphic pipeline*** 이라 부른다. 뒷 부분에서 좀 더 자세하게 알아보고자한다.

---

#### Reference
[OpenGL 용어 정리 참조 사이트](https://medium.com/@NovaWoo/opengl%EC%9D%84-%EC%9C%84%ED%95%9C-3d-%EA%B8%B0%EB%B3%B8-%EA%B0%9C%EB%85%90-1-1f305105b478)

#### Memorial
- supply 제공하다
- perform on something : something을 가지고 수행하다.
- varying : 바뀌는, 변화하는 가지각색의
- interpolation : 보관법
- lighting equation : 밝기 차이?
- Alternatively : 그렇지 않으면, 그 대신에
- projection : 예상
- dimensional : 차원 (e.g. two-dimensional 2차원)


#### Memorial sentence
- The mechanism used to generate a value for each fragment from the vertex shader outputs that is assigned to each vertex of the primitive is called interpolation.

