/*
 * @Descripttion: 一个简单的tcp server进程，能够接受多个client
 * @Author: jev
 * @Date: 2026-01-16
 */
#include <algorithm>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>
struct TcpConfig {
    std::string ip;
    uint16_t port;
};

using MessageCallback = std::function<void(const std::string&)>;

class TcpServer {
public:
    explicit TcpServer(const TcpConfig& cfg)
        : cfg_(cfg){};
    ~TcpServer() { stop(); }

    // 启动TCP服务器
    void start() {
        // 如果服务器已经启动了，则直接返回
        if (is_runing_) {
            std::cout << "tcp server is already running" << std::endl;
            return;
        }

        // 1. 创建 socket fd
        // AF_INET : IPv4 Internet protocols
        // SOCK_STREAM: Provides  sequenced,  reliable,  two-way,  connection-based byte streams.
        listen_fd_ = ::socket(AF_INET, SOCK_STREAM, 0);

        // 2. 设置端口复用
        int opt = 1;
        setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

        // 3. 设置地址和地址族
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(cfg_.port);
        // 将 cfg_.ip 转换为 满足af 地址族结构的地址 addr.sin_addr
        inet_pton(AF_INET, cfg_.ip.c_str(), &addr.sin_addr);

        // 4. bind, 将特定地址分配给socket的文件描述符
        if (::bind(listen_fd_, (struct sockaddr*)&addr, sizeof(addr) < 0)) {
            perror("bind");
            ::close(listen_fd_);
            listen_fd_ = -1;
            return;
        }

        // 5. listen, 监听 socket fd 的连接事件，n表示候选连接列表的最大长度
        if (::listen(listen_fd_, 5) < 0) {
            perror("listen");
            ::close(listen_fd_);
            listen_fd_ = -1;
            return;
        }

        is_runing_.store(true);

        // 启动连接线程
        accept_thread_ = std::thread(&TcpServer::acceptThreadFunc, this);

        std::cout << "TCP Server started on " << cfg_.ip << ":" << cfg_.port << std::endl;
    }

    // 停止TCP服务器
    void stop() {
        if (!is_runing_) return;

        // 关闭 监听的 fd
        if (listen_fd_ >= 0) {
            ::close(listen_fd_);
            listen_fd_ = -1;
        }

        // 关闭所有客户端
        closeAllClient();

        // 等待线程结束
        if (accept_thread_.joinable()) { accept_thread_.join(); }

        for (auto& t : client_threads_) {
            if (t.joinable()) { t.join(); }
        }

        client_threads_.clear();
        client_fds_.clear();
    }

    // 发送信息
    bool send(const void* data) { return true; }

    // 设置回调，让它在接收到信息后触发回调
    void setCallback(MessageCallback cb) { recv_cb_ = cb; }

private:
    // 接受客户端线程
    void acceptThreadFunc() {
        while (is_runing_) {
            sockaddr_in client_addr{};
            socklen_t addr_len = sizeof(client_addr);
            int client_fd = ::accept(listen_fd_, (struct sockaddr*)&client_addr, &addr_len);

            if (client_fd < 0) {
                if (is_runing_) perror("accept");
                continue;
            }

            std::cout << "Client connected :" << client_fd << std::endl;
            client_fds_.push_back(client_fd);

            // 启动数据接受线程
            client_threads_.emplace_back(&TcpServer::recvThreadFunc, this, client_fd);
        }
    }

    // 接受消息线程
    void recvThreadFunc(int fd) {
        // 开辟缓冲区
        char buffer[1024];

        while (is_runing_) {
            ssize_t n = ::recv(fd, buffer, sizeof(buffer), 0);

            if (n <= 0) {
                if (n < 0) perror("recv");
                std::cout << "Client disconnected: " << fd << std::endl;
                ::close(fd);
                break;
            }

            std::string raw(buffer, n);

            if (recv_cb_) {
                try {
                    // 解析数据

                    // 利用回调处理数据
                    recv_cb_(raw);
                } catch (std::exception& e) {
                    std::cerr << "Failed to parse message: " << e.what() << std::endl;
                }
            }
        }

        // 移除客户端
        client_fds_.erase(std::remove(client_fds_.begin(), client_fds_.end(), fd),
                          client_fds_.end());
    }

    void closeAllClient() {
        for (int fd : client_fds_) { ::close(fd); }
        client_fds_.clear();
    }

private:
    TcpConfig cfg_;
    int listen_fd_{-1};  // socket 文件描述符
    std::vector<int> client_fds_;  // 接收到客户端的文件描述符列表（这里做多客户端连接的demo）
    std::vector<std::thread> client_threads_;
    std::thread accept_thread_;
    std::atomic<bool> is_runing_{false};
    MessageCallback recv_cb_;
};
