#pragma once
#include <vector>
#include <string>

class Node;
class NodeEntity;
class NodeActor;
class TrackKeyFrame;

class CineTrack
{
public:

	void InsertKeyFrame(TrackKeyFrame* frame, double time);
	void AddKeyFrame(TrackKeyFrame* frame);

private:

	Node* m_Node;
	NodeActor* m_Actor;
	std::vector<TrackKeyFrame*> m_KeyFrames;


};

