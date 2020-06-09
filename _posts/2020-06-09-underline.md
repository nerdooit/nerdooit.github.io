---
layout: post
title: '[Chromium] Text decoration skip ink 옵션'
subtitle: 'CSS text-decoration-skip-ink property에 대해 알아보자'
date: 2020-06-09
author: nerdooit
cover: '/img/chromium_nerdooit.png'
tags: chromium css
lastmod : '2020-06-09 22:47:00'
sitemap :
  changefreq : daily
  priority : 1.0
---
### text-decoration-skip-ink
CSS 속성으로 outline과 inline을 어떻게 설정할 것인가를 결정하는 속성이다. 구체적으로, text에 underline을 긋게 되는데, 밑줄 기>준으로 언어가 나올 경우 (e.g. y,g,j 등) 생략할 것인가를 결정할 때 사용하는 옵션이다. 그림으로 보면 이해가 더 쉬울 것이다.

[text-decoration-skip-ink 적용]()

### Chrome과 Chromium 적용 상태
Chrome에서는 64버전 부터 default 값이 auto로 세팅되어졌다. (chromium은 57 베타버전부터 사용된 것으로 보인다.) Chrome에서 UA 단
어 기준으로 고려했을 때, 위의 예시와 같이 소문자에서 글자가 밑줄로 내려가는 경우 생략될 수도 있기 때문에 auto로 세팅한 것 같다. 만약 밑줄로 인해 "y" 의 하단부가 가려자 "v"로 보일 수도 있기 때문이 아닌가 조심스레 생각해본다.

혹시, text-decoration-skip-ink를 적용하길 원한다면 아래와 같이 설정하자.

```java
/* CSS 기준 */
/* Single keyword */
text-decoration-skip-ink: none;
text-decoration-skip-ink: auto;
text-decoration-skip-ink: all;

/* Javascript 기준 */
function settingSkipInk() {
  var id = document.getElementById("id");
  id.textDecorationSkipInk = "none";
  id.textDecorationSkipInk = "auto";
  id.textDecorationSkipInk = "all";

/* Javascript 기준 */
function settingSkipInk() {
  var id = document.getElementById("id");
  id.textDecorationSkipInk = "none";
  id.textDecorationSkipInk = "auto";
  id.textDecorationSkipInk = "all";
}
```

#### Reference
[크롬적용 history](https://www.chromestatus.com/feature/5631679087509504)
[Web document](https://developer.mozilla.org/en-US/docs/Web/CSS/text-decoration-skip-ink)
[necols issue tracking](https://github.com/necolas/normalize.css/issues/722)

