#pragma once
#include <vector>
#include <string>

class Mesh3D;
class NodeEntity;
class Node;

class Importer
{
public:

	Node* ImportNode(std::string path);
	Node* ImportActor(std::string path);

private:

};

