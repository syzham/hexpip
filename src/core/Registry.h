#ifndef HEXPIP_REGISTRY_H
#define HEXPIP_REGISTRY_H

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

using Entity = std::uint32_t;

class Registry
{
public:
    Entity create();
    void destroy(Entity id);
    void clear();

    template<typename T, typename... Args>
    T& emplace(Entity e, Args&&... args)
    {
        auto& store = storage<T>();
        return store.emplace(e, std::forward<Args>(args)...);
    }

    template<typename T>
    T& get(Entity e)
    {
        auto* s = storageIfExists<T>();
        if (!s) throw std::runtime_error("Registry::get - no storage for component type");
        auto it = s->data.find(e);
        if (it == s->data.end()) throw std::runtime_error("Registry::get - entity missing component");
        return it->second;
    }

    template<typename T, typename Func>
    void forEach(Func&& fn)
    {
        auto* s = storageIfExists<T>();
        if (!s) return;

        for (auto& [e, comp] : s->data)
            fn(e, comp);
    }

    template<typename C0, typename C1, typename... Rest, typename Func>
    void forEach(Func&& fn)
    {
        auto* s0 = storageIfExists<C0>();
        if (!s0) return;

        for (auto& [e, c0] : s0->data)
        {
            if (!has<C1>(e)) continue;
            if (!((has<Rest>(e)) && ...)) continue;

            fn(e, c0, get<C1>(e), get<Rest>(e)...);
        }
    }

    template<typename T>
    int count()
    {
        auto* s = storageIfExists<T>();
        if (!s) return 0;

        return s->data.size();
    }

    template<typename C0, typename C1, typename... Rest>
    int count()
    {
        auto* s0 = storageIfExists<C0>();
        if (!s0) return 0;

        int cnt = 0;

        for (auto& [e, c0] : s0->data)
        {
            if (!has<C1>(e)) continue;
            if (!((has<Rest>(e)) && ...)) continue;

            cnt++;
        }

        return cnt;
    }

    template<typename T>
    [[nodiscard]] bool has(Entity e) const
    {
        auto* s = storageIfExists<T>();
        if (!s) return false;
        return s->data.find(e) != s->data.end();
    }

private:
    struct IStorage
    {
      virtual ~IStorage() = default;
      virtual void erase(Entity e) = 0;
      [[nodiscard]] virtual bool contains(Entity e) const = 0;
    };

    template<typename T>
    struct Storage : IStorage
    {
      std::unordered_map<Entity, T> data;

      template<typename... Args>
      T& emplace(Entity e, Args&&... args)
      {
        auto [it, inserted] = data.emplace(e, T{std::forward<Args>(args)...});
        if (!inserted) it->second = T{std::forward<Args>(args)...};
        return it->second;
      }

      T& get(Entity e)
      {
        auto it = data.find(e);
        if (it == data.end())
          throw std::runtime_error("component not found for entity");
        return it->second;
      }

      void erase(Entity e) override { data.erase(e); }
      [[nodiscard]] bool contains(Entity e) const override { return data.contains(e); }
    };

    template<typename T>
    Storage<T>& storage()
    {
      auto key = std::type_index(typeid(T));
      const auto it = m_storages.find(key);
      if (it == m_storages.end())
      {
        auto ptr = std::make_unique<Storage<T>>();
        auto* raw = ptr.get();
        m_storages.emplace(key, std::move(ptr));
        return *raw;
      }
      return *static_cast<Storage<T>*>(it->second.get());
    }
private:
    Entity m_nextEntity{0};
    std::vector<Entity> m_freeList;

    std::unordered_map<std::type_index, std::unique_ptr<IStorage>> m_storages;

    template<typename T>
    Storage<T>* storageIfExists()
    {
        const auto key = std::type_index(typeid(T));
        const auto it = m_storages.find(key);
        if (it == m_storages.end()) return nullptr;
        return static_cast<Storage<T>*>(it->second.get());
    }

    template<typename T>
    const Storage<T>* storageIfExists() const
    {
        const auto key = std::type_index(typeid(T));
        const auto it = m_storages.find(key);
        if (it == m_storages.end()) return nullptr;
        return static_cast<const Storage<T>*>(it->second.get());
    }
};

#endif //HEXPIP_REGISTRY_H