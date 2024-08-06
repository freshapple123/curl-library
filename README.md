# curl-library
How to Interwork Curl Library with Visual Studio

우선 필자는 Visual Studio 2022 버전을 사용합니다.

## 1. 다운로드

[다운로드 링크](https://curl.se/download/)

위 사이트를 통해 최신 버전을 다운받습니다.

+) 2024.07.13 기준으로 최신 버전이 8.8.0입니다. 하지만 8.8.0 버전은 내부 파일에 솔루션 파일이 없어서 필자는 이전 버전인 8.7.1 버전을 사용하였습니다.

만일 최신 버전을 압축 해제 후, `[curl-버전]\projects\Windows` 파일이 존재하지 않으면 이전 버전을 사용하시길 바랍니다.

압축 해제 경로는 `C:\`인 C 드라이브에 바로 해제하여야 합니다.

---

## 2. 빌드

1. 압축 해제한 폴더를 열어서 `C:\curl-8.7.1\projects\Windows\VC14.30` 경로에 들어가서 솔루션 파일을 엽니다.

   +) VC 버전은 여러 개가 존재할 수 있습니다. 각자 원하는 버전을 사용하면 됩니다. 필자는 최신 버전인 VC14.30을 사용하였습니다.

   ![solution route](https://github.com/user-attachments/assets/23d752fd-a8c8-41b9-8fbb-b4046fdf6f82)
   솔루션 경로 이미지

2. 솔루션 파일을 열면 다음과 같은 화면이 나옵니다.

   ![solution file choose](https://github.com/user-attachments/assets/c3768aa9-33c6-4775-8ebc-0044fda792bb)
   솔루션 파일에서 선택해야 할 빌드

   위 그림과 같이 LIB 디버그와 릴리즈를 사용할 것입니다.

   +) DLL과 LIB의 차이는 동적/정적 라이브러리입니다. 동적 라이브러리는 추가적인 작업이 필요하고, 정적 라이브러리를 사용하더라도 신경 쓸 필요가 없습니다.

3. 차례로 하나를 선택하고 빌드를 실행합니다.

   필자는 릴리즈 모드에서 CURL 라이브러리와 별개로 최적화 오류가 발생하여 디버그 모드에 관해 설명하겠습니다. 릴리즈 모드를 사용하고자 할 경우 마지막 추가 종속성만 차이가 있습니다.

   ![solution build](https://github.com/user-attachments/assets/8642ee93-3b38-4ea6-b369-569cde570da7)
   솔루션 빌드

4. 빌드 이후, 폴더를 확인해 보면 다음과 같은 디버그 폴더가 생성된 것을 알 수 있습니다.

   ![debug file](https://github.com/user-attachments/assets/c19d6060-9d2b-4cf7-bd79-80d46edd3bb0)
   디버그 폴더

---

## 3. 폴더 옮기기

디버그 폴더에 있는 `libcurld.lib` 파일을 복사하여 `[curl-버전]\lib` 폴더에 붙여넣기 합니다.

---

## 4. CURL을 Visual Studio에서 사용하기

1. CURL 라이브러리를 사용하고 싶은 솔루션 파일을 엽니다.

2. **프로젝트** - **[파일이름] 속성** - **C/C++** - **일반** - **추가 포함 디렉토리**에 `C:\curl-버전\include`를 추가합니다.

   ![add directory](https://github.com/user-attachments/assets/6f428f81-eca7-4b28-b748-e27165533d15)
   추가 포함 디렉터리

3. **프로젝트** - **[파일이름] 속성** - **C/C++** - **전처리기** - **전처리기 정의**에 `CURL_STATICLIB`를 추가합니다.

4. **프로젝트** - **[파일이름] 속성** - **링커** - **일반** - **추가 라이브러리 디렉토리**에 `C:\curl-버전\lib`를 추가합니다.

5. **프로젝트** - **[파일이름] 속성** - **링커** - **입력** - **추가 종속성**에 `libcurld.lib`를 추가합니다.

   +) 만일 릴리즈 모드를 사용하고 싶다면, 속성의 상단에서 **구성**을 **릴리즈 모드**로 변경 후 모든 과정은 동일하지만, 추가 종속성에서 `d`를 뺀 `libcurl.lib`를 추가합니다.

6. 마지막으로, `main.cpp` 코드에 다음과 같은 코드를 추가합니다.

   ```cpp
   #define CURL_STATICLIB
   #pragma comment(lib, "libcurld.lib")
   #pragma comment(lib, "wldap32.lib")
   #pragma comment(lib, "ws2_32.lib")
   ```
외부참조 에러를 없애주는것으로 알고있으면 된다.

이러한 과정을 거치면, 해당 파일에 CURL 라이브러리 사용이 가능하다.

마지막으로 다음 해더파일을 사용하면 에러가 표시되지않고 사용가능할것이다.
````cpp
#include <curl/curl.h>
````
   
