#ifndef UV_LOOP_H
#define UV_LOOP_H
#include <uv.h>

namespace uv {
    class TcpServer;
    class TcpClient;
    /**
     * Loop de eventos principal
     */ 
    class Loop {
    public:
        /**
         * Inicia loop de eventos
         */
        Loop();
        /**
         * Cierra loop de eventos
         */
        ~Loop();
        /**
         * Comienza el loop de eventos.
         * En modo default corre hasta que no quedan más "handles" abiertos
         **/
        void run();
    private:
        uv_loop_t loop;
        friend class TcpServer;
        friend class TcpClient;
    };
}

#endif
