// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

//就像是SphereComp天生自带一个OnComponentHit事件
//这里是去设置一个叫做OnHealtgChanged的事件，具体的语法参考OnComponentHit的签名即可
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


//FOnHealtChanged就是这个Delegate的类型，这个宏自定义声明了这个类，记得将这个添加到成员内
//随后在cpp里面，希望将某个情景记作该事件发生，在对应的函数内触发 OnHealtChangedHit.broatcast(xxx..),记得传入你前面预留设计好的需要的参数
//随后可以在别的蓝图里，希望该事件发生时做些什么，就参考oncomponenthit的使用方法去定义和绑定行为就好啦

//补充：出自教程lecture7
//目的是ui自动读取血量，可以在widget里面基于tick去做，但那样开销太离谱，实际只需要在血量变化事件发生时更新即可
//教程采用了蓝图实现，详情见ui的widget
//实际上做法是
// widget蓝图 -> event construct事件（相当于在被add到viewport时激活 -> 拿到对应的player，拿到对应的pawn，从而拿到目标attributecomp -> bind event to on health changed（但是注意，必须用assign，否则bind节点不会提供实际的事件）
//自此，当attributecomp中healtchange事件被广播时，所有assign的蓝图（例如widget内），其onhealthchanged事件都会被触发



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	USAttributeComponent();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Health;
	
	UFUNCTION(BlueprintCallable)
	bool UpdateHealth(int delta);
	
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
	
	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnHealthChanged OnHealthChanged;//具体的成员，UPROPERTY设置参考oncomponenthit


	static USAttributeComponent* GetAttribute(AActor* AActor);

	AActor* InstigatorActor;
protected:
	
};
