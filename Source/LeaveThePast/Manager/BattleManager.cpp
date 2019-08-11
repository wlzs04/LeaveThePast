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

void UBattleManager::StartBattle()
{
	inBattle = true;
}

void UBattleManager::StopBattle()
{
	inBattle = false;
}

bool UBattleManager::IsInBattle()
{
	return inBattle;
}
