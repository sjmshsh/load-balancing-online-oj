#include "compile_run.hpp"
#include "../comm/httplib.h"


using namespace ns_compile_and_run;
using namespace httplib;

void Usage(std::string proc)
{

    std::cerr << "Usage: " << proc << " port" << std::endl;
}

//编译服务随时可能被多个人请求，必须保证传递上来的code，形成源文件名称的时候，要具有唯一性
//不然多个用户可能会相互影响
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        return 1;
    }

    Server svr;


    svr.Post("/compile_and_run", [](const Request &req, Response &resp)
             {
        std::string in_json = req.body;
        std::string out_json;
        if(!in_json.empty())
        {
            CompileAndRun::Start(in_json, &out_json);
            resp.set_content(out_json, "application/json;charset=utf-8;");
        } });
        
    svr.listen("0.0.0.0", atoi(argv[1]));
    return 0;
}