// Fill out your copyright notice in the Description page of Project Settings.

#include "Affixes.h"


void UAffix::Apply() { }

void UAffix::Cancel() { }

FText UAffix::GetText() {return FText::FromString("Asd");}


void UBasicAffix::Apply()
{

}

void UBasicAffix::Cancel()
{

}

FText UBasicAffix::GetText()
{
	return FText::FromString("Asd");
}

void UEquipAffix::Apply()
{

}

void UEquipAffix::Cancel()
{

}

FText UEquipAffix::GetText()
{
	return FText::FromString("Asd");
}

void UTriggerAffix::Apply()
{

}

void UTriggerAffix::Cancel()
{

}

FText UTriggerAffix::GetText()
{
	return FText::FromString("Asd");
}
