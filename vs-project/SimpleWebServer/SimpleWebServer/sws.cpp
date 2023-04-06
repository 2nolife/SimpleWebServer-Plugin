#pragma once

#if defined _WIN64
    #define DLL_EXPORT __declspec(dllexport)
#endif
#ifndef DLL_EXPORT
    #define DLL_EXPORT
#endif

#include "sws.h"
#include "server_http.hpp"
#include <chrono>
#include <string>

using namespace std;
using namespace sws;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

string current_time() {
    const auto p1 = chrono::system_clock::now();
    const auto p2 = chrono::duration_cast<chrono::seconds>(p1.time_since_epoch()).count();
    return to_string(p2);
}

DLL_EXPORT SimpleWebServer::SimpleWebServer() {
    
}

DLL_EXPORT SimpleWebServer::~SimpleWebServer() {
    destroy_instance();
}

DLL_EXPORT void SimpleWebServer::create_instance() {
    server = new HttpServer();
}

DLL_EXPORT void SimpleWebServer::destroy_instance() {
    if (server != nullptr)
        delete server;
}

DLL_EXPORT void SimpleWebServer::start(int port) {
    auto* server2 = static_cast<HttpServer*>(server);
    server2->config.port = port;
    promise<unsigned short> server_port;
    server_thread = thread([&server2, &server_port]() {
        // Start server
        server2->start([&server_port](unsigned short port) {
            server_port.set_value(port);
        });
    });
    cout << "Server is listening on port " << server_port.get_future().get() << endl;
}

DLL_EXPORT void SimpleWebServer::stop() {
    auto* server2 = static_cast<HttpServer*>(server);
    server2->stop();
    cout << "Server stopped" << endl;
}

DLL_EXPORT void SimpleWebServer::add_default_routes() {
    auto* server2 = static_cast<HttpServer*>(server);

    // POST
    server2->resource["^/.*$"]["POST"] = [this](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        auto content = request->content.string();

        string reply = current_time();
        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << reply.length() << "\r\n\r\n" << reply;

        if (callback != nullptr)
            callback->on_post(request->path, content);
    };

    // GET
    server2->resource["^/.*$"]["GET"] = [this](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        map<string, string> query;
        auto query_fields = request->parse_query_string();
        for (auto& field : query_fields)
            query.insert({ field.first, field.second });

        response->write(current_time());

        if (callback != nullptr)
            callback->on_get(request->path, query);
    };

    server2->on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code& /*ec*/) {
        // Handle errors here
        // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
    };
}

DLL_EXPORT void Callback::on_post(string& path, string& content) {
    // override me
    cout << path << " on_post: " << content << endl;
}

DLL_EXPORT void Callback::on_get(string& path, map<string, string>& query) {
    // override me
    cout << path << " on_get: ";
    for (auto& field : query)
        cout << field.first << " = " << field.second << ", ";
    cout << endl;
}
