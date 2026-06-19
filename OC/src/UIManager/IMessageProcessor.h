#pragma once
class IMessageProcessor
{
public:
	IMessageProcessor() = default;
	// 인터페이스이기 때문에 virtual을 넣음. 상속 받은 클래스를 죽이는것.
	virtual ~IMessageProcessor() = default;

public:
	virtual void processMessage() = 0;
};

