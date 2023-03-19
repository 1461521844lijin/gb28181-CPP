#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <queue>
#include <atomic>
#include <future>
#include <condition_variable>
#include <thread>
#include <functional>
#include <stdexcept>
#include <string.h>

#include <future>





using namespace std;
/*
*
* 公共工具函数文件，如，计算时间戳，
*
*/


inline double GetSpan(std::chrono::system_clock::time_point time1, std::chrono::system_clock::time_point time2) {
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1);
	return double(duration.count()) * std::chrono::microseconds::period::num /
		std::chrono::microseconds::period::den;
};


inline std::string Time2Str(time_t ts = time(0), const std::string& format = "%Y-%m-%d %H:%M:%S"){
        struct tm tm;
        localtime_r(&ts, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), format.c_str(), &tm);
        return buf;
    }

inline time_t Str2Time(const char* str, const char* format = "%Y-%m-%d %H:%M:%S"){
        struct tm t;
        memset(&t, 0, sizeof(t));
        if(!strptime(str, format, &t)) {
            return 0;
        }
        return mktime(&t);
    }


// 线程安全队列
template<class T>
class SList {

public:
	void Push(T& data) {
		unique_lock<mutex> lock(m_mutex);
		m_list.push_back(data);
		if (m_list.size() > max_number)
			m_list.pop_front();
	}

	bool Pop(T& data) {
		unique_lock<mutex> lock(m_mutex);
		if (m_list.size() == 0) return false;
		data = move(m_list.front());
		m_list.pop_front();
		return true;
	}

	void set_max_size(const int size) {
		unique_lock<mutex> lock(m_mutex);
		max_number = size;
	}

	int size() {
		return m_list.size();
	}

	void clear(){
		unique_lock<mutex> lock(m_mutex);
		m_list.clear();
	}


private:
	std::mutex m_mutex;

	list<T> m_list;

	int max_number = 25;

};

