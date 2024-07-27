//
// Created by ZZK on 2024/7/27.
//

#pragma once

#include <cstddef>
#include <memory>
#include <cstdint>
#include <utility>
#include <vector>
#include <mutex>
#include <concepts>

#if !defined (_WIN32) || !defined(_WIN64)
#error "Requires windows platform"
#else
#include <corecrt_malloc.h>
#endif

namespace util::details
{
    struct NullMutex
    {
        void lock() const {}
        void unlock() const {}
    };

    template <typename Mutex>
    concept MutexConcept = requires (Mutex mutex)
    {
        { mutex.lock() }   -> std::same_as<void>;
        { mutex.unlock() } -> std::same_as<void>;
    };

    inline void* memalign_alloc(size_t alignment, size_t size)
    {
        return _aligned_malloc(size, alignment);
    }

    inline void memalign_free(void *ptr)
    {
        _aligned_free(ptr);
    }

    template <typename T>
    struct ObjectPool
    {
    protected:
        virtual ~ObjectPool() = default;

        template <typename ... Args>
        T* construct_at_impl(Args&& ... args)
        {
            if (m_vacants.empty())
            {
                uint32_t num_objects = 16u << m_memory.size();
                T* ptr = static_cast<T *>(memalign_alloc(std::max<size_t>(64, alignof(T)),
                                                        num_objects * sizeof(T)));

                if (!ptr) return nullptr;

                for (uint32_t i = 0; i < num_objects; ++i)
                {
                    m_vacants.push_back(&ptr[i]);
                }

                m_memory.emplace_back(ptr);
            }

            T* ptr = m_vacants.back();
            m_vacants.pop_back();
            new (ptr) T(std::forward<Args>(args)...);
            return ptr;
        }

        void destroy_at_impl(T *ptr)
        {
            ptr->~T();
            m_vacants.push_back(ptr);
        }

        void deallocate_impl()
        {
            m_vacants.clear();
            m_memory.clear();
        }

    private:
        std::vector<T *> m_vacants;
        struct AlignedMallocDeleter
        {
            void operator()(T* ptr) const
            {
                memalign_free(ptr);
            }
        };
        std::vector<std::unique_ptr<T, AlignedMallocDeleter>> m_memory;
    };

    template <typename T, MutexConcept Mutex>
    struct CustomizedObjectPool : ObjectPool<T>
    {
    public:
        ~CustomizedObjectPool() override = default;

        template <typename ... Args>
        T* construct_at(Args&& ... args)
        {
            std::lock_guard<Mutex> lock_guard{ m_mutex };
            return ObjectPool<T>::construct_at_impl(std::forward<Args>(args)...);
        }

        void destroy_at(T* ptr)
        {
            std::lock_guard<Mutex> lock_guard{ m_mutex };
            ObjectPool<T>::destroy_at_impl(ptr);
        }

        void deallocate()
        {
            std::lock_guard<Mutex> lock_guard{ m_mutex };
            ObjectPool<T>::deallocate_impl();
        }

    private:
        Mutex m_mutex;
    };
}

namespace util
{
    template <typename T>
    using ThreadSafeObjectPool = details::CustomizedObjectPool<T, std::mutex>;

    template <typename T>
    using UnsafeObjectPool = details::CustomizedObjectPool<T, details::NullMutex>;
}
