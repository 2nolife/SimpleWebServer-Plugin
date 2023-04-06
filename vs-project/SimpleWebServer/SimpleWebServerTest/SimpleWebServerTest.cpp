#include "../SimpleWebServer/sws.h"
#include "../SimpleWebServer/client_http.hpp"
#include "../SimpleWebServer/server_http.hpp"

using namespace std;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int main() {
    sws::SimpleWebServer server;
    server.create_instance();
    server.add_default_routes();
    server.start(8080);

    sws::Callback callback;
    server.callback = &callback;

    cout << endl;


    // CLIENT 
    
    HttpClient client("localhost:8080");

    try {
        cout << "Example GET request to http://localhost:8080/" << endl;
        auto r1 = client.request("GET", "/?cmd=foo&bar=baz");
        cout << "Response content: " << r1->content.rdbuf() << endl << endl;
    }
    catch (const SimpleWeb::system_error& e) {
        cerr << "Client request error: " << e.what() << endl << endl;
    }

    try {
        cout << "Example GET request to http://localhost:8080/get" << endl;
        auto r1 = client.request("GET", "/get?cmd=foo&bar=baz");
        cout << "Response content: " << r1->content.rdbuf() << endl << endl;
    }
    catch (const SimpleWeb::system_error& e) {
        cerr << "Client request error: " << e.what() << endl << endl;
    }

    try {
        cout << "Example POST request to http://localhost:8080/" << endl;
        string post_string = "The population of Antarctica is unknown!";
        auto r2 = client.request("POST", "/", post_string);
        cout << "Response content: " << r2->content.rdbuf() << endl << endl;
    }
    catch (const SimpleWeb::system_error& e) {
        cerr << "Client request error: " << e.what() << endl << endl;
    }

    try {
        cout << "Example POST request to http://localhost:8080/post" << endl;
        string post_string = "The population of Antarctica is unknown!";
        auto r2 = client.request("POST", "/post", post_string);
        cout << "Response content: " << r2->content.rdbuf() << endl << endl;
    }
    catch (const SimpleWeb::system_error& e) {
        cerr << "Client request error: " << e.what() << endl << endl;
    }


    server.stop();
    server.destroy_instance();

    system("pause");
}
