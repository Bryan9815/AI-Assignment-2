#include "SceneAI.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "Waiter.h"
#include "Chef.h"
#include "Cashier.h"
#include "Customer.h"
#include "MessageBoard.h"
SceneAI::SceneAI()
{
}

SceneAI::~SceneAI()
{
}

void SceneAI::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;
	Mtx44 Rotation;
	Rotation.SetToRotation(90, 0, 0, 1);

	Math::InitRNG();

	//Exercise 1: initialize m_objectCount
	m_objectCount = 0;
	m_ghost = new GameObject(GameObject::GO_BALL);

    Entity_Manager = EntityManager::GetInstance();
    Entity_Manager->Init();

#define EntityMoveWidth m_worldWidth
#define EntityMoveHeight (m_worldHeight * 0.25) * 3

    Chef *chef = new Chef();
    chef->Init(Vector3(m_worldWidth * 0.4f, m_worldHeight * 0.33f, 0));
    
	Waiter *waiter = Waiter::GetInstance();
    waiter->Init();
	
	Cashier *cashier = new Cashier();
	cashier->Init(Vector3(m_worldWidth *0.7f, m_worldHeight * 0.333f, 0));

	Customer *customer = Customer::GetInstance();
	customer->Init();
}

GameObject* SceneAI::FetchGO()
{
	//Exercise 2a: implement FetchGO()
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		if (!(*it)->active)
		{
			(*it)->active = true;
			m_objectCount += 1;
			return (*it);
		}
	}
	// No inactive object found
	for (int i = 0; i < 10; i++)
	{
		m_goList.push_back(new GameObject(GameObject::GO_NONE));
	}
	GameObject* go = m_goList.back();;
	go->active = true;
	m_objectCount += 1;
	return go;
}

bool SceneAI::CheckCollision(GameObject *go1, GameObject *go2, float dt)
{
	switch (go2->type)
	{
	case GameObject::GO_BALL:
	{
		if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL)
		{
			float distanceSquared = ((go1->pos + go1->vel * dt) - (go2->pos - go2->vel * dt)).LengthSquared();
			float combinedRadiusSquared = (go1->scale.x + go2->scale.x) * (go1->scale.x + go2->scale.x);
			Vector3 relativeVelocity = go1->vel - go2->vel;
			Vector3 relativeDisplacement = go2->pos - go1->pos;
			return distanceSquared < combinedRadiusSquared && relativeVelocity.Dot(relativeDisplacement) > 0;
		}
	}
	case GameObject::GO_WALL:
	{
		Vector3  w0 = go2->pos;
		Vector3 b1 = go1->pos;
		Vector3 N = go2->normal;
		float r = go1->scale.x;
		float h = go2->scale.x;
		float l = go2->scale.y;

		Vector3 NP(-N.y, N.x);

		Vector3 RV = go1->vel;
		Vector3 RD = w0 - b1;

		if (RD.Dot(N) < 0)
			N = -N;

		return abs(RD.Dot(N)) < r + h / 2 && abs(RD.Dot(NP)) < l / 2 && RV.Dot(N) > 0;
	}
	}
}

void SceneAI::CollisionResponse(GameObject *go1, GameObject *go2)
{
	switch (go2->type)
	{
	case GameObject::GO_BALL:
	{
		//Exercise 8b: store values in auditing variables
		m1 = go1->mass;
		m2 = go2->mass;
		u1 = go1->vel;
		u2 = go2->vel;

		Vector3 u1N, u2N, N;
		N = (go2->pos - go1->pos).Normalized();

		u1N = u1.Dot(N) * N;
		u2N = u2.Dot(N) * N;
		go1->vel = u1 + (2 * m2) / (m1 + m2) * (u2N - u1N);
		go2->vel = u2 + (2 * m1) / (m1 + m2) * (u1N - u2N);

		v1 = go1->vel;
		v2 = go2->vel;
		break;
	}
	case GameObject::GO_WALL:
	{
		m1 = go1->mass;
		m2 = go2->mass;
		Vector3 u = go1->vel;
		Vector3 N = go2->normal;
		Vector3 uN = u.Dot(N) * N;
		go1->vel = u - 2 * uN;
		go2->active = false;
		m_objectCount -= 1;
		obstacleCount -= 1;
		break;
	}
	}
}

void SceneAI::Update(double dt)
{
	SceneBase::Update(dt);

    //Entity Update
    Entity_Manager->Update(dt);

    //if (Application::IsKeyPressed('X'))
    //{
    //    warrior->WarriorSM.SetState("Knocking Back");
    //}
}


void SceneAI::RenderGO(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_BALL:
	{	//Exercise 4: render a sphere using scale and pos
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
	case GameObject::GO_WALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		float angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		modelStack.Rotate(angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BORDER], false);
		modelStack.PopMatrix();
	}
	}
}

void SceneAI::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

    RenderEntity();
	RenderRestaurant();
    RenderEntityInfo();
    RenderMessageHistory();
}

void SceneAI::RenderEntity()
{
    
    for (vector<BaseEntity*>::iterator it = Entity_Manager->EntityList.begin(); it != Entity_Manager->EntityList.end(); ++it)
    {
        modelStack.PushMatrix();
        if ((*it)->GetName() == "Chef")
        {
            Vector3 temp = (*it)->GetPosition();
            modelStack.Translate(temp.x, temp.y, temp.z);
            modelStack.Scale((*it)->GetScale(), (*it)->GetScale(), (*it)->GetScale());
            RenderMesh(meshList[GEO_RANGER], false);
            

        }
        else if ((*it)->GetName() == "Waiter")
        {
            Vector3 temp = (*it)->GetPosition();
            modelStack.Translate(temp.x, temp.y, temp.z);
            modelStack.Scale((*it)->GetScale(), (*it)->GetScale(), (*it)->GetScale());
            RenderMesh(meshList[GEO_HEALER], false);
        }
		else if ((*it)->GetName() == "Customer")
        {
			Vector3 temp = (*it)->GetPosition();
			modelStack.Translate(temp.x, temp.y, temp.z);
			modelStack.Scale((*it)->GetScale(), (*it)->GetScale(), (*it)->GetScale());
			RenderMesh(meshList[GEO_WARRIOR], false);
        }
		else
		{
			Vector3 temp = (*it)->GetPosition();
			modelStack.Translate(temp.x, temp.y, temp.z);
			modelStack.Scale((*it)->GetScale(), (*it)->GetScale(), (*it)->GetScale());
			RenderMesh(meshList[GEO_MOB], false);
		}
        modelStack.PopMatrix();
    }
    
}

void SceneAI::Insert_Text_On_Screen(float x, float y, float size, Color colour, string text)
{
    modelStack.PushMatrix();
    Mtx44 projection;
    projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
    RenderTextOnScreen(meshList[GEO_TEXT], text, colour, size, x, y, projection);
    modelStack.PopMatrix();
}

void SceneAI::RenderEntityInfo()
{
#define OFFSET 5.f 
    //renderBorder
    modelStack.PushMatrix();
    modelStack.Translate((m_worldWidth * 0.5f),(m_worldHeight * 0.25f),0);
    modelStack.Scale(m_worldWidth, 1, 1);
    RenderMesh(meshList[GEO_BORDER], false);
    modelStack.PopMatrix();
    for (vector<BaseEntity*>::iterator it = Entity_Manager->EntityList.begin(); it != Entity_Manager->EntityList.end(); ++it)
    {
        modelStack.PushMatrix();
        if ((*it)->GetName() == "Chef")
        {
            Chef* chef = dynamic_cast<Chef*>((*it));
            Insert_Text_On_Screen(chef->GetPosition().x - 2.f, chef->GetPosition().y - 5.f, 2.f, Color(1.f, 1.f, 1.f), chef->getState());
        }
        else if ((*it)->GetName() == "Waiter")
        {
            Waiter* waiter = dynamic_cast<Waiter*>((*it));
            Insert_Text_On_Screen(waiter->GetPosition().x - 2.f, waiter->GetPosition().y - 5.f, 2.f, Color(1.f, 1.f, 1.f), waiter->getState());
        }
		else if ((*it)->GetName() == "Customer")
		{
			Customer* customer = dynamic_cast<Customer*>((*it));
			Insert_Text_On_Screen(customer->GetPosition().x - 2.f, customer->GetPosition().y - 5.f, 2.f, Color(1.f, 1.f, 1.f), customer->getState());
		}

        modelStack.PopMatrix();
    }

    
}

void SceneAI::RenderRestaurant()
{
	// Restaurant Entrance
	modelStack.PushMatrix();
	modelStack.Translate((m_worldWidth * 0.75f), (m_worldHeight * 0.75f), 0);
	modelStack.Scale(1, (m_worldHeight * 0.5f), 1);
	RenderMesh(meshList[GEO_RESTAURANT_WALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate((m_worldWidth * 0.75f), (m_worldHeight * 0.333f), 0);
	modelStack.Scale(1, (m_worldHeight * 0.155f), 1);
	RenderMesh(meshList[GEO_RESTAURANT_WALL], false);
	modelStack.PopMatrix();

	// Counter & Kitchen
	modelStack.PushMatrix();
	modelStack.Translate((m_worldWidth * 0.65f), (m_worldHeight * 0.333f), 0);
	modelStack.Scale(1, (m_worldHeight * 0.155f), 1);
	RenderMesh(meshList[GEO_RESTAURANT_WALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate((m_worldWidth * 0.35f), 40.55, 0);
	modelStack.Scale((m_worldWidth * 0.8), 1, 1);
	RenderMesh(meshList[GEO_RESTAURANT_WALL], false);
	modelStack.PopMatrix();

	// Tables
	for (int i = 0; i < 4; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((m_worldWidth * 0.1f + i * 30), 60, 0);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_TABLE], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate((m_worldWidth * 0.1f + i * 30), 80, 0);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[GEO_TABLE], false);
		modelStack.PopMatrix();
	}
}

void SceneAI::RenderMessageHistory()
{
    if (MessageBoard::GetInstance()->MessageHistory.size() == 0)
        return;
    
    for (int i = 0; i < MessageBoard::GetInstance()->MessageHistory.size(); i++)
    {
        /*modelStack.PushMatrix();
        modelStack.Translate
        modelStack.PopMatrix();*/
        Insert_Text_On_Screen(m_worldWidth * 0.1f, m_worldHeight * (0.05 + 0.025 * i), 3.f, Color(1.f, 1.f, 1.f), MessageBoard::GetInstance()->MessageHistory[i]);
    }
    
}

void SceneAI::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if (m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}
