#pragma once

#include <memory>
namespace Tools {

template <class T>
class Singleton {
public:
    /**
     * @brief 返回单例裸指针
     */
    static T *GetInstance() {
        static T v;
        return &v;
    }
};

/**
 * @brief 单例模式智能指针封装类
 * @details T 类型
 *
 */
template <class T>
class SingletonPtr {
public:
    /**
     * @brief 返回单例智能指针
     */
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v(new T);
        return v;
    }
};

}  // namespace Tools