# Overlapped I/O 모델과 IOCP 모델
### Overlapped I/O
* **중첩(Overlapped) 입출력**이라는 의미로, I/O가 처리되기 전에 리턴되는 **비동기적** 방식으로 작동하는 모델
* 입출력에 대한 완료 알림이 오면 그 때 작업을 수행하도록 하는데, 방식은 두 가지가 있다.
	1. **이벤트(시그널)** 통지
	2. **콜백 함수** 등록


### Overlapped 구조체
* 중첩 I/O **작업(WSASend, WSARecv 등) 한 건마다 한 개씩** 생성된다.
* 작업이 완료될 때까지 해당 구조체를 보존해야 한다!


### 동기-비동기 / 블락-논블락 개념
* **동기** : 리턴 시 작업이 끝남을 보장해준다
* **비동기** : 리턴 시 작업이 끝남을 보장할 수 없다
* **블락** : 작업이 *지금 완수될 수 없다면* 블락한다
* **논블락** : 작업이 *지금 완수될 수 없으면* 바로 리턴한다

---

## Overlapped I/O 모델
### 이벤트 통지 방식
* **WSAWaitForMultipleEvents()** 로 시그널을 받고, **GetOverlappedResult()**로 **lpcbTransfer**에 몇 바이트가 작업되었는지 알 수 있다.
	* 어느 소켓인지, Send, Recv 중 어떤 종류의 작업인지는 알려주지 않는다!
	* 이벤트는 **64**개만 등록할 수 있다.

### Async Procedure Call 방식
* Overlapped 구조체에 **콜백 함수 포인터**를 넣는다.
* I/O 요청 후 Alertable Wait 상태에 진입하게 해주는 ...Ex 함수를 호출
* 입출력이 완료되면 각 스레드마다 존재하는 **APC 큐**에 **Completion Routine**를 넣는다.
* **Alertable Wait** 상태로 존재하는, ***I/O를 요청한** 스레드*는 APC 큐에 완료 루틴이 들어오면 Dequeue해 작업을 처리한다.

---

## IOCP 모델
* **I/O 완료 통지**가 들어오는 완료 통지 포트(**Completion Port**)를 사용해 해당 통지를 Dequeue하여, **블락된 워커 스레드를 깨우고 작업을 처리**하도록 하는 스레드 풀
* **CreateIOCompletionPort()** 함수
	* 완료 통지 포트 생성
	* 소켓 등록
	* 생성 시, **CPU의 논리 프로세서 이하의 개수**만이 **NumberOfConcurrentThreads 인자로 들어가야 한다.** (논리프로세서 이상의 스레드가 Running 상태가 되어봐야 **잦은 컨텍스트 스위칭**으로 성능이 더 떨어진다)
	* Running 중이던 워커 스레드가 작업 처리 중 블락이 된다면 다른 완료 통지가 Dequeue될 수 있고, 블락됐던 워커 스레드가 다시 Running 상태가 되어 **러닝 중인 스레드 개수가 NumberOfConcurrentThreads의 개수를 초과할 수 있다.**
	* 그러나, **완료 통지가 들어오는 순간 러닝 스레드의 개수가 NumberOfConcurrentThreads 이상일 경우 더는 Running 상태로 깨우지 않는다.**
	* 완료 통지 포트는 **Nonpaged Pool**에 속한다.
* **GetQueuedCompletionStatus()** 함수
	* 이 함수를 호출하는 스레드는 해당 완료 통지 포트의 워커 스레드로 등록됨 *(한 번 등록하면 계속 취급된다)*
	* **완료 통지를 Dequeue**하면서 **워커 스레드를 블락 상태에서 깨어나게** 함