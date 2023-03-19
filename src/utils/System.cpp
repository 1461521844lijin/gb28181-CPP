/*
 * Copyright (c) 2016 The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/xia-chu/ZLMediaKit).
 *
 * Use of this source code is governed by MIT license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#if !defined(_WIN32)
#include <limits.h>
#include <sys/resource.h>
#include <sys/wait.h>
#if !defined(ANDROID)
#include <execinfo.h>
#endif//!defined(ANDROID)
#endif//!defined(_WIN32)

#include <cstdlib>
#include <csignal>
#include <map>
#include <iostream>

#include "glog/logging.h"
#include "System.h"

using namespace std;


#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

string System::execute(const string &cmd) {
    FILE *fPipe = NULL;
    fPipe = popen(cmd.data(), "r");
    if(!fPipe){
        return "";
    }
    string ret;
    char buff[1024] = {0};
    while(fgets(buff, sizeof(buff) - 1, fPipe)){
        ret.append(buff);
    }
    pclose(fPipe);
    return ret;
}



void System::startDaemon(bool &kill_parent_if_failed) {
    kill_parent_if_failed = true;
#ifndef _WIN32
    static pid_t pid;
    do {
        pid = fork();
        if (pid == -1) {
            LOG(WARNING) << "fork失败:"; 
            //休眠1秒再试
            sleep(1);
            continue;
        }

        if (pid == 0) {
            //子进程
            return;
        }

        //父进程,监视子进程是否退出
        LOG(WARNING) << "启动子进程:" << pid;
        signal(SIGINT, [](int) {
            LOG(WARNING) << "收到主动退出信号,关闭父进程与子进程";
            kill(pid, SIGINT);
            exit(0);
        });

        do {
            int status = 0;
            if (waitpid(pid, &status, 0) >= 0) {
                LOG(WARNING) << "子进程退出";
                //休眠3秒再启动子进程
                sleep(3);
                //重启子进程，如果子进程重启失败，那么不应该杀掉守护进程，这样守护进程可以一直尝试重启子进程
                kill_parent_if_failed = false;
                break;
            }
            LOG(WARNING) << "waitpid被中断:";
        } while (true);
    } while (true);
#endif // _WIN32
}

void System::systemSetup(){
#if !defined(_WIN32)
    struct rlimit rlim,rlim_new;
    if (getrlimit(RLIMIT_CORE, &rlim)==0) {
        rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
        if (setrlimit(RLIMIT_CORE, &rlim_new)!=0) {
            rlim_new.rlim_cur = rlim_new.rlim_max = rlim.rlim_max;
            setrlimit(RLIMIT_CORE, &rlim_new);
        }
        LOG(WARNING) << "core文件大小设置为:" << rlim_new.rlim_cur;
    }

    if (getrlimit(RLIMIT_NOFILE, &rlim)==0) {
        rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
        if (setrlimit(RLIMIT_NOFILE, &rlim_new)!=0) {
            rlim_new.rlim_cur = rlim_new.rlim_max = rlim.rlim_max;
            setrlimit(RLIMIT_NOFILE, &rlim_new);
        }
        LOG(WARNING) << "文件最大描述符个数设置为:" << rlim_new.rlim_cur;
    }

#ifndef ANDROID
    // signal(SIGSEGV, sig_crash);
    // signal(SIGABRT, sig_crash);
    //忽略挂起信号
    signal(SIGHUP, SIG_IGN);
#endif// ANDROID
#endif//!defined(_WIN32)
}

