### Component 전달 방식
Component간 전달방식에 대해 알아보자. (i)을 통해 우리는 Chromium에서 주 사용 프로세스인 Browser Process 와 Renderer에 대해 알아보았다. 위에서 주로 언급된 RenderProcessHost와 RenderProcess 간 데이터 전달은 어떤 방식으로 일어나는지 알아보자.

#### IPC
Browser 와 Renderer는 둘 다 Process이다. Process는 상호독립존재로 자신만의 고유한 메모리 영역을 갖고 있다. 따라서, 하나의 Process는 다른 Process에 접근을 할 수 없도록 구성되어져있다. 그렇다면, 어떻게 데이터를 주고 받을 것인가? Browser Process와 Renderer는 ***IPC (inter process communication)*** 을 활용해 데이터를 주고 받는다. 운영체제를 공부하다보면 IPC에 대해 접할 경우가 많이 있다. Chromium에서는 IPC를 named pipe를 이용해 구현하고 있다. Pipe는 Browser process내 channel(ChannelProxy 객체) 과 RenderProcess에 연결되어져 있다. 통신 같은 경우 Browser에서 Renderer에게 할 수 있고 Renderer에서 Browser로 할 수 있다. 따라서, 양방향으로 구현되어져있으며 필수적으로 listener interface를 구현하고 있다. [IPC chromium](https://www.chromium.org/developers/design-documents/inter-process-communication) 문서를 읽어보자 (해당 블로그에서 추후에 IPC 자료를 정리하고자 한다.)

#### Channel Proxy
RenderProcess에서는 Browser process의 main process와 직접적으로 통신하지 않는다.
앞 포스팅에서 봤듯이, I/O thread를 이용해 통신한다. 구체적으로 작업을 I/O
thread에서 접근하는 ChannelProxy에서 처리하도록 한다. Channel과 통신하는거
아닌가? 할 수 있지만, Channel 같은 경우 thread safe가 만족되지 않는다. 


---
#### Reference
[Zico Deng 블로그](https://medium.com/@zicodeng/explore-the-magic-behind-google-chrome-c3563dbd2739)

---
#### Memorization
- dominant - 우세한
- proprietary - 소유권의
