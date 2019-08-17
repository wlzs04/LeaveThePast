#include "BattleManager.h"

UBattleManager* UBattleManager::battleManager = nullptr;

UBattleManager* UBattleManager::GetInstance()
{
	return battleManager;
}

void UBattleManager::Init()
{
	inBattle = false;
}

void UBattleManager::EnterBattle()
{
	inBattle = true;
}

void UBattleManager::EndBattle()
{
	inBattle = false;
}

bool UBattleManager::IsInBattle()
{
	return inBattle;
}
