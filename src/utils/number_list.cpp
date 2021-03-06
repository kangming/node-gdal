

#include "number_list.hpp"

namespace node_gdal {

IntegerList::IntegerList()
	: list(NULL), len(0), name("")
{
}

IntegerList::IntegerList(const char* name)
	: list(NULL), len(0)
{
	name = (std::string(" ")+name).c_str();
}

IntegerList::~IntegerList()
{
	if(list) delete [] list;
}

int IntegerList::parse(Handle<Value> value)
{
	NanScope();
	unsigned int i;
	Handle<Array> arr;

	if(value->IsNull() || value->IsUndefined()) 
		return 0;

	if(value->IsArray()) {
		arr = value.As<Array>();
		len = arr->Length();
		if (len == 0) 
			return 0;

		list = new int [len];
		for (i = 0; i < len; ++i) {
			Handle<Value> element = arr->Get(i);
			if(element->IsNumber()){
				list[i] = element->Int32Value();
			} else {
				std::string err = std::string("Every element in the")+name+" array must be a number";
				NanThrowTypeError(err.c_str());
				return 1;
			}
		}
	} else if (value->IsNumber()) {
		list = new int [1];
		list[0] = value->Int32Value();
		len = 1;
	} else {
		std::string err = std::string(name)+"integer list must be an array or single integer";
		NanThrowTypeError(err.c_str());
		return 1;
	}
	return 0;
}

DoubleList::DoubleList()
	: list(NULL), len(0), name("")
{
}

DoubleList::DoubleList(const char* name)
	: list(NULL), len(0)
{
	name = (std::string(" ")+name).c_str();
}

DoubleList::~DoubleList()
{
	if(list) delete [] list;
}

int DoubleList::parse(Handle<Value> value)
{
	NanScope();
	unsigned int i;
	Handle<Array> arr;

	if(value->IsNull() || value->IsUndefined()) 
		return 0;

	if(value->IsArray()) {
		arr = value.As<Array>();
		len = arr->Length();
		if (len == 0) 
			return 0;

		list = new double [len];
		for (i = 0; i < len; ++i) {
			Handle<Value> element = arr->Get(i);
			if(element->IsNumber()){
				list[i] = element->NumberValue();
			} else {
				std::string err = std::string("Every element in the")+name+" array must be a number";
				NanThrowTypeError(err.c_str());
				return 1;
			}
		}
	} else if (value->IsNumber()) {
		list = new double [1];
		list[0] = value->NumberValue();
		len = 1;
	} else {
		std::string err = std::string(name)+"double list must be an array or single number";
		NanThrowTypeError(err.c_str());
		return 1;
	}
	return 0;
}


} //node_gdal namespace