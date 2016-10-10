#include "NetworkHelper.h"

int DefaultCompletionHandler::execute() {
    return 0;
}

DefaultCompletionHandler default_handler;

CompletionHandler::~CompletionHandler() {}

class NetworkHelperImpl {

};

NetworkHelper::NetworkHelper() {

}
NetworkHelper::~NetworkHelper() {

}

// for Client
NetworkHelper& NetworkHelper::CreateClient() {
    return *this;
}
NetworkHelper& NetworkHelper::CreateClient(const std::tstring& addr, int port) {
    return *this;
}

NetworkHelper& NetworkHelper::Connect(CompletionHandler* const connected_handler/*=&default_handler*/) {
    return *this;
}
NetworkHelper& NetworkHelper::Connect(const std::tstring& addr, int port, CompletionHandler* const connected_handler/*=&default_handler*/) {
    return *this;
}

// for Server
NetworkHelper& NetworkHelper::CreateServer() {
    return *this;
}
NetworkHelper& NetworkHelper::CreateServer(int port) {
    return *this;
}

NetworkHelper& NetworkHelper::run(int port, CompletionHandler* const request_handler/*=&default_handler*/) {
    return *this;
}
NetworkHelper& NetworkHelper::run(CompletionHandler* const request_handler/*=&default_handler*/) {
    return *this;
}

// Session associated 
std::list<Session*> NetworkHelper::EnumSessions() {
    return std::list<Session*>();
}

// common recv/send
void NetworkHelper::useSession(Session* session) {

}
void NetworkHelper::Send(const std::tstring& msg, CompletionHandler* const handler/*=&default_handler*/) {

}
void NetworkHelper::Send(Session* session, const std::tstring& msg, CompletionHandler* const handler/*=&default_handler*/) {

}
void NetworkHelper::Send(const byte* const& bytes, CompletionHandler* const handler/*=&default_handler*/) {

}
void NetworkHelper::Send(Session* session, const byte* const& bytes, CompletionHandler* const handler/*=&default_handler*/) {

}

void NetworkHelper::Receive(std::tstring& buffer, CompletionHandler* const handler/*=&default_handler*/) {

}
void NetworkHelper::Receive(Session* session, std::tstring& buffer, CompletionHandler* const handler/*=&default_handler*/) {

}
void NetworkHelper::Receive(byte* const& buffer, CompletionHandler* const handler/*=&default_handler*/) {

}
void NetworkHelper::Receive(Session* session, byte* const& buffer, CompletionHandler* const handler/*=&default_handler*/) {

}

