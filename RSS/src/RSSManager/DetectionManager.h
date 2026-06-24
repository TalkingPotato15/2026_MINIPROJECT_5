#pragma once

/**
 * @file DetectionManager.h
 * @brief RSS 레이다 탐지 영역과 탐지 중인 공중위협 캐시를 관리한다.
 */

#include "RSSInfoTypes.h"
#include <map>
#include <set>

/**
 * @brief RSS 레이다 탐지 범위와 탐지 상태 전이를 관리하는 클래스.
 *
 * 레이다 위치/반경을 기준으로 공중위협이 탐지 범위 안에 있는지 계산하고,
 * 현재 탐지 중인 표적의 마지막 유효 위치를 캐시한다. 표적이 범위를 벗어나면
 * RSSManager가 이 캐시를 이용해 마지막 위치를 전송한 뒤 탐지 상태를 해제한다.
 */
class DetectionManager
{
public:
	/**
	 * @brief 탐지 영역과 탐지 표적 캐시를 초기화한다.
	 */
	void reset();

	/**
	 * @brief RSS 레이다 탐지 영역을 설정한다.
	 * @param x 레이다 중심 X 좌표.
	 * @param y 레이다 중심 Y 좌표.
	 * @param z 레이다 중심 Z 좌표.
	 * @param radius 레이다 탐지 반경.
	 */
	void setDetectionArea(double x, double y, double z, double radius);

	/**
	 * @brief 유효한 탐지 영역이 설정되어 있는지 확인한다.
	 * @return 탐지 반경이 0보다 크면 true, 아니면 false.
	 */
	bool hasDetectionArea() const;

	/**
	 * @brief 레이다 중심과 공중위협 사이의 3차원 거리를 계산한다.
	 * @param atsInfo 거리 계산 대상 공중위협 정보.
	 * @return 레이다 중심과 공중위협 사이의 유클리드 거리.
	 */
	double getDistanceToRSS(const CachedATSInfo& atsInfo) const;

	/**
	 * @brief 공중위협이 현재 레이다 탐지 반경 안에 있는지 확인한다.
	 * @param atsInfo 범위 확인 대상 공중위협 정보.
	 * @return 탐지 영역이 설정되어 있고 거리가 반경 이하이면 true.
	 */
	bool isInRange(const CachedATSInfo& atsInfo) const;

	/**
	 * @brief 지정한 공중위협이 현재 탐지 중인지 확인한다.
	 * @param targetId 공중위협 식별자.
	 * @return 탐지 중인 표적이면 true.
	 */
	bool isDetected(uint32_t targetId) const;

	/**
	 * @brief 공중위협을 탐지 상태로 등록하고 최신 정보를 캐시에 저장한다.
	 * @param atsInfo 탐지된 공중위협 정보.
	 */
	void markDetected(const CachedATSInfo& atsInfo);

	/**
	 * @brief 탐지 중인 공중위협의 최신 정보를 갱신한다.
	 * @param atsInfo 갱신할 공중위협 정보.
	 */
	void updateDetectedTarget(const CachedATSInfo& atsInfo);

	/**
	 * @brief 지정한 공중위협을 탐지 목록과 캐시에서 제거한다.
	 * @param targetId 제거할 공중위협 식별자.
	 */
	void removeDetectedTarget(uint32_t targetId);

	/**
	 * @brief 탐지 중인 공중위협의 캐시 정보를 조회한다.
	 * @param targetId 조회할 공중위협 식별자.
	 * @return 캐시된 정보 포인터. 탐지 중이 아니면 nullptr.
	 */
	const CachedATSInfo* findDetectedTarget(uint32_t targetId) const;

private:
	/** @brief 현재 탐지 중인 공중위협 ID 집합. */
	std::set<uint32_t> detectedTargetIds;
	/** @brief 탐지 중인 공중위협의 마지막 유효 정보 캐시. */
	std::map<uint32_t, CachedATSInfo> detectedTargetInfoMap;

	/** @brief RSS 탐지 영역 설정 여부. */
	bool hasRSSDetectionArea = false;
	/** @brief RSS 레이다 중심 X 좌표. */
	double rssPosX = 0.0;
	/** @brief RSS 레이다 중심 Y 좌표. */
	double rssPosY = 0.0;
	/** @brief RSS 레이다 중심 Z 좌표. */
	double rssPosZ = 0.0;
	/** @brief RSS 레이다 탐지 반경. */
	double rssRadius = 0.0;
};
