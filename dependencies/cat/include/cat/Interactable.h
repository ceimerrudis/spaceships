#pragma once
#include "cat/Game.h"
#include "cat/AdvancedMath.h"
#include <array>

namespace cat
{
using Function = void (*)(void*);
using FunctionData = void*;
	
enum class InteractableTypes {
  Button
}; 
	
class Interactable
{
public:
	Function callback;
	FunctionData callbackData;
	InteractableTypes type;
	
	Interactable(InteractableTypes type, Function callback, FunctionData callbackData);
};
}
