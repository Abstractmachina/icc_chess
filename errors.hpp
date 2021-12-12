#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>

class Err_Base : public std::exception {
    protected:
        std::string m_msg = "(base error): ";
    public:
        Err_Base(const std::string& msg) noexcept : m_msg(msg) {}
        const char * what () const noexcept override { return m_msg.c_str(); }
};

class Err_InvalidInput : public Err_Base {
    private:
        std::string m_msg = "(Invalid input): ";
    public:
        using Err_Base::Err_Base;
};

class Err_IncorrectInputLength : public Err_Base {
    private:
        std::string m_msg = "(Incorrect input length): ";
    public:
        using Err_Base::Err_Base;
};

class Err_WrongPlayer : public Err_Base {
     private:
        std::string m_msg = "(Wrong Player): ";
    public:
        using Err_Base::Err_Base;
};

class Err_InvalidMove : public Err_Base {
    public:
        using Err_Base::Err_Base;
};

#endif