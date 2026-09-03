// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLASSEXERCISE2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Value for maximum health
	UPROPERTY(Category = "Health", EditAnywhere, BlueprintReadWrite)
	int MaxHealth;

	// Value for current health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int CurrentHealth;

	// Value for Regen Timer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float TimeSinceLastHeal;

	// Function to apply damage by subtracting from health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(int damage);

	// Function to restore health by adding healing
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(int heal);

	// Function to determine if alive or dead
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	bool IsDead() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
