#ifndef __SIMPLE_TEXT_EDITOR_H__
#define __SIMPLE_TEXT_EDITOR_H__

/*
Simple Text Editor
- 간단한 라인 에디터
*/

#include <iostream>
#include <string>
#include <fstream>

#include "SinglyLinkedList.h"


using List = SinglyLinkedList<std::string>;
using Line = OneWayNode<std::string>;

class SimpleTextEditor {
    List* textFile;
    static const int BUFFER_SIZE = 1000;
public:
    SimpleTextEditor();
    ~SimpleTextEditor();
    void Run();

private:
    void _displayText();
    void _info(const std::string& message);
    void _warning(const std::string& message);
    void _error(const std::string& message);
    void _help();
    void _read_file();
    void _write_file();
    void _delete_line();
    void _insert_line();
    void _modify_line();
    void _do_command(char command);
};



#endif
