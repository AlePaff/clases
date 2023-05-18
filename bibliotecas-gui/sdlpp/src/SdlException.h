#ifndef __SDL_EXCEPTION_H__
#define __SDL_EXCEPTION_H__
#include <string>
#include <exception>

class SdlException : public std::exception {
    char msg[256];
public:
    explicit SdlException(const char* description);
    virtual ~SdlException() noexcept = default;
    const char* what() const noexcept override;
};

#endif
