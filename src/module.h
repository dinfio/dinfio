/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2024. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 Module
------------------------------------------------------------
*/

void init_builtin(int argc, char* argv[]) {
    // Constant 'dinfio'

    gc<DataType> di = core::create_empty_object("dinfio_info");

    gc<DataType> version = new_gc<DataType>(__TYPE_STRING__);
    version->__value_string = __DINFIO_VERSION__;
    di->__value_object->__attributes["version"] = version;

    gc<DataType> version_major = new_gc<DataType>(__TYPE_STRING__);
    version_major->__value_string = __DINFIO_VERSION_MAJOR__;
    di->__value_object->__attributes["version_major"] = version_major;

    gc<DataType> version_minor = new_gc<DataType>(__TYPE_STRING__);
    version_minor->__value_string = __DINFIO_VERSION_MINOR__;
    di->__value_object->__attributes["version_minor"] = version_minor;

    gc<DataType> version_rev = new_gc<DataType>(__TYPE_STRING__);
    version_rev->__value_string = __DINFIO_VERSION_REVISION__;
    di->__value_object->__attributes["version_revision"] = version_rev;

    gc<DataType> version_number = new_gc<DataType>(__TYPE_DOUBLE__);
    version_number->__value_double = __DINFIO_VERSION_NUMBER__;
    di->__value_object->__attributes["version_number"] = version_number;

    gc<DataType> platform = new_gc<DataType>(__TYPE_STRING__);
    platform->__value_string = __DINFIO_PLATFORM__;
    di->__value_object->__attributes["platform"] = platform;

    gc<DataType> build_date = new_gc<DataType>(__TYPE_STRING__);
    build_date->__value_string = __DINFIO_BUILD_DATE_RAW__;
    di->__value_object->__attributes["build_date"] = build_date;

    gc<DataType> path = new_gc<DataType>(__TYPE_STRING__);
    path->__value_string = __DINFIO_PATH__;
    di->__value_object->__attributes["path"] = path;

    gc<DataType> is_linux = new_gc<DataType>(__TYPE_BOOL__);
    is_linux->__value_bool = __DINFIO_PLATFORM_RAW__ == 0;
    di->__value_object->__attributes["is_linux"] = is_linux;

    gc<DataType> is_mac = new_gc<DataType>(__TYPE_BOOL__);
    is_mac->__value_bool = __DINFIO_PLATFORM_RAW__ == 1;
    di->__value_object->__attributes["is_mac"] = is_mac;

    gc<DataType> is_windows = new_gc<DataType>(__TYPE_BOOL__);
    is_windows->__value_bool = __DINFIO_PLATFORM_RAW__ == 2;
    di->__value_object->__attributes["is_windows"] = is_windows;

    __variables["1dinfio"] = di;


    // Constant 'arguments'

    gc<DataType> args = core::create_array(0);

    for (int i = 1; i < argc; i++) {
        gc<DataType> argi = new_gc<DataType>(__TYPE_STRING__);
        argi->__value_string = argv[i];
        args->__value_array->__elements.push_back(argi);
    }

    __variables["1arguments"] = args;


    // Built-in modules

    standardIO::__init();
    core::__init();


    // Initialise all fios_module::init() functions

    for (int i = 0; i < __init_functions.size(); i++) {
        uint_fast32_t cid = 1;
        call_function(__init_functions.at(i), cid);
    }
}

void import_module(string mod) {
    string fm = __MODULES_PATH__ + mod + "/" + mod + __MODULE_EXTENSION__;
 
    void* handle = dlopen(fm.c_str(), __RTLD_TYPE__);

    if (handle == NULL) {
        error_message("Could not import '" + mod + "': " + dlerror());
    }

    Module* (*create)();
    void (*destroy)(Module*);

    create = (Module*(*)()) dlsym(handle, "create_module");
    destroy = (void(*)(Module*)) dlsym(handle, "destroy_module");

    Module* m = (Module*) create();
    m->__init(__module_connector);

    __modules.push_back(m);


    // Special modules

    if (mod == "gui") {
        __gui_module = m;
        __gui_event_loop = 1;
    }
}

uint_fast16_t Connector::__register_function(string name) {
    return register_function(name, __REG_EXTERNAL_FUNCTION__);
}

gc<DataType> Connector::__get_value(AST* expression, uint_fast32_t& caller_id) {
    return get_value(expression, caller_id);
}

void Connector::__call_function(AST* func, uint_fast32_t& caller_id) {
    call_function(func, caller_id);
}

gc<DataType> Connector::__create_array(uint_fast32_t size) {
    return core::create_array(size);
}

gc<DataType> Connector::__create_object(const string& name) {
    return core::create_empty_object(name);
}

void Connector::__object_set_attribute(gc<DataType> d, string name, gc<DataType> value) {
	d->__value_object->__attributes[name] = value;
}

void Connector::__object_set_function(gc<DataType> d, string name, uint_fast16_t value) {
	d->__value_object->__functions[name] = value;
}

void Connector::__add_constant(const string& name, gc<DataType> value) {
    __variables["1" + name] = value;
}

void Connector::__error_message(string error) {
    error_message(error);
}

void Connector::__error_message_param(string error) {
    error_message_param(error);
}

void Connector::__error_message_params(string error, uint8_t size) {
    error_message_params(error, size);
}

bool Connector::__variable_exists(string var_name, uint_fast32_t& caller_id) {
    return variable_exists(var_name, caller_id);
}

void Connector::__remove_garbage(AST* param, gc<DataType> d_param) {
    remove_garbage(param, d_param);
}

string Connector::__get_current_file() {
    return __codes_info[__cur_i]->__file;
}

string Connector::__get_version() {
    return __DINFIO_VERSION__;
}

string Connector::__get_path() {
    return __DINFIO_PATH__;
}
