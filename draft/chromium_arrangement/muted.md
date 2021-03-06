### Video / Audio muted
Muted property 같은 경우 이름 그대로 음소거 설정이다. 음소거를 하기 위해서는 control button의 음소거 버튼을 클릭>하거나 javascript를 이용해 설정이 변경가능하다. 변경을 하기 위해서는 muted 속성을 true로 변경하면 된다.

보통 속성을 변경하기 위해서 사용하는 javascript 옵션 같은 경우 ***setAttribute(), (.) operation*** 두 가지가 존재
한다. Javascript를 사용하는 사람이라면 충분히 많이 사용했을 것이라 생각한다. 다만, 무슨 이유인지는 모르겠지만, Muted option을 사용할 경우 Chrome / FireFox 에서는 setAttribute가 적용되지 않는다.

### setAttribute option
아래의 소스코드는 [w3c school](https://www.w3schools.com/tags/tryit.asp?filename=tryhtml5_av_prop_muted)의 muted option test code를 발췌한 것이다.

```java
<!DOCTYPE html>
<html>
<body>

<button onclick="enableMute()" type="button">Mute sound</button>
<button onclick="disableMute()" type="button">Enable sound</button>
<button onclick="checkMute()" type="button">Check muted status</button><br>

<video id="myVideo" width="320" height="176" controls>
  <source src="mov_bbb.mp4" type="video/mp4">
  <source src="mov_bbb.ogg" type="video/ogg">
  Your browser does not support HTML5 video.
</video>

<script>
var vid = document.getElementById("myVideo");

function enableMute() {
  vid.setAttribute(muted,true);
  //vid.muted = true;
}

function disableMute() {
  vid.setAttribute(muted,false);
  //vid.muted = false;
}

function checkMute() {
  alert(vid.muted);
}
</script>

<p>Video courtesy of <a href="https://www.bigbuckbunny.org/" target="_blank">Big Buck Bunny</a>.</p>

</body>
```
위의 코드를 직접 컴파일 해보거나 귀찮으신 분들은 w3c school link를 타고 들어가 enableMute() / disableMute() 함수를 변경한 뒤 Run 동작을 눌러컴파일 해보길 바란다. 이후 실행을 해보면, ***Muted 동작***이 수행되지 않는 것을 확인할 수 있다.

왜 그런지를 찾으려 노력했지만, 정확한 이유를 찾지는 못했다. 다만 그럴사한 흔적들을 발견해 공유하고자 한다.

### 몇 가지 흔적들..
- HTML5 video muted attribute not applied using property but applied using setAttribute [스택오버플로우 링크](https://stackoverflow.com/questions/41656297/html5-video-muted-attribute-not-applied-using-property-but-applied-using-setattr)
  - video tag에서 src를 제외한 나머지 property들은 current 상태를 유지하려고한다. setAttribute로는 현재 상태를 변경할 수 없으>며, 반영되지 않을 것이라는 정보가 담겨있다. Video tag와 마찬가지로 HTMLMediaElement를 상속 받는 Audio tag도 동일하지 않을까 하
는 생각을 한다.

- cly7796 blog 내용 발췌 [블로그 주소](http://cly7796.net/wp/javascript/muted-added-with-setattribute-to-the-video-element-does-not-work-with-firefox-and-chrome/)
  - setAttribute가 동작하지 않는 것을 예시로 보여주는 블로그

- MDN setAttribute 문서 [MDN document](https://developer.mozilla.org/en-US/docs/Web/API/Element/setAttribute)
  - 마지막 Gecko 노트를 참조해보자. setAttribute()는 불완전함으로 (.) 연산을 사용하는 것을 권장한다.

- HTML5 Canvas Dummy book 일부분 발췌 [Dummy 책](https://books.google.co.kr/books?id=1fg0uRR-SjIC&pg=PT380&lpg=PT380&dq=dummy+html5+canvas+setAttribute+src+muted&source=bl&ots=tX9o-_kjsi&sig=ACfU3U2Xtmvv30eRV65l6cqO--0q2bm0tQ&hl=ko&sa=X&ved=2ahUKEwit5fzL4_HpAhUbM94KHZHnDygQ6AEwAHoECAoQAQ#v=onepage&q=dummy%20html5%20canvas%20setAttribute%20src%20muted&f=false)
  - 책에 video tag 관련해 자세하게 나와있다. setAttribute같은 경우 src만 변경가능하고 나머지 property 속성은 변경이 되지 않는>다. 4번 내용을 참조하자.

- Chromium bug 발췌 [chromium bug](https://bugs.chromium.org/p/chromium/issues/detail?id=1033554)
  - HTML5 문서에 muted는 create 이후 속성 변경이 불가능하다. 하기 위해서는 (.)연산자를 사용해야한다고 나와있다. 다만, 의문이 >드는 것은 spec문서에서는 찾아볼 수 없다.. (만약 찾은사람은 링크를 주기 바란다.)

### 해결 방법
해결 방법은 단순하다. setAttribute 말고 (.)을 사용하자!

w3c에 적혀있는대로 (.)연산자를 이용해 muted속성을 변경하자.

```java
<!DOCTYPE html>
<html>
<body>

<button onclick="enableMute()" type="button">Mute sound</button>
<button onclick="disableMute()" type="button">Enable sound</button>
<button onclick="checkMute()" type="button">Check muted status</button><br>

<video id="myVideo" width="320" height="176" controls>
  <source src="mov_bbb.mp4" type="video/mp4">
  <source src="mov_bbb.ogg" type="video/ogg">
  Your browser does not support HTML5 video.
</video>

<script>
var vid = document.getElementById("myVideo");


function enableMute() {
  //vid.setAttribute(muted,true);
  vid.muted = true;
}

function disableMute() {
  //vid.setAttribute(muted,false);
  vid.muted = false;
}

function checkMute() {
  alert(vid.muted);
}
</script>

<p>Video courtesy of <a href="https://www.bigbuckbunny.org/" target="_blank">Big Buck Bunny</a>.</p>

</body>
```

위의 소스코드를 돌려보면 잘 동작하는 것을 확인할 수 있을 것이다. 어렵게 생각하지말고 (.)쓰자 :)


