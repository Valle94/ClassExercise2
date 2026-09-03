// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize with safe values
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	TimeSinceLastHeal = 0.f;
	RegenAmount = 1;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Ensure CurrentHealth doesn't exceed MaxHealth at start
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastHeal += DeltaTime;

	Regen(RegenAmount);
}

void UHealthComponent::ApplyDamage(int damage)
{
	if (damage <= 0)
	{
		return; // Don't apply negative or zero damage
	}

	CurrentHealth = FMath::Max(0, CurrentHealth - damage);
	UE_LOG(LogTemp, Display, TEXT("Player took %d damage!"), damage);
	UE_LOG(LogTemp, Display, TEXT("Current Health: %d"), CurrentHealth);
	UE_LOG(LogTemp, Display, TEXT("%d"), IsDead());
}

void UHealthComponent::Heal(int heal)
{
	if (heal <= 0)
	{
		return; // Don't apply negative or zero healing
	}

	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + heal);
	UE_LOG(LogTemp, Display, TEXT("Player healed %d hitpoints!"), heal);
	UE_LOG(LogTemp, Display, TEXT("Current Health: %d"), CurrentHealth);
	UE_LOG(LogTemp, Display, TEXT("%d"), IsDead());
}

void UHealthComponent::Regen(int regen)
{
	if (TimeSinceLastHeal >= 0.5f and !IsDead() and (CurrentHealth < MaxHealth))
	{
		Heal(regen);
		TimeSinceLastHeal = 0.f;
	}
}

bool UHealthComponent::IsDead() const
{
	return CurrentHealth <= 0;
}