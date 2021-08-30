#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"


class PickupComponent : public nc::Component {

public:
	void Create() override;
	virtual void Update() override;

	virtual void onCollisionEnter(const nc::Event& event);
	virtual void onCollisionExit(const nc::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed = 0;

private:
	std::list<nc::Actor*> contacts;

};