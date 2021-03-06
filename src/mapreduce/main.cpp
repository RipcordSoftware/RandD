#include <iostream>
#include <fstream>
#include <chrono>

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
            
            rs::scriptobject::ScriptObjectPtr rootObj = nullptr;
            if (IsObject(json, fileLength)) {
                ScriptObjectJsonSource source(&json[0]);
                rootObj = rs::scriptobject::ScriptObjectFactory::CreateObject(source);
            } /*else if (IsArray(json, fileLength)) {
                ScriptArrayJsonSource source(&json[0]);
                arrayObj = rs::scriptobject::ScriptArrayFactory::CreateArray(source);
            } */else {
                throw "The input file was not recognised as JSON";
            }
            
            std::cerr << "done, found: " << std::endl << 
                rs::scriptobject::ScriptObjectKeysCache::getCount() << " keys" << std::endl <<
                rs::scriptobject::ScriptObjectFactory::getCount() << " objects" << std::endl <<
                (rs::scriptobject::ScriptObjectFactory::getTotalBytesAllocated() / 1024) << " total objects KB" << std::endl <<
                rs::scriptobject::ScriptArrayFactory::getCount() << " arrays" << std::endl <<
                (rs::scriptobject::ScriptArrayFactory::getTotalBytesAllocated() / 1024) << " total array KB" << std::endl;
            
            delete[] json;
            
            rs::jsapi::Runtime rt;
            
            auto arrayObj = rootObj->getArray("rows");
            
            std::vector<rs::jsapi::Value> resultKeys;
            resultKeys.reserve(4096);
            std::vector<rs::jsapi::Value> resultValues;
            resultValues.reserve(4096);
            
            rs::jsapi::Global::DefineFunction(rt, "emit", 
                [&](const std::vector<rs::jsapi::Value>& args, rs::jsapi::Value&) {
                    if (args.size() > 0) {
                        resultKeys.emplace_back(args[0]);
                        
                        if (args.size() > 1) {
                            resultValues.emplace_back(args[1]);
                        } else {
                            resultValues.emplace_back(rt);
                        }
                    }                                        
                });
            
            rs::scriptobject::ScriptObjectPtr scriptObj = nullptr;
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
            
            rs::jsapi::Value func(rt);
            rt.Evaluate("(function() { return function(doc) { if (doc._rev[0] == '1') emit(doc._id, doc.title); }; })()", func);
            
            rs::jsapi::Value temp(rt);
            
            auto start = std::chrono::high_resolution_clock::now();
            
            for (unsigned i = 0, length = arrayObj->count; i < length; ++i) {
                scriptObj = arrayObj->getObject(i)->getObject("doc");

                func.CallFunction(args);
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            
            for (auto result : resultKeys) {
                std::cout << result << std::endl;
            }

            std::cout << "Time: " << duration.count() << "ms" << std::endl;
            std::cout << "Rows: " << resultKeys.size() << std::endl;
                        
            return 0;
        } catch (const char* msg) {
            std::cerr << "Error: " << msg << std::endl;
            return 2;
        }
    }
        
    return 0;
}

