#include "pch.h"
#include "SceneGraph.h"
#include "Node.h"
#include "NodeEntity.h"
#include "NodeCamera.h"
#include "Engine.h"
#include "Mesh3D.h"

SceneGraph::SceneGraph() {

	m_Camera = new NodeCamera;
	m_RootNode = new Node();
	m_RootNode->SetName("Graph Root");

}

void SceneGraph::AddNode(Node* node) {

	m_RootNode->AddNode(node);

}

void SceneGraph::AddLight(NodeLight* light) {

	m_Lights.push_back(light);

}

void SceneGraph::Render() {

	Engine::m_Camera = m_Camera;
	Engine::m_Lights = m_Lights;
	m_RootNode->Render();
	

}

NodeCamera* SceneGraph::GetCamera() {

	return m_Camera;

}

float dot(const float3& a, const float3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length(const float3& v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
float3 cross(const float3& a, const float3& b)
{
    return float3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

constexpr float EPSILON = 1e-6f;

HitResult RayToTri(float3 pos,float3 end, float3 v0, float3 v1, float3 v2)
{

    float3 edge1, edge2, h, s, q;
    float a, f, u, v;
    HitResult res = HitResult();

    edge1 = v1 - v0;// vertex1 - vertex0;
    edge2 = v2 - v0;
    h = cross(end, edge2);


    a = dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return res;    // This ray is parallel to this triangle.
    f = 1.0f / a;
    s =pos - v0;
    u = f *dot(s, h);
    if (u < 0.0f || u > 1.0f)
        return res;
    q = cross(s, edge1);
    v = f * dot(end, q);
    if (v < 0.0f || u + v > 1.0f)
        return res;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * dot(edge2, q);

    if (t > EPSILON) // ray intersection
    {
        //outIntersectionPoint = rayOrigin + rayVector * t;
        res.m_Hit = true;
        res.m_Point =pos + end * t;
        res.m_Distance = length(res.m_Point - pos);
        return res;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return res;

    res.m_Hit = false;
    return res;

    return res;
}


HitResult RayCastMesh(float3 pos, float3 end, Mesh3D* mesh) {

    float cd = 100000;
    HitResult close;

    auto world = mesh->GetOwner()->GetWorldMatrix();

    for (auto t : mesh->GetTris())
    {

        float3 v0, v1, v2;



        v0 = mesh->GetVertices()[t.v0].position * world;
        v1 = mesh->GetVertices()[t.v1].position * world;
        v2 = mesh->GetVertices()[t.v2].position * world;

        HitResult res = RayToTri(pos, end, v0, v1, v2);
        if (res.m_Hit) {
            if (res.m_Distance < cd) {
                cd = res.m_Distance;
                close = res;
                close.m_Mesh = mesh;
                close.m_Node = (Node*)mesh->GetOwner();
                close.m_Entity = mesh->GetOwner();
            }
        }
    }

 //   printf("CD:%f\n", cd);

    return close;

}

HitResult SceneGraph::MousePick(int x, int y, NodeEntity* entity) {

    float fx = (float)x;
    float fy = (float)y;
    float mx = -1 + (float)(x) / (float)(Engine::m_FrameWidth) * 2;
    float my = 1 - (float)(y) / (float)(Engine::m_FrameHeight) * 2;

    float3 origin = float3(mx, my, 0);
    float3 dest = float3(mx, my, 1.0f);



    //Matrix4x4 viewProj = RenderGlobals.CurrentCamera.WorldMatrix * RenderGlobals.CurrentCamera.ProjectionMatrix;
    float4x4 viewProj = Engine::m_Camera->GetWorldMatrix() * Engine::m_Camera->GetProjection();

    // Matrix4x4 vp;
    // Matrix4x4.Invert(viewProj, out vp);
    // Matrix4x4 inverseProj = vp;


    float4x4 inverseProj = viewProj.Inverse();


    //****Ve
    //Vector3 ray_origin = Vector3.Transform (origin, inverseProj);
    //Vector3 ray_end = Vector3.TransformNormal(dest, inverseProj);
    //Vector4 ro = Vector4.Transform(origin, inverseProj);
    //Vector4 rd = Vector4.Transform(dest, inverseProj);

    float4 ro = float4(origin, 1.0f) * inverseProj;
    float4 rd = float4(dest, 1.0) * inverseProj;


    float3 ray_origin = float3(ro.x / ro.w, ro.y / ro.w, ro.z / ro.w);
    float3 ray_end = float3(rd.x / rd.w, rd.y / rd.w, rd.z / rd.w);
    float3 ray_dir = ray_end - ray_origin;

    //Vector3 ray_origin = new Vector3(ro.X / ro.W, ro.Y / ro.W, ro.Z / ro.W);
    //Vector3 ray_end = new Vector3(rd.X / rd.W, rd.Y / rd.W, rd.Z / rd.W);
    //Vector3 ray_dir = ray_end - ray_origin;

    ray_dir = normalize(ray_dir);


    float cd = 10000.0f;
    HitResult close;
    close.m_Hit = false;

    for (auto mesh : entity->GetMeshes()) {

        HitResult res = RayCastMesh(m_Camera->GetPosition(), ray_dir,mesh);
        if (res.m_Hit) {
            if (res.m_Distance < cd) {
                cd = res.m_Distance;
                close = res;
            }
        }

    }

    return close;

}

HitResult SceneGraph::MousePick(int x, int y)
{
	float fx = (float)x;
	float fy = (float)y;
    float mx = -1 + (float)(x) / (float)(Engine::m_FrameWidth) * 2;
    float my = 1 - (float)(y) / (float)(Engine::m_FrameHeight) * 2;

    float3 origin = float3(mx, my, 0);
    float3 dest = float3(mx, my, 1.0f);



    //Matrix4x4 viewProj = RenderGlobals.CurrentCamera.WorldMatrix * RenderGlobals.CurrentCamera.ProjectionMatrix;
    float4x4 viewProj = Engine::m_Camera->GetWorldMatrix() * Engine::m_Camera->GetProjection();

   // Matrix4x4 vp;
   // Matrix4x4.Invert(viewProj, out vp);
   // Matrix4x4 inverseProj = vp;


    float4x4 inverseProj = viewProj.Inverse();


    //****Ve
    //Vector3 ray_origin = Vector3.Transform (origin, inverseProj);
    //Vector3 ray_end = Vector3.TransformNormal(dest, inverseProj);
    //Vector4 ro = Vector4.Transform(origin, inverseProj);
    //Vector4 rd = Vector4.Transform(dest, inverseProj);

    float4 ro = float4(origin,1.0f) * inverseProj;
    float4 rd = float4(dest, 1.0) * inverseProj;


    float3 ray_origin = float3(ro.x / ro.w, ro.y / ro.w, ro.z / ro.w);
    float3 ray_end = float3(rd.x / rd.w, rd.y / rd.w, rd.z / rd.w);
    float3 ray_dir = ray_end - ray_origin;

    //Vector3 ray_origin = new Vector3(ro.X / ro.W, ro.Y / ro.W, ro.Z / ro.W);
    //Vector3 ray_end = new Vector3(rd.X / rd.W, rd.Y / rd.W, rd.Z / rd.W);
    //Vector3 ray_dir = ray_end - ray_origin;

    ray_dir = normalize(ray_dir);

    //Ray ray = new Ray();


   // ray.Pos = RenderGlobals.CurrentCamera.Position;
   // ray.Dir = ray_dir;
   // return ray;
	HitResult result = RayCast(m_Camera->GetPosition(),ray_dir);


	return result;
}

HitResult RayCastNode(Node* node) {

    
    return HitResult();
}

std::vector<Mesh3D*> GetMeshes(Node* node, std::vector<Mesh3D*> meshes)
{

    NodeEntity* pEntity = dynamic_cast<NodeEntity*>(node);

    if (pEntity) {
        // Casting successful, pNode is a nodeEntity
        //pEntity->entityFunction();

        for (auto mesh : pEntity->GetMeshes()) {

            meshes.push_back(mesh);

        }
    }

    for (auto sub : node->GetNodes()) {
        meshes = GetMeshes(sub, meshes);

    }

    return meshes;

}


HitResult SceneGraph::RayCast(float3 pos, float3 end) {


    HitResult result;

    std::vector<Mesh3D*> meshes;
    float cd = 10000;
    HitResult close;

    meshes = GetMeshes(m_RootNode,meshes);

    for (auto mesh : meshes) {

        auto res = RayCastMesh(pos, end, mesh);
        if (res.m_Hit) {
            if (res.m_Distance < cd) {
                close = res;
                res.m_Entity = res.m_Mesh->GetOwner();
                
            }
        }

    }

    int b = 5;

    //result = RayCastNode(m_RootNode);


    return close;

}