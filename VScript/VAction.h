#pragma once

class VContext;
class VVar;

class VAction
{
public:

	virtual VVar* Exec() { return nullptr; };
	virtual void SetContext(VContext* context);
	VContext* GetContext();

private:

	VContext* m_Context;

};


