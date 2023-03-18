// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CharMoveTest/Boss/BossAIController.h"
//#include "CharMoveTest/TestCharacter.h" //플레이어를 감지하기 위해서 필요, Test인 것 같으니 플레이어로 사용할 파일로 바꿔줄 필요 있음
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h" //디버그용
//#include "CharMoveTest/Boss/BossAI_NumericalControl.h" //기획자가 수치 조절할 수 있게
#include "Detect_BTService.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UDetect_BTService : public UBTService
{
	GENERATED_BODY()
	
private:
	UDetect_BTService();

	UPROPERTY()
	float DetectRadius; //범위 반지름

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
