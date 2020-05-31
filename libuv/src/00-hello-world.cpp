#include <iostream>
#include <vector>
#include <cstdio> // Necesario para `fileno()`. ¡No es std!
#include <uv.h>

namespace uv {
    /**
     * Loop de eventos principal
     */ 
    class Loop {
    public:
        /**
         * Inicia loop de eventos
         */
        Loop() {
            uv_loop_init(&loop);
        }
        /**
         * Cierra loop de eventos
         */
        ~Loop() {
            uv_loop_close(&loop);
        }
        /**
         * Comienza el loop de eventos. En modo default corre hasta que no quedan más "handles" abiertos
         **/
        void run() {
            uv_run(&loop, UV_RUN_DEFAULT);
        }
        /**
         * Ehm...
         */
        uv_loop_t* getUvLoop() {
            return &this->loop;
        }
    private:
        uv_loop_t loop;
    };

    /**
     * Flujo de datos
     */
    class Pipe {
    public:
        Pipe(Loop& loop, int fd) : fd(fd) {
            uv_pipe_init(loop.getUvLoop(), &this->pipe, false); // Asocio al loop
            this->pipe.data = this; // El handler tiene la dirección de this.
            uv_pipe_open(&this->pipe, fd);
        }

        Pipe(Loop& loop, FILE* file) : Pipe(loop, fileno(file)){}

    /**
     * No quiero que sea copiable
     **/
        Pipe(const Pipe& pipe) = delete;

    /**
     * Tampoco movible, porque `pipe.data` tiene una referencia a `this`
     **/
        Pipe(Pipe&& pipe) = delete;

        ~Pipe() {
            uv_close((uv_handle_t*)&pipe, NULL);
        }

        void read() {
            uv_read_start((uv_stream_t*)&pipe,
            &Pipe::staticBufferAllocCallback,
            &Pipe::staticReadCallback);
        }
    private:
        /**
         * Callback que se llama cuando comienza a leer un stream.
         * Reserva memoria en *uvBuf que debe ser liberada por readCallback
         */
        static void staticBufferAllocCallback(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* uvBuf) {
            Pipe* self = (Pipe*) handle->data;
            self->bufferAllocCallback(suggestedSize, uvBuf);
        };

        static void staticReadCallback(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
            Pipe* self = (Pipe*) stream->data;
            self->readCallback(nread);
        };

        /**
         *  Agrando un buffer RAII que ya tengo. Podría usar un pool de memoria por ejemplo
         **/
        void bufferAllocCallback(size_t suggestedSize, uv_buf_t* uvBuf) {
            std::cout << std::endl << "Se llamó a \033[33;1mbufferAlloc\033[0m, sugiere reservar: " << suggestedSize << std::endl;
            this->buf.resize(suggestedSize);
            *uvBuf = uv_buf_init(this->buf.data(), suggestedSize);
        };

        /**
         * Se produjo una lectura de nread bytes. Si bien estos bytes los tengo en uv_buf_t*, uso mi buffer.
         **/
        void readCallback(ssize_t nread) {
            std::cout << "Se llamó a \033[33;1mreadCallback\033[0m" << std::endl;
            if (nread > 0) {
                std::cout << "Lei " << nread << " bytes en el stream:" << std::endl;
                for (ssize_t i = 0; i < nread; ++i) {
                    std::cout << buf[i];
                }
                std::cout << std::endl;
            } else if (nread < 0) {
                std::cout << "nread < 0, el pipe fue cerrado" << std::endl;
            }
        };
        uv_pipe_t pipe;
        int fd;
        std::vector<char> buf;
    };
};

int main(int argc, char** argv) {
    uv::Loop loop;
    uv::Pipe stdinPipe(loop, stdin);
    stdinPipe.read();
    loop.run();
}
