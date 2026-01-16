/*
 * @Descripttion: 写个tcp 的server进程
 * @Author: jev
 * @Date: 2026-01-16
 */
#include <string>
#include <sys/socket.h>
#include <thread>
#include <vector>

struct TcpConfig {
    std::string ip;
    std::string port;
};

class TcpServer {
public:
    explicit TcpServer(const TcpConfig& cfg)
        : cfg_(cfg){};
    ~TcpServer() {}

    bool start();

    bool stop();

    bool send(const void * data) {
        return true;
    }

    void setCallback();

    private:
    void accept

private:
    TcpConfig cfg_;
    int socket_fd_{-1};  // socket 文件描述符
    std::vector<int> client_fds_;  // 接收到客户端的文件描述符列表（这里做多客户端连接的demo）
};
