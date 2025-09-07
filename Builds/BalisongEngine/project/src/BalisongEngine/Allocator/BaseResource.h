#pragma once

namespace BalisongEngine{
namespace BalisongEngineAllocator
{
    /// <summary>
    /// For choosing the resource type
    /// </summary>
    enum class ResourceType
    {
        TEXTURE,
        AUDIO,
        // Add more later
    };

    // ===============================================================================

    /// <summary>
    /// Keeps track of its resource type and ref counts, other resource classes inherit from it
    /// </summary>
    class BaseResource
    {
    public:

        /// <summary>
        /// Ctor
        /// </summary>
        /// <param name="type">enum ResourceType</param>
        BaseResource(ResourceType type);
        virtual ~BaseResource() = default;

        /// <summary>
        /// Gets current refCount
        /// </summary>
        /// <returns>int refCount</returns>
        int GetRefCount();
        /// <summary>
        /// Adds 1 to current refCount
        /// </summary>
        void IncrementRef();
        /// <summary>
        /// Removes 1 from current refCount
        /// </summary>
        void DecrementRef();

        /// <summary>
        /// Gets enum ResourceType
        /// </summary>
        /// <returns>enum ResourceType</returns>
        ResourceType GetResourceType();

    private:

        int refCount=0;
        ResourceType type;

    };

}
}