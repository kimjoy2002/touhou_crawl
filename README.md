# touhou_crawl
던전크롤+동방 팬게임 동방크롤


던전크롤 스톤수프와 동방이 섞인 로그라이크 팬게임이다.


5년동안 발전이 없는 똥 게임이니 마음대로 굽고 삶고 해도 됨.


뭘 쓸지 잘 모르겠다.

# How To Build

일단 굉장히 오래된 프로젝트라서 빌드 과정이 약간 귀찮음

1. 다이렉트X 9.0 설치
https://www.microsoft.com/en-us/download/details.aspx?id=6812

DXSDK_JUN10 버전으로 설치하면됨


2. 컴파일러는 Visual Studio 2019를 이용하여 테스트함. 다른 컴파일러도 가능하겠지만 테스트해보진않아서 불확실

최근 커밋으로 VS 프로젝트 파일을 추가했음. 이걸로 로딩하거나

파일-새로만들기->기존 코드의 프로젝트 만들기로 직접 th_crawl폴더 안을 경로로 잡아서 C++ 프로젝트를 생성해도 됨


3. 포함(include) 디렉터리와 라이브러리(library) 디렉터리에 다이렉트X를 설정해야함

VS 프로젝트파일로부터 로딩했으면 설정되겠지만 내 로컬 경로라서 실제 설치된 경로랑 다를 수 있으니 다르다면 수정이 필요함

참고로 내 프로젝트에선

포함디렉터리:C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include

라이브러리디렉터리: C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86

로 되어있음


4. 빌드하기



덤-일부 트러블슈팅

- atlstr.h를 못찾음 -> visual studio검색에서 v142 빌드 도구용 C++ ATL(x86 및 x64)

- String.h를 string 으로 바꿈 (최근 커밋으로 고쳐졌으니 pull받으면 됨)

- crtdbg.h가 visual studio에 디펜던시가 있으므로 삭제 (최근 커밋으로 고쳐졌으니 pull받으면 됨)



2025/3
 - VSCODE 빌드 추가


2025/4
 - steam api 추가
   - steamworks_sdk(162사용중)를 받아서 연결해야함
 - D3D11로 전환
   - 이제 D3D9 sdk를 받을 필욘없지만 Windows Kits에 있는 d3D11 include/lib와 연결해야함
   - DirectXTK 다운로드후 include/lib와 연결 필요

---

스팀 무료 배포를 목표로 재개발중
- 다국어 지원 (완)
- 내부 data 암호화 및 난독화
- 스팀 api 추가 (완)
- 키 설정 추가 
- 고 해상도/폰트 크기 변경 지원 (완)
- 인게임 설정/모그 지원
- 마우스 지원 (완)
- 사운드/음악 어떻게 할지 고민하기
- 컨텐츠 추가 (새 몬스터, 고난이도를 위한 이변 시스템, 밸런싱, 도트 다듬기) 
- 그외 일부 레거시 코드 리펙토링 (리플레이 버그 수정등)
등등...

[디스코드 링크](https://discord.gg/jDUfvGZTq2)
