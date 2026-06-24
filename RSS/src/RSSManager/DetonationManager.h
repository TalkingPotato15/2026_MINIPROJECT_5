#pragma once

/**
 * @file DetonationManager.h
 * @brief RSS 요격 성공 판정과 파괴 처리된 표적 목록을 관리한다.
 */

#include "RSSInfoTypes.h"
#include <set>

/**
 * @brief ATS-MSS 간 거리 기반 요격 판정과 중복 파괴 이벤트를 관리하는 클래스.
 *
 * RSS는 현재 탐지 중인 공중위협에 대해서만 유도탄과의 거리를 계산한다.
 * 거리가 INTERCEPT_DISTANCE_THRESHOLD 이하가 되면 요격 성공으로 판단하고,
 * 한 번 파괴 처리된 표적은 중복 이벤트 전송을 막기 위해 destroyedTargetIds에 저장한다.
 */
class DetonationManager
{
public:
	/**
	 * @brief 파괴 처리된 표적 목록을 초기화한다.
	 */
	void reset();

	/**
	 * @brief 지정한 공중위협이 이미 파괴 처리되었는지 확인한다.
	 * @param targetId 공중위협 식별자.
	 * @return 이미 파괴 처리된 표적이면 true.
	 */
	bool isDestroyed(uint32_t targetId) const;

	/**
	 * @brief 지정한 공중위협을 파괴 처리 목록에 등록한다.
	 * @param targetId 파괴 처리할 공중위협 식별자.
	 */
	void markDestroyed(uint32_t targetId);

	/**
	 * @brief 공중위협과 유도탄 사이의 3차원 거리를 계산한다.
	 * @param atsInfo 공중위협 위치 정보.
	 * @param mssInfo 유도탄 위치 정보.
	 * @return 공중위협과 유도탄 사이의 유클리드 거리.
	 */
	double getDistance(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const;

	/**
	 * @brief 공중위협과 유도탄 사이의 거리가 요격 성공 조건을 만족하는지 확인한다.
	 * @param atsInfo 공중위협 위치 정보.
	 * @param mssInfo 유도탄 위치 정보.
	 * @return 거리가 요격 임계값 이하이면 true.
	 */
	bool isIntercepted(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const;

private:
	/** @brief 요격 성공으로 판정하는 ATS-MSS 간 최대 거리. */
	static constexpr double INTERCEPT_DISTANCE_THRESHOLD = 1.0;
	/** @brief 이미 파괴 처리되어 TargetDestroyed 이벤트가 전송된 표적 ID 집합. */
	std::set<uint32_t> destroyedTargetIds;
};
