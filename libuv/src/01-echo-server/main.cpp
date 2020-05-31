#include <iostream>
#include <vector>
#include <cstdio> // Necesario para `fileno()`. ¡No es std!
#include <uv.h>
#include "loop.h"

constexpr int PORT = 1;
constexpr int BACKLOG = 10;

namespace uv {
    /**
     * Clase que representa a un cliente conectado por un socket tcp
     **/
    class TcpClient {
    public:
        TcpClient(Loop& loop) {
            this->client.data = this;
            uv_tcp_init(&loop.loop, &this->client);
        }

        TcpClient(const TcpClient& client) = delete;

        TcpClient(TcpClient&& other) = delete;

        ~TcpClient(){
            uv_close((uv_handle_t*)&this->client, NULL);
        }
        
        /**
         * Acá se comporta igual que un pipe del ejemplo anterior
         **/
        void startRead() {
            uv_read_start((uv_stream_t*)&this->client,
                &TcpClient::staticBufferAllocCallback,
                &TcpClient::staticReadCallback);
        }
    private:
        static void staticBufferAllocCallback(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* uvBuf) {
            TcpClient* self = (TcpClient*) handle->data;
            self->bufferAllocCallback(suggestedSize, uvBuf);
        };

        static void staticReadCallback(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
            TcpClient* self = (TcpClient*) stream->data;
            self->readCallback(nread);
        };

        void bufferAllocCallback(size_t suggestedSize, uv_buf_t* uvBuf) {
            this->buf.resize(suggestedSize);
            *uvBuf = uv_buf_init(this->buf.data(), suggestedSize);
        };

        /**
         * Se produjo una lectura de nread bytes. Si bien estos bytes los tengo en uv_buf_t*, uso mi buffer.
         **/
        void readCallback(ssize_t nread) {
            std::cout << "Se llamó a \033[33;1mreadCallback\033[0m" << std::endl;
            if (nread > 0) {
                for (ssize_t i = 0; i < nread; ++i) {
                    std::cout << buf[i];
                }
                std::cout << std::endl;
            } else if (nread < 0) {
                std::cout << "nread < 0, el pipe fue cerrado" << std::endl;
            }
        };
        std::vector<char> buf;
        uv_tcp_t client;
        friend class TcpServer;
    };

    class TcpServer {
    public:
        /**
         * Clase que representa a un servidor TCP
         **/
        TcpServer(Loop& loop, const char* mask, int port) : loop(loop) {
            this->server.data = this;
            uv_tcp_init(&loop.loop, &this->server);
            uv_ip4_addr(mask, port, &bind_addr);
            int err = uv_tcp_bind(&server, (const struct sockaddr*) &bind_addr, 0);
            if (err) {
                std::cerr << "Error en bind: " << uv_strerror(err) << std::endl;
            }
            uv_listen((uv_stream_t*) &server, BACKLOG, &TcpServer::staticOnNewConnection);
        }

        ~TcpServer() {
            for (auto tcpClient : this->clientList) {
                delete tcpClient;
            }
        }
    private:
        uv_tcp_t server;
        struct sockaddr_in bind_addr;
        std::vector<TcpClient*> clientList;
        Loop& loop;

        static void staticOnNewConnection(uv_stream_t *server, int status) {
            TcpServer* self = (TcpServer*) server->data;
            self->onNewConnection(status);
        }

        void onNewConnection(int status) {
            std::cout << "Se llamó a \033[33;1monNewConnection\033[0m" << std::endl;
            if (status == -1) {
                return;
            }
            TcpClient* client = new TcpClient(this->loop);
            if (uv_accept((uv_stream_t*) &this->server, (uv_stream_t*) &client->client) == 0) {
                this->clientList.push_back(client);
                client->startRead();
            } else {
                std::cerr << "Error al aceptar" << std::endl;
            }
        }
    };
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    uv::Loop loop;
    std::cout << "connect "  << std::stoi(argv[PORT]) << std::endl;
    uv::TcpServer server(loop, "0.0.0.0", std::stoi(argv[PORT]));
    loop.run();
}
