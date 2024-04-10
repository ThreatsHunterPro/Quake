#pragma once
#include "../../CoreMinimal.h"
#include "../Engine/Engine.h"
class RegisterActor
{
private:
	int currentid = -1;
	deque<int>idActors;
private:
	RegisterActor() =default;
	RegisterActor(RegisterActor&) = delete;
public:
	void Display()const;
	bool Contains(const int& _id);
	FORCEINLINE static RegisterActor& GetInstance() {
		static RegisterActor instance;
		return instance;
	}
	void Add(const int& _id);
	FORCEINLINE void SetCurrentActor(const int& _currentid) { currentid = _currentid; }
	FORCEINLINE int GetIdActor(const int& _id) const{ return idActors[_id]; }
	FORCEINLINE deque<int> GetAllActorInScene() const { return idActors; }
	FORCEINLINE size_t Count() const { return idActors.size(); }
	FORCEINLINE FVector GetActorPosition(const int& _id)  const { if (_id <= 0 || _id > Engine::GetInstance().GetAllActors()) return FVector(0); Engine::GetInstance().GetCubePosition(_id); }
	FORCEINLINE int GetCurrentActor()  const { return currentid; }
};

