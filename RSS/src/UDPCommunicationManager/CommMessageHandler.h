#pragma once
/**
 * @file CommMessageHandler.h
 * @brief UDP 수신 ICD 메시지 ID와 NOM 메시지 이름 간 매핑을 관리한다.
 */

#include <map>
#include <nFramework/util/util.h>

using namespace std;

/**
 * @brief ICD 메시지 ID를 NOM 메시지 이름으로 변환하는 테이블 관리자.
 *
 * UDPCommunicationManager는 UDP 수신 버퍼에서 ICD 메시지 ID를 확인한 뒤
 * 이 클래스의 매핑 테이블을 통해 대응되는 NOM 메시지 이름을 찾는다.
 */
class CommMessageHandler
{
public:
	/**
	 * @brief 메시지 ID-이름 테이블을 초기화한다.
	 */
	CommMessageHandler();

	/**
	 * @brief 메시지 핸들러 자원을 해제한다.
	 */
	~CommMessageHandler();

	/**
	 * @brief ICD 메시지 ID에 대응되는 NOM 메시지 이름을 조회한다.
	 * @param msgID 조회할 ICD 메시지 ID.
	 * @return 등록된 NOM 메시지 이름. 등록되지 않은 ID이면 빈 문자열이 반환될 수 있다.
	 */
	tstring getMsgName(unsigned short msgID);

	/**
	 * @brief ICD 메시지 ID와 NOM 메시지 이름의 매핑을 등록한다.
	 * @param msgID 등록할 ICD 메시지 ID.
	 * @param msgName msgID에 대응되는 NOM 메시지 이름.
	 */
	void setIDNameTable(unsigned short msgID, tstring msgName);

private:
	/**
	 * @brief 기본 메시지 ID-이름 매핑을 구성한다.
	 */
	void initialize();

	/**
	 * @brief 메시지 ID-이름 매핑 테이블을 정리한다.
	 */
	void release();

private:
	/** @brief ICD 메시지 ID와 NOM 메시지 이름 매핑 테이블. */
	map<unsigned short, tstring> idNameTable;
};
