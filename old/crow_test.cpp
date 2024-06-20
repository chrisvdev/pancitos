#include "crow.h"
#include <iostream>

struct MyMiddleware
{
  struct context
  {
  };

  void before_handle(crow::request &req, crow::response &res, context &ctx)
  {
    std::string auth = std::string(req.url_params.get("auth"));
    std::string alita = std::string("alita");
    if (auth != alita)
    {
      auto result = auth == alita;
      std::cout << req.url_params.get("auth") << " " << result << std::endl;
      res.code = 403;
      res.end();
    }
  }

  void after_handle(crow::request &req, crow::response &res, context &ctx)
  {
    res.add_header("server", "ChrisVServer");
    res.end();
  }
};

int main()
{
  crow::App<MyMiddleware> app; // define your crow application

  // define your endpoint at the root directory
  CROW_ROUTE(app, "/")
  ([]()
   { return "Hello world"; }); // () => {}

  CROW_ROUTE(app, "/pythonesa")
  ([]()
   { return "Holi"; });

  CROW_ROUTE(app, "/hello/<string>/<string>")
  ([](std::string name, std::string last_name)
   { return "Hello " + name + " " + last_name; });

  CROW_ROUTE(app, "/sum/<int>/<int>")
  ([](int a, int b)
   { return "La suma es " + std::to_string(a + b); });

  CROW_ROUTE(app, "/res/<int>/<int>").methods(crow::HTTPMethod::POST)([](int a, int b)
                                                                      { return "La resta es " + std::to_string(a - b); });

  CROW_ROUTE(app, "/data")
      .methods(crow::HTTPMethod::POST)([](const crow::request &req) { //.../data?name=pepe&age=20&city=madrid
        crow::response res;
        const std::string name = req.url_params.get("name");
        res.body = "Hello " + name;
        res.code = 201;
        res.add_header("Content-Type", "text/plain");
        res.add_header("Location", "/data");
        res.add_header("name", name);
        return res;
      });

  // set the port, set the app to run on multiple threads, and run the app
  app.port(18080).multithreaded().run_async();
}