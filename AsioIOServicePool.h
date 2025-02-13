#pragma once
#include <vector>
#include <boost/asio.hpp>
#include "Singleton.h"

using IOService = boost::asio::io_context;
using Work = boost::asio::io_context::work;
using WorkPtr = std::unique_ptr<Work>;

class AsioIOServicePool :public Singleton<AsioIOServicePool>
{
    friend Singleton<AsioIOServicePool>;
public:
    ~AsioIOServicePool();
    AsioIOServicePool(const AsioIOServicePool&) = delete;
    AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;
    // 使用 round-robin 的方式返回一个 io_service
    boost::asio::io_context& GetIOService();
    void Stop();
private:


    AsioIOServicePool(std::size_t size = 2/*std::thread::hardware_concurrency()*/);
    std::vector<IOService> _ioServices;
    std::vector<WorkPtr> _works;//避免服务监听套接字数目为0而自动跳出循环。
    std::vector<std::thread> _threads;
    std::size_t _nextIOService;
};

