### 依赖zlm并使用cpp实现的gb28181的视频平台

#### 简单介绍

作为开源的新gb28181项目，很多地方才起步不太完善，假如真的如果有人用的话希望多多包涵，自己在开发过程中主要参考的还是wvp中的一些设计，自己再对照gb文档慢慢改进；项目后续会不定期的更新代码，希望这个项目慢慢完善。当然如有大佬感兴趣能参与进来一起开发，提一提issue或pr那就更好啦。

#### 依赖三方库

~~~sh
ZLTookit                # 使用了里面的日志、线程池、定时器等模块
oatpp&oatpp-swagger     # http服务和swagger文档模块
osip&exosip				# sip信令相关
~~~

#### 如何使用----安装依赖库
当前项目运行环境为linux，不支持直接在win下运行，仅支持gcc8版本以上的编译

~~~sh
#安装oatpp
git clone https://github.com/oatpp/oatpp.git
cd oatpp 
mkdir -p build 
cd build 
cmake -D BUILD_SHARED_LIBS=ON  ..
make -j4 
sudo make install
#安装oatpp-swagger
git clone https://github.com/oatpp/oatpp-swagger.git
cd oatpp-swagger 
mkdir -p build 
cd build 
cmake -D BUILD_SHARED_LIBS=ON ..
make -j4 
sudo make install
#安装osip
wget https://www.antisip.com/download/exosip2/libosip2-5.3.0.tar.gz
tar -zxvf libosip2-5.3.0.tar.gz
cd libosip2-5.3.0
./configure
 make
 sudo make install
#安装exosip
wget https://www.antisip.com/download/exosip2/libexosip2-5.3.0.tar.gz
tar -zxvf libexosip2-5.3.0.tar.gz
cd libexosip2-5.3.0
./configure
make
sudo make install

# 构建项目
mkdir build
cd build
cmake ..
make
~~~



#### 配置项

/config/dev_config.json文件中可以进行http服务配置、sip相关配置、和zlm相关配置

#### 查看swagger ui

http://{host}:{port}/swagger/ui#/

#### 已实现功能

- 国标摄像头接入、目录查询、推流
- ptz通用控制、预置位调用、看守位调用
- 部分zlm的webhook接口：推流/播放鉴权

#### 后续逐步实现的功能

- 国标平台级联
-  zlm的其他hook接口、zlm多节点负载均衡
- 