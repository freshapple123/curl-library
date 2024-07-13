# curl-library
How to Interwork Curl Library with Visual Studio<br>
우선 필자는 visual studio 2022 버전을 사용한다.<br><br><br>



**1.[다운로드]**

<https://curl.se/download/>

위 사이트를 통해 최신 버전을 다운받는다.

+) 2024.07.13 기준으로 최신버전이 8.8.0 버전이다. 하지만 8.8.0버전은 내부 파일에 솔루션 파일이 없어서
필자는 이전버전인 8.7.1버전을 사용하였다.
<br><br>


만일 최신버전을 압축 해제후, [curl-버전]\projects\Windows 파일이 존재하지 않으면 이전버전버전을 사용하길 바란다.

압축해제 경로는 C:\ 인 C드라이브에 바로 해제하여야 한다.


<br><br><br>

---

<br><br><br>


**2.[빌드]**

압축해제한 폴더를 열어서 C:\curl-8.7.1\projects\Windows\VC14.30 경로에 들어가서 솔루션 파일을 연다.

+) VC버전은 여러개가 존재할 수도 있다. 각자 원하는 버전을 사용하면된다. 필자는 최신버전인 vc14.30을 사용하였다.

![solution rute](https://github.com/user-attachments/assets/23d752fd-a8c8-41b9-8fbb-b4046fdf6f82)
솔루션 경로 이미지


솔루션 파일을 연다. 다음과 같은 화면이 나올것이다.

![solution file choose](https://github.com/user-attachments/assets/c3768aa9-33c6-4775-8ebc-0044fda792bb)
솔루션 파일에서 선택해야할 빌드

위 그림과 같이 LIB 디버그와 릴리즈를 사용할것이다.

+) DLL과 LIB의 차이는 동적/정적 라이브러리 인데 동적 라이브러리는 추가적인 작업이 필요하고,
정적 라이브러리를 사용하더라도 신경안써도 된다.
<br><br>

차례로 한개를 선택하고 빌드를 실행시킨다.

필자는 릴리즈모드에서 CURL라이브러리와 별개로 최적화 오류가 발생하여 디버그 모드에 관해 설명하겠다.
혹여나 릴리즈 모드를 사용을 원하더라도 마지막 추가종속성만 차이가 존재한다.

![solution build](https://github.com/user-attachments/assets/8642ee93-3b38-4ea6-b369-569cde570da7)
솔루션 빌드

빌드 이후, 폴더를 확인 해보면

![debug file](https://github.com/user-attachments/assets/c19d6060-9d2b-4cf7-bd79-80d46edd3bb0)
디버그 폴더

이러한 경로에 폴더가 생긴것을 알 수 있다.


<br><br><br>

---


<br><br><br>

**3.[폴더 옮기기]**

디버그 폴더에 libcurld.lib를 복사하여 [curl-버전]\lib 의 폴더에 붙여넣기를 한다.

<br><br><br>
---

<br><br><br>
**4.[ CURL visual studio에서 사용하기]**

1. 우선 curl 라이브러리를 사용하고 싶은 솔루션 파일을 연다.

2. 프로젝트 - [파일이름]속성 - C/C++ - 일반 - 추가 포함 디렉토리에 C:\curl-버전\include 를 추가한다.

![add directoty](https://github.com/user-attachments/assets/6f428f81-eca7-4b28-b748-e27165533d15)
추가 포함 디렉터리

3. 프로젝트 - [파일이름]속성  - C/C++ - 전처리기 - 전처리기 정의에 CURL_STATICLIB 를 추가한다.

4. 프로젝트 - [파일이름]속성  - 링커 - 일반 - 추가 라이브러리 디렉토리에  C:\curl-버전\lib 를 추가한다.

5. 프로젝트 - [파일이름]속성  - 링커 - 입력 - 추가 종속성에 libcurld.lib 를 추가한다.

+) 만일 릴리즈 모드를 사용하고 싶을땐 속성의 상단의 구성에서 릴리즈모드로 변경후 모든 과정은 동일하지만,
추가 종속성에서 d를 뺀  libcurl.lib 를 추가한다.

<br><br>

6. 마지막으로, main.cpp 코드에 다음과 같은 코드를 추가한다.

```C++
#define CURL_STATICLIB
#pragma comment(lib, "libcurld.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")
```
<br><br>
외부참조 에러를 없애주는것으로 알고있으면 된다.
<br><br><br>


---
<br><br><br>


이러한 과정을 거치면, 해당 파일에 CURL 라이브러리 사용이 가능하다.

마지막으로 다음 해더파일을 사용하면 에러가 표시되지않고 사용가능할것이다.
````C++
#include <curl/curl.h>
````

<br><br>

