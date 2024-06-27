#pragma once
#include <vector>

class PostProcess;
class Draw2D;

class PostProcessing
{
public:

	PostProcessing();
	void AddPostProcess(PostProcess* process);
	void Process();

private:

	std::vector<PostProcess*> m_Processes;
	Draw2D* m_Draw;

};

