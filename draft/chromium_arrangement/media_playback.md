### Playback
크로미움에서 미디어를 동작했을 때, 어떻게 동작하는지 알아보자.

Chromium 같은 경우 media 재생동작을 S/W를 이용해 동작하도록 구현해두었다. Open
source로 제공되고 있으며, demuxer 같은 경우 library를 이용하도록 한다. 자세한
설명은 [여기]() 를 클릭해 함께 알아보자. 미디어 같은 경우 Platform 의존성이
있으며, Platform에 맞게 H/W 디코딩을 활용한다면 향상된 미디어를 느낄 수 있다.

미디어를 재생함에 있어 미디어영역에서는 다양한 기법들을 포함하고 있다. 재생
동작을 세부적으로 보기에는 너무 방대한 양이며, 전반적인 흐름을 체크하도록 하자.

미디어 디렉토리 안에는 미디어 demuxing, S/W & H/W 비디오 디코더, 음향출력 그리고
비디오 / 음향 renderer 들이 존재한다.

아래는 전반적인 미디어 재생 파이프라인을 설명한다.

![media pipeline](/img/media_playback.png)

우리는 <video> tag가 어떻게 재생을 하는지를 기준으로 살펴보자.

비디오 재생은 blink::HTMLMediaElement를 상속받는 <video> (or <audio>) 테그를
이용해 content::MediaFactory를 통해 생성되는 media::WebMediaPlayerImpl 까지
도달해야 가능하다. 각 blink::HTMLMediaElement는 비디오를 제어하기 위한 동작
seek, play, pause등을 요청하기 위해 media::WebMediaPlayerImpl를 포인팅 하고
있다. (이름은 WebMediaPlayer로 포인팅 하고 있음)

위의 그림에서 볼 수 있듯, media::WebMediaPlayerImpl (그림에서는 WebMediaPlayer로
		나타남) 네트워크를 통한 미디어 로딩, 디먹싱 그리고 파이프라인을 초기화 하는
동작을을 한다. media::WebMediaPlayerImpl가 가지고 있는 media::PipelineController
통해 로딩, video / audio rendering 동작을 한다.

아래는 간단한 루틴을 설명한다. WebMediaPlayer가 load된 이후 Data source 초기화
및 pipeline을 생성하는 부분이다. pipeline을 생성하는 부분에서 만약 FFMPEG S/W
디코더를 사용하겠다는 플래그를 설정하게 된다면, 해당 Data source를 Demuxer에
전달한다.

```java
WebMediaPlayerImpl::DoLoad()
	WebMediaPlayerImpl::DataSourceInitialized(bool success)
		WebMediaPlayerImpl::StartPipeline()
		/* demuxer에서 소스코드 담은 후 초기화 아래에 있음 */
```

```java
// demuxer에서 소스코드 담은 후 초기화 아래에 있음

// FFMPEG, S/W 디코더 사용할 건지 빌드 플레그 설정되 있을 경우만 동작함.
#if BUILDFLAG(ENABLE_FFMPEG)
    Demuxer::MediaTracksUpdatedCB media_tracks_updated_cb =
        BindToCurrentLoop(base::Bind(
            &WebMediaPlayerImpl::OnFFmpegMediaTracksUpdated, weak_this_));

		// demuxer를 받은 data source로 리셋
    demuxer_.reset(new FFmpegDemuxer(
        media_task_runner_, data_source_.get(), encrypted_media_init_data_cb,
        media_tracks_updated_cb, media_log_.get(), IsLocalFile(loaded_url_)));
#else
```

렌더러 동작
