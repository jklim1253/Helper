#pragma once
#include "Helper_define.h"

class HELPER_API NetworkNode {

};

class HELPER_API ClientNode : public NetworkNode {

};

class HELPER_API ServerNode : public NetworkNode {

};

class HELPER_API Session {
private :
    NetworkNode* host_;
    NetworkNode* remote_;
};

struct HELPER_API CompletionHandler {
    virtual ~CompletionHandler();
    virtual int execute() = 0;
};

struct HELPER_API DefaultCompletionHandler : public CompletionHandler {
    virtual int execute(); // do nothing.
};
extern DefaultCompletionHandler default_handler;

class NetworkHelperImpl;
class HELPER_API NetworkHelper {
    typedef unsigned char byte;
public :
    NetworkHelper();
    ~NetworkHelper();

    // for Client
    NetworkHelper& CreateClient();
    NetworkHelper& CreateClient(const std::tstring& addr, int port);

    NetworkHelper& Connect(CompletionHandler* const connected_handler = &default_handler);
    NetworkHelper& Connect(const std::tstring& addr, int port, CompletionHandler* const connected_handler = &default_handler);

    // for Server
    NetworkHelper& CreateServer();
    NetworkHelper& CreateServer(int port);

    NetworkHelper& run(int port, CompletionHandler* const request_handler = &default_handler);
    NetworkHelper& run(CompletionHandler* const request_handler = &default_handler);

    // Session associated 
    std::list<Session*> EnumSessions();

    // common recv/send
    void useSession(Session* session);
    void Send(const std::tstring& msg, CompletionHandler* const handler = &default_handler);
    void Send(Session* session, const std::tstring& msg, CompletionHandler* const handler = &default_handler);
    void Send(const byte* const& bytes, CompletionHandler* const handler = &default_handler);
    void Send(Session* session, const byte* const& bytes, CompletionHandler* const handler = &default_handler);

    void Receive(std::tstring& buffer, CompletionHandler* const handler = &default_handler);
    void Receive(Session* session, std::tstring& buffer, CompletionHandler* const handler = &default_handler);
    void Receive(byte* const& buffer, CompletionHandler* const handler = &default_handler);
    void Receive(Session* session, byte* const& buffer, CompletionHandler* const handler = &default_handler);

private :
    NetworkHelperImpl* impl;
};