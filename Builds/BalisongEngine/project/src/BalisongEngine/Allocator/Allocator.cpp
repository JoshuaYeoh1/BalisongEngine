#include "Allocator.h"
using namespace BalisongEngine;
using namespace BalisongEngineAllocator;

using namespace std;

// ===============================================================================

// initialize static collection
std::unordered_map<ResourceType, std::unordered_map<std::string, BaseResource*>> Allocator::resources;

// ===============================================================================

void Allocator::ReleaseUnusedResources(ResourceType resource_type)
{
    auto& resource_map = resources[resource_type];

    // Iterate the collection, for each AllocatedResource element
    for (auto it = resource_map.begin(); it != resource_map.end(); )
    {
        // If element refCount is 0
        if (it->second->GetRefCount() == 0)
        {
            // Delete the resource
            cout << "[Allocator] " << "Deleted resource: " << it->first << endl;
            delete it->second;
            // Remove element from collection
            it = resource_map.erase(it);
        }
        else it++;
    }
}

// ===============================================================================

void Allocator::ReleaseAllUnusedResources()
{
    for (auto it = resources.begin(); it != resources.end(); ++it)
    {
        auto& type = it->first;
        auto& resource_map = it->second;

        ReleaseUnusedResources(type);
    }
}

// ===============================================================================

void Allocator::PrintResourceUsage()
{
    for (auto it = resources.begin(); it != resources.end(); ++it)
    {
        auto& resource_type = it->first;
        auto& resource_map = it->second;

        for (auto it = resource_map.begin(); it != resource_map.end(); ++it)
        {
            auto& path = it->first;
            auto& resource = it->second;

            cout << "[Allocator] Resource path: " << path
                << " | type: " << static_cast<int>(resource_type)
                << " | refCount: " << resource->GetRefCount() << endl;
        }
    }
}