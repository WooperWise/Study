#include <iostream>
#include <string>
#include "crow_all.h"
#include "Automat.hpp"
#include "threads.hpp"


#define crow_json crow::json::wvalue

using namespace std;

void prosessReuestSync(crow::websocket::connection& conn, const crow::json::rvalue& json){

    vector<vector<bool>> field = parseField(json["cellStates"], json["rows"].i(), json["columns"].i());

    Automat automat(field, json["filterType"].i());

    automat.setRules(parseRules(json["alive"]), parseRules(json["death"]));

    automat.prossesField(json["iterations"].i());

    vector<vector<bool>> grid = automat.getField();

    std::string gridString = "{\"cellStates\":{";
    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            gridString += "\"" + std::to_string(row) + "-" + std::to_string(col) + "\":" + (grid[row][col] ? "true" : "false") + ",";
        }
    }
    // Remove the trailing comma
    if (!gridString.empty()) {
        gridString.pop_back();
    }
    gridString += "}}";

    // Send the response back to the client
    conn.send_text(gridString);

}

int main()
{
    crow::SimpleApp app;

    //TSQueue< pair<crow::websocket::connection&, const std::string&> > queue;

    ThreadPool pool(4);

    CROW_ROUTE(app, "/").
        methods("POST"_method)([&](const crow::request& req) {

            cout << "Received message: " << data << endl;

            cout << "Received message: " << req.body << endl;

            crow::json::rvalue json = crow::json::load(req.body);

            if (!json){
                return false;
            }
            else if (json["rows"].i() == -1){
                return true;
            }
            else{

                //prosessReuestSync(conn, json);
                pool.process(req, json);
                //prosessReuestAsync(conn, data);

                // Return true to keep the WebSocket connection open
                return true;
            }

        });
            
            

    // CROW_ROUTE(app, "/ws")
    //     .websocket()
    //     .onopen([&](crow::websocket::connection& conn) {
    //         // WebSocket connection opened
    //         cout << "New user" << endl;
    //         return true;
    //     })
    //     .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
    //         // WebSocket connection closed
    //         cout << "Connection closed: " << reason << endl;
    //     })
    //     .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
    //         // Handle the message here
    //         // You can access the message, is_binary, and conn variables as needed

    //         cout << "Received message: " << data << endl;

    //         crow::json::rvalue json = crow::json::load(data);

    //         if (!json){
    //             return false;
    //         }
    //         else if (json["rows"].i() == -1){
    //             return true;
    //         }
    //         else{

    //             //prosessReuestSync(conn, json);
    //             pool.process(conn, json);
    //             //prosessReuestAsync(conn, data);

    //             // Return true to keep the WebSocket connection open
    //             return true;
    //         }

    //     });


    app.port(2288).run();
};