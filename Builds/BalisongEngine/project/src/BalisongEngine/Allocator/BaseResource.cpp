#include "BaseResource.h"
using namespace BalisongEngine;
using namespace BalisongEngineAllocator;

// ====================================================================

BaseResource::BaseResource(ResourceType type) : refCount(1), type(type) {}

// ====================================================================

int BaseResource::GetRefCount()
{
	return refCount;
}
void BaseResource::IncrementRef()
{
	refCount++;
}
void BaseResource::DecrementRef()
{
	if (refCount > 0)
		refCount--;
}

// ====================================================================

ResourceType BaseResource::GetResourceType()
{
	return type;
}
