# Windows 소켓 프로그래밍 - 에러 처리, WinSock 초기화, 소켓 생성

## 1. 에러 처리
네트워크에서는 오류 발생 빈도도 높고 원인도 다양하므로, 에러를 사용자에게 알려줄 수 있어야 한다.

* **리턴 값의 에러 코드를 통해 내용을 확인하는 방법**
	* **WSAGetLastError()** : 소켓 함수 호출에서 에러 발생 시 가장 마지막에 발생한 오류 코드를 얻어옴
	* **FormatMessage()** : 에러 코드를 통해 에러 메시지를 얻어옴
		* **DWORD dwFlags** : *FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESAGE_FROM_SYSTEM*
		에러 메시지를 저장할 공간을 함수가 알아서 할당하고, 운영 체제로부터 에러 메시지를 가져온다는 의미
		* **LPCVOID lpSource** : NULL
		* **DWORD dwMessageId** : 에러 코드
		* **DWORD dwLanguageId** : 에러 메시지를 표시할 언어 설정
			* *MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)* : 제어판의 기본 언어로 설정
		* **LPTSTR lpBuffer** : 에러 메시지의 주소값을 저장할 변수의 주소.

에러 메시지 사용이 끝나면, 시스템이 할당한 메모리를 반환하기 위해 **LocalFree**()를 사용해야 한다. 

## 2. WinSock 초기화
* **WSAStartup()** : **윈속 라이브러리를 초기화**해주는 함수
	* *실패 시, 메모리에 WS2_32.dll이 로드되지 않음*
	* 요청할 윈속 버전(**MAKEWORD(2, 2)**)과 **WSADATA 구조체의 주소**값을 매개변수로 전달한다.
* **WSACleanup()** : 윈속 사용 완료 후 종료해주는 함수

## 3. 소켓 생성
* **Socket()**
	* **af** : 주소 체계를 지정
	
	| 매크로 변수명 | 주소 체계 |
	|-|-|
	|***AF_INET***|TCP,UDP, ...|
	|AF_INET6|IPv6|
	|AF_IRDA|IrDA|	
	|AF_BTH|Bluetooth RFCOMM/L2CAP |
	
	* **type** : 소켓 타입을 지정

	|소켓 타입|설명|
	|-|-|
	|**SOCKET_STREAM**|신뢰성 있음, 연결형 프로토콜 (TCP)|
	|SOCKET_DGRAM|신뢰성 없음, 비연결형 프로토콜 (UDP)|

	* **protocol** : 사용할 프로토콜 지정 *(대개 소켓과 주소만으로 결정 가능하므로 0 사용)*

	|프로토콜|매크로 변수명|
	|-|-|
	|**TCP**|IPPROTO_TCP|	
	|UDP|IPPROTO_UDP

* **closesocket()** : 소켓 사용 완료 후 닫아주는 함수