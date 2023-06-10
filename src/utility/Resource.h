//
// Created by wirewhiz on 6/7/23.
//

#ifndef BRANESCRIPT_RESOURCEHANDLE_H
#define BRANESCRIPT_RESOURCEHANDLE_H

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <cassert>

template<typename T>
class ResourceHandle;

/***
 * A resource that can be loaded and unloaded. This is used to track resources and determine if they are still in use and if it's safe to unload them.
 * It will also throw errors if a resource is unloaded while still in use.
 * @tparam T
 */
template<typename T>
class Resource
{
    std::unique_ptr<T> _data;
    size_t _refCount = 0;
    friend class ResourceHandle<T>;
  public:
    Resource(std::unique_ptr<T> data) : _data(std::move(data)) {}
    Resource(const Resource<T>&) = delete;
    Resource(Resource<T>&& o)
    {
        if(_refCount != 0)
            throw std::runtime_error("Resource was moved while referenced!");
        _data = std::move(o._data);
    }
    ~Resource()
    {
        if(_refCount != 0)
            throw std::runtime_error("Resource destroyed while still in use!");
    }
    typename std::add_lvalue_reference<T>::type operator*() noexcept
    {
        assert(_data);
        return *_data;
    }
    T* operator->() const noexcept
    {
        assert(_data);
        return _data.get();
    }
    bool isUsed() const noexcept
    {
        return _refCount != 0;
    }
};

/***
 * A handle to a resource. This is used to track uses of resources and determine if they are still in use and if it's safe to unload them.
 * @tparam T
 */
template<typename T>
class ResourceHandle
{
    Resource<T>* resource;
  public:
    ResourceHandle(Resource<T>& resource) : resource(&resource)
    {
        resource._refCount++;
    }
    ResourceHandle(const ResourceHandle<T>& other) : resource(other.resource)
    {
        resource->_refCount++;
    }
    ResourceHandle(ResourceHandle<T>&& other) noexcept : resource(other.resource)
    {
        other.resource = nullptr;
    }
    ~ResourceHandle()
    {
        if(resource)
            resource->_refCount--;
    }

    typename std::add_lvalue_reference<T>::type operator*() noexcept
    {
        assert(resource);
        return **resource;
    }
    T* operator->() const noexcept
    {
        assert(resource);
        return &**resource;
    }
    T* get()
    {
        if(!resource)
            return nullptr;
        return &**resource;
    }
    void release()
    {
        if(resource)
        {
            resource->_refCount--;
            resource = nullptr;
        }
    }
};



#endif // BRANESCRIPT_RESOURCEHANDLE_H
