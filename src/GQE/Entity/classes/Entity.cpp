#include "GQE/Entity/classes/Entity.hpp"
namespace GQE
{

	Entity::Entity()
	{
	}
	Entity::~Entity()
	{
		std::map<std::string,AProperty*>::iterator anProptertyIter;
		std::map<std::string,IComponent*>::iterator anComponentIter;
		AProperty* anProperty;
		IComponent* anComponent;
		for(anProptertyIter=mPropertyList.begin(); anProptertyIter!=mPropertyList.end(); ++anProptertyIter)
		{
			anProperty=(anProptertyIter->second);
			delete anProperty;
			anProperty=NULL;
		}
		for(anComponentIter=mComponentList.begin(); anComponentIter!=mComponentList.end(); ++anComponentIter)
		{
			anComponent=(anComponentIter->second);
			anComponent->DeInit();
			anComponent->HandleCleanup();
			delete anComponent;
			anComponent=NULL;
		}
	}
	void Entity::AttachComponent(IComponent* theComponent)
	{
		if(theComponent==NULL)
			return;
		if(theComponent->GetID()=="")
			return;
		if(mComponentList.find(theComponent->GetID())!=mComponentList.end())
		{
			//log error
			return;
		}
		mComponentList[theComponent->GetID()]=theComponent;
		theComponent->DoInit(this);
	}
	void Entity::DetachComponent(typeComponentID theComponetID)
	{
		if(theComponetID=="")
			return;
		if(mComponentList.find(theComponetID)==mComponentList.end())
			return;
		IComponent* anComponent=mComponentList[theComponetID];
		anComponent->DeInit();
	}
	void Entity::HandleEvents(sf::Event theEvent)
	{
		IComponent* anComponent;
		std::map<std::string,IComponent*>::iterator anComponentIter;
		for(anComponentIter=mComponentList.begin(); anComponentIter!=mComponentList.end(); ++anComponentIter)
		{
			anComponent=anComponentIter->second;
			anComponent->HandleEvents(theEvent);
		}
	}
	void Entity::UpdateFixed()
	{
		IComponent* anComponent;
		std::map<std::string,IComponent*>::iterator anComponentIter;
		for(anComponentIter=mComponentList.begin(); anComponentIter!=mComponentList.end(); ++anComponentIter)
		{
			anComponent=anComponentIter->second;
			anComponent->UpdateFixed();
		}
	}

	void Entity::UpdateVariable(float theElapstedTime)
	{
		IComponent* anComponent;
		std::map<std::string,IComponent*>::iterator anComponentIter;
		for(anComponentIter=mComponentList.begin(); anComponentIter!=mComponentList.end(); ++anComponentIter)
		{
			anComponent=anComponentIter->second;
			anComponent->UpdateVariable(theElapstedTime);
		}
	}
	void Entity::Draw()
	{
		IComponent* anComponent;
		std::map<std::string,IComponent*>::iterator anComponentIter;
		for(anComponentIter=mComponentList.begin(); anComponentIter!=mComponentList.end(); ++anComponentIter)
		{
			anComponent=anComponentIter->second;
			anComponent->Draw();
		}
	}
	void Entity::HandleCleanup()
	{
		IComponent* anComponent;
		std::map<std::string,IComponent*>::iterator anComponentIter;
		for(anComponentIter=mComponentList.begin(); anComponentIter!=mComponentList.end(); ++anComponentIter)
		{
			anComponent=anComponentIter->second;
			anComponent->HandleCleanup();
			if(anComponent->CanRemove())
			{
				mComponentList.erase(anComponentIter);
				delete anComponent;
				anComponent=NULL;
			}
		}
	}
}