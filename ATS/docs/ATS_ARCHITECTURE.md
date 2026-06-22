# ATS 프로젝트 아키텍처

## 실행 컴포넌트

- `UDPCommunicationManager`: 운용통제기 UDP 메시지 송수신과 외부/내부 NOM 변환
- `ScenarioManager`: 공통 시나리오에서 ATS용 `sceneInfo[4]` 파싱 및 검증
- `ManeuverManager`: 공중위협 4대의 경로 기동, 상태 관리, 1 Hz 상태 발행

Manager 간에는 직접 메서드 호출 대신 nFramework MEB/NOM 메시지를 사용한다.

## 공중위협 시나리오 구조

```text
Scenario(0x01)
└─ sceneInfo[4]                 // 배열 인덱스가 targetId(0~3)
   ├─ ATSPos[4]                // 순서대로 4개 경로점
   │  └─ x, y, z
   └─ speed
```

속도가 0이고 네 경로점이 모두 `(0,0,0)`인 슬롯은 미설정 표적으로 처리한다.

## 상태

### ATS 모의기 상태

| 값 | 상태 |
|---:|---|
| 0 | IDLE |
| 1 | READY |
| 2 | RUNNING |

### 공중위협 상태

| 값 | 상태 |
|---:|---|
| 0 | READY |
| 1 | FLYING |
| 2 | DESTROYED |

## 메시지 흐름

```text
OC Scenario(0x01)
  → UDPCommunicationManager
  → InnerSendScenario(0x21)
  → ScenarioManager
  → InnerSendScenarioToModel(0x23)
  → ManeuverManager

OC StartSimulation(0x06)
  → InnerStartSimulation(0x24)
  → ScenarioManager
  → InnerStartSimulationToModel(0x26)
  → ManeuverManager

ManeuverManager (1 Hz)
  → InnerAirThreatInfoToComm(0x41)
  → UDPCommunicationManager
  → OC ATSStatus(0x02)

OC ATSInterceptionResult(0x0E)
  → InnerAirThreatDetonationToATM(0x40)
  → ManeuverManager
  → targetID에 해당하는 공중위협 이동 정지 및 DESTROYED 전환

OC Stop(0x10)
  → InnerStopSimulation(0x27)
  → ScenarioManager
  → InnerStopSimulationToModel(0x29)
  → ManeuverManager
```

`missionFlag=0`은 요격 성공, `missionFlag=1`은 실패로 처리한다.

## 기동 모델

각 공중위협은 자신의 `ATSPos[0]`에서 시작한다. `FLYING` 상태에서는 1초마다 `speed × 1초` 거리만큼 다음 경로점을 향해 등속 직선 이동한다. 경로점을 통과하고 이동 거리가 남으면 다음 구간으로 이어서 이동하며, 마지막 경로점 도착 시 `READY`로 전환한다. `DESTROYED` 상태에서는 더 이상 위치를 갱신하지 않는다.
