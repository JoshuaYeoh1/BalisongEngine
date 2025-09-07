#pragma once
#include "BaseResource.h"
#include "Texture2D.h"
#include <string>
#include <unordered_map>
#include <iostream>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineAllocator
{
    /// <summary>
    /// If a resource file path is currently in use, it will reuse that
    /// </summary>
    class Allocator
    {
    public:

        /// <summary>
        /// Will try and see if the resource currently exist by checking the refCount, else it will create a new one
        /// </summary>
        /// <typeparam name="T">Template for classes that derives from BaseResource</typeparam>
        /// <param name="resource_type">An enum for the type of resource</param>
        /// <param name="resource_path">The file path of the resource</param>
        /// <returns></returns>
        template <
            typename T//,
            //typename std::enable_if<std::is_base_of<BaseResource, T>::value>::type = 0
        >
        static T* GetResource(ResourceType resource_type, const std::string& resource_path)
        {
            auto& resource_map = resources[resource_type];

            // Try find AllocatedResource object in collection using resourcePath
            auto it = resource_map.find(resource_path);
            // If found
            if (it != resource_map.end())
            {
                // Increase refCount by 1
                it->second->IncrementRef();
                // Print to console: Reusing resource: <resourcePath> :: refCount: <refCount>
                std::cout << "[Allocator] " << "Reused resource: " << resource_path << " :: refCount: " << it->second->GetRefCount() << std::endl;
                // Return the resource
                return static_cast<T*>(it->second);
            }

            // else if not found,
            // Try load resource
            T* new_resource = CreateResource<T>(resource_type, resource_path);
            // If successful
            if (new_resource)
            {
                // Create AllocatedResource object with the resource
                resource_map[resource_path] = new_resource;
                // Increase refCount by 1
                // Add the object to the collection
                std::cout << "[Allocator] " << "Loaded new resource: " << resource_path << " :: refCount: " << new_resource->GetRefCount() << std::endl;
                // Return the resource
                return new_resource;
            }

            // else return blank
            std::cout << "[Allocator] " << "Failed to load resource: " << resource_path << std::endl;
            return BlankResource<T>(resource_type);
        }

        // ===============================================================================

        /// <summary>
        /// When a resource is no longer in use, it will decrement the refCount if it's more than 0
        /// </summary>
        /// <typeparam name="T">Template for classes that derives from BaseResource</typeparam>
        /// <param name="resource">Any class that derives from BaseResource</param>
        template <
            typename T//,
            //typename std::enable_if<std::is_base_of<BaseResource, T>::value>::type = 0
        >
        static void ReturnResource(T* resource)
        {
            auto& resource_map = resources[resource->GetResourceType()];

            // get resourcePath from resource
            // Find the matching AllocatedResource object using resourcePath
            for (auto it = resource_map.begin(); it != resource_map.end(); ++it)
            {
                auto& path = it->first;
                auto& allocated = it->second;

                // If found
                if (allocated == resource)
                {
                    // If refCount is 0
                    if (allocated->GetRefCount() == 0)
                    {
                        // Print to console: <resourcePath> refCount is 0!
                        std::cout << "[Allocator] " << path << " refCount is already 0!" << std::endl;
                        break;
                    }

                    // Decrease the refCount
                    allocated->DecrementRef();

                    std::cout << "[Allocator] " << "Returned resource: " << path << " :: refCount: " << allocated->GetRefCount() << std::endl;
                }
            }
        }

        // ===============================================================================

        /// <summary>
        /// Checks all current resources of a specific type to remove those with a refCount of 0
        /// </summary>
        /// <param name="resource_type">An enum for the type of resource</param>
        static void ReleaseUnusedResources(ResourceType resource_type);

        /// <summary>
        /// Checks all current resources of all types to remove those with a refCount of 0
        /// </summary>
        static void ReleaseAllUnusedResources();

        // ===============================================================================
        
        /// <summary>
        /// Show a list of current resources being used
        /// </summary>
        static void PrintResourceUsage();

        // ===============================================================================

    private:

        template <typename T>
        static T* CreateResource(ResourceType type, const std::string& resource_path)
        {
            if (type == ResourceType::TEXTURE)
            {
                BalisongEngineRenderer::TextureConfig cfg;
                cfg.wrapModeX = BalisongEngineRenderer::TextureWrapMode::REPEAT;
                cfg.wrapModeY = BalisongEngineRenderer::TextureWrapMode::REPEAT;
                cfg.filterMode = BalisongEngineRenderer::TextureFilterMode::LINEAR;
                cfg.useMipmaps = false;
                return new BalisongEngineRenderer::Texture2D(resource_path, cfg);
            }
            return nullptr;
        }

        template <typename T>
        static T* BlankResource(ResourceType type)
        {
            if (type == ResourceType::TEXTURE)
            {
                return BalisongEngineRenderer::Texture2D::BlankTexture();
            }
            return nullptr;
        }

        // Dictionary of maps for each ResourceType enum
        static std::unordered_map<ResourceType, std::unordered_map<std::string, BaseResource*>> resources;
    };

}
}