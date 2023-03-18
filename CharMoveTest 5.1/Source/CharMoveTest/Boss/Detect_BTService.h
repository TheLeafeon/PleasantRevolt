// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CharMoveTest/Boss/BossAIController.h"
//#include "CharMoveTest/TestCharacter.h" //�÷��̾ �����ϱ� ���ؼ� �ʿ�, Test�� �� ������ �÷��̾�� ����� ���Ϸ� �ٲ��� �ʿ� ����
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h" //����׿�
//#include "CharMoveTest/Boss/BossAI_NumericalControl.h" //��ȹ�ڰ� ��ġ ������ �� �ְ�
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
	float DetectRadius; //���� ������

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
