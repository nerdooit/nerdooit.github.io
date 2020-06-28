Delegate 초기화 하는 부분

ChromeMain()
	  content::ContentMainParams params(&chrome_main_delegate); 를 통해 delegate
		초기화
		  struct ContentMainParams로 되어져있음
			    explicit ContentMainParams(ContentMainDelegate\* delegate)
	  explicit은 뭔가?
		    - 자동형변환을 막기 위함
				  content::ContentMain()을 할 경우에 delegate가 change 됨. 상속
					구조이니까 upstream으로



					ChromeMain()
	  commandLine::Init()
	  content::ContentMain()
	    serviceManager::Main()
	      ContentServiceManagerMainDelegate::Initialize() // content 메니저가
	생성됨
	      // process type으로 어떤 프로세스를 run할 것인가 결정함.
	      ContentServiceManagerMainDelegate::RunEmbedderProcess() //
	RunEmbbederProcess를 통해 부름


	ContentMainRunnerImpl::Run()
	 RunBrowserProcessMain() // service manager는 browser에서 사용함
	  BrowserMain() 호출됨
		 RunOtherNamedProcessTypeMain()
	  //CHROME_MULTIPLE_DLL_BROWSER 기준으로 나뉨
	  - RunZygote()
	  -- ZygoteMain()
	  --- ProcessRequests()
	  ---- HandleRequestFromBrowser()
	  ----- HandleForkRequest()
	  ------ ReadArgsAndFork()
	  -------- ForkWithRealPid()

	0. zygote는 뭐하는 놈인지?
zygote readme를 읽어보자.


~~1. content runner가 어떻게 불리는지?~~
~~2. browser process외의 프로세스가 어떤 기준을 가지고 fork동작으로 가는지?~~
  - kProcessType 가지고 확인
    - empty이냐.. 아니냐
    -> empty가 어떻게 만들어지는데?
      내부적으로 process value들이 관리 된다. 만약 현재 프로세스의 이름을 얻고 싶다고 전달하면 출력이 되어야하는데 그게 안됨.
      process를 생성할 때, 자신의 value이름을 정해서 넣는다.
      넣지 않기 때문에 empty 인듯함 확실하게 보이지 않음(?) 즉, 다른 프로세스들은 zygote의 fork를 통해 생성됨
      ```java
      command_line->AppendSwitchASCII(switches::kProcessType,
                                switches::kCloudPrintServiceProcess);

      cmd_line.AppendSwitchASCII(switches::kProcessType, switches::kUtilityProcess);

      command_line->AppendSwitchASCII(switches::kProcessType,
                                switches::kRendererProcess);
      ```


ppoll
sigmask
epoll
poll
sigprocmask

- blocking nonblocking
- sync async
- callback
- 개념정리

