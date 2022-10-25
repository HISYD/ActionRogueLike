// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LibMesh  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LibMesh"));
	LibMesh -> SetupAttachment(BaseMesh);

	TargetPitch = 110.0f;
}

void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LibMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));

	
	//常用的Debug语法示例（注意字符串打印和log的区别
	UE_LOG(LogTemp, Log, TEXT("Chest Opend"));
	UE_LOG(LogTemp, Warning, TEXT("Name is %s | Time is %f"), *GetNameSafe(InstigatorPawn), GetWorld()->TimeSeconds);//似乎字符串属于特别要求得用指针的方式传入 
	FString CombinedString = FString::Printf(TEXT("Hit at time of %f"), GetWorld()->TimeSeconds);
	DrawDebugString(GetWorld(), GetActorLocation(), CombinedString);
}
