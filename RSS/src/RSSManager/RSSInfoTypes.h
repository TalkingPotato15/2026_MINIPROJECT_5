#pragma once

/**
 * @file RSSInfoTypes.h
 * @brief RSS 탐지 및 요격 판정에서 사용하는 표적/유도탄 캐시 데이터 구조체를 정의한다.
 */

#include <cstdint>

/**
 * @brief RSS가 최근 탐지한 공중위협(ATS) 정보를 보관하는 캐시 구조체.
 *
 * ATSInformationToRSS 메시지의 targetInfo 항목을 RSS 내부 로직에서 사용하기 쉽도록
 * 평면 구조로 변환해 저장한다. targetId는 0부터 시작하는 유효 ID일 수 있으므로
 * 존재 여부 판단에 사용하지 않는다.
 */
struct CachedATSInfo
{
	/** @brief 공중위협 X 좌표. */
	double x = 0.0;
	/** @brief 공중위협 Y 좌표. */
	double y = 0.0;
	/** @brief 공중위협 Z 좌표. */
	double z = 0.0;
	/** @brief 공중위협 속도. */
	uint32_t speed = 0;
	/** @brief 공중위협 식별자. 0부터 시작하는 유효 ID이다. */
	uint32_t targetId = 0;
	/** @brief 공중위협 상태값. 0은 ready, 1은 active, 2는 destroyed를 의미한다. */
	uint32_t atsStatus = 0;
};

/**
 * @brief RSS가 수신한 유도탄(MSS) 정보를 보관하는 캐시 구조체.
 *
 * MSSInformationDownlinkToRSS 메시지의 missileInfo 항목을 RSS 내부 요격 판정에서 사용한다.
 * missileId와 targetId는 모두 0부터 시작할 수 있으므로, 미발사 여부는 mssStatus로 판단한다.
 */
struct CachedMSSInfo
{
	/** @brief 유도탄 X 좌표. */
	double x = 0.0;
	/** @brief 유도탄 Y 좌표. */
	double y = 0.0;
	/** @brief 유도탄 Z 좌표. */
	double z = 0.0;
	/** @brief 유도탄이 추적 중인 공중위협 식별자. */
	uint32_t targetId = 0;
	/** @brief 유도탄 식별자. 0부터 시작하는 유효 ID이다. */
	uint32_t missileId = 0;
	/** @brief 유도탄 상태값. 0은 미발사/대기, 1은 비행 중, 2는 종료 상태를 의미한다. */
	uint32_t mssStatus = 0;
};
