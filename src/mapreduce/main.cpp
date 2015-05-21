#include <iostream>
#include <fstream>

#include "script_object_json_source.h"
#include "script_array_json_source.h"
#include "script_object_factory.h"
#include "script_array_factory.h"
#include "script_object_keys_cache.h"

#include "libjsapi.h"

bool IsObject(const char* json, int length) {
    int front = 0;
    while (front < (length - 1) && (json[front] == ' ' || json[front] == '\t' || json[front] == '\n')) {
        front++;
    }
    
    int back =  length - 1;
    while (back > 0 && json[back] == ' ' || json[back] == '\t' || json[back] == '\n') {
        back--;
    }
    
    return json[front] == '{' && json[back] == '}';
}

bool IsArray(const char* json, int length) {
    int front = 0;
    while (front < (length - 1) && (json[front] == ' ' || json[front] == '\t' || json[front] == '\n')) {
        front++;
    }
    
    int back = length - 1;
    while (back > 0 && json[back] == ' ' || json[back] == '\t' || json[back] == '\n') {
        back--;
    }
    
    return json[front] == '[' && json[back] == ']';
}

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "command line: [json file]" << std::endl;
        return 1;
    } else {
        try {
            std::ifstream istream;
            istream.open(argv[1], std::ios::in | std::ios::binary);
            if (!istream) {
                throw "Unable to open input file";
            }
            
            std::cerr << "Reading... ";
            istream.seekg(0, std::ios::end);
            auto fileLength = istream.tellg();
            istream.seekg(0, std::ios::beg);

            char* json = new char[fileLength];
            istream.read(json, fileLength);        
            std::cerr << "done" << std::endl;

            std::cerr << "Parsing... ";
            
            rs::scriptobject::ScriptObjectPtr scriptObj = nullptr;
            if (IsObject(json, fileLength)) {
                ScriptObjectJsonSource source(&json[0]);
                scriptObj = rs::scriptobject::ScriptObjectFactory::CreateObject(source);
            } /*else if (IsArray(json, fileLength)) {
                ScriptArrayJsonSource source(&json[0]);
                auto object = rs::scriptobject::ScriptArrayFactory::CreateArray(source);
            }*/ else {
                throw "Error: the input file was not recognised as JSON";
            }
            
            std::cerr << "done, found: " << std::endl << 
                rs::scriptobject::ScriptObjectKeysCache::getCount() << " keys" << std::endl <<
                rs::scriptobject::ScriptObjectFactory::getCount() << " objects" << std::endl <<
                (rs::scriptobject::ScriptObjectFactory::getTotalBytesAllocated() / 1024) << " total objects KB" << std::endl <<
                rs::scriptobject::ScriptArrayFactory::getCount() << " arrays" << std::endl <<
                (rs::scriptobject::ScriptArrayFactory::getTotalBytesAllocated() / 1024) << " total array KB" << std::endl;
            
            delete[] json;
            
            rs::jsapi::Runtime rt;
            
            rs::jsapi::Value object(rt);
            rs::jsapi::DynamicObject::Create(rt, 
                [&](const char* name, rs::jsapi::Value& value) {
                    switch (scriptObj->getType(name)) {
                        case rs::scriptobject::ScriptObjectType::Boolean:
                            value = scriptObj->getBoolean(name);
                            return;
                        case rs::scriptobject::ScriptObjectType::Int32:
                            value = scriptObj->getInt32(name);
                            return;                            
                        case rs::scriptobject::ScriptObjectType::String:
                            value = scriptObj->getString(name);
                            return;
                        case rs::scriptobject::ScriptObjectType::Double:
                            value = scriptObj->getDouble(name);
                            return;                        
                    }
                }, 
                nullptr, nullptr, nullptr, object);
                
            rs::jsapi::FunctionArguments args(rt);
            args.Append(object);
            args.Append("_id");
            rs::jsapi::Value result(rt);    
            rt.Evaluate("var myfunc = function(o, n) { return o[n]; }");
            rt.Call("myfunc", args, result);
            
            std::cout << result << std::endl;
                        
            return 0;
        } catch (const char* msg) {
            std::cerr << "Error: " << msg << std::endl;
            return 2;
        }
    }
        
    return 0;
}

