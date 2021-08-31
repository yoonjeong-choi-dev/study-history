#include "SimpleTextEditor.h"


SimpleTextEditor::SimpleTextEditor() {
    textFile = new List();
}

SimpleTextEditor::~SimpleTextEditor() {
    delete textFile;
}

void SimpleTextEditor::_displayText() {
    Line* line = textFile->getHeadPointer();

    std::cout << "====================================" << std::endl;
    for (int i = 0; i < textFile->length(); i++) {
        std::cout << i << " : " << line->data << std::endl;
        line = line->next;
    }
    std::cout << "====================================" << std::endl;
}

void SimpleTextEditor::_info(const std::string& message) {
    std::cout << "[INFO] " << message << std::endl;
}

void SimpleTextEditor::_warning(const std::string& message) {
    std::cout << "[WARN] " << message << std::endl;
}

void SimpleTextEditor::_error(const std::string& message) {
    std::cout << "[ERROR] " << message << std::endl;
    exit(1);
}

void SimpleTextEditor::_help() {
    std::cout << "====================================" << std::endl;
    std::cout << "i : 입력" << std::endl;
    std::cout << "d : 삭제" << std::endl;
    std::cout << "m : 수정" << std::endl;
    std::cout << "r : 파일 읽기" << std::endl;
    std::cout << "w : 파일 쓰기" << std::endl;
    std::cout << "q: 종료" << std::endl;
    std::cout << "====================================" << std::endl;
}


void SimpleTextEditor::_read_file() {
    std::ifstream rfile;
    std::string fileName;
    char buffer[BUFFER_SIZE];

    if (!textFile->isEmpty()) {
        textFile->clear();
    }

    std::cout << "파일 이름 : ";
    std::cin >> fileName;

    rfile.open(fileName);

    if (!rfile.is_open()) {
        _warning(fileName + " 파일을 열 수 없습니다");
    }
    else {
        while (rfile.getline(buffer, sizeof(buffer))) {
            textFile->append_back(buffer);
        }
        _info("파일 불러오기 성공!");
    }

    rfile.close();
    _displayText();
}


void SimpleTextEditor::_write_file() {
    std::ofstream wfile;
    std::string fileName;
    char buffer[BUFFER_SIZE];


    std::cout << "파일 이름 : ";
    std::cin >> fileName;

    wfile.open(fileName);

    if (!wfile.is_open()) {
        _warning(fileName + " 파일을 열 수 없습니다");
    }
    else {

        Line* line = textFile->getHeadPointer();
        for (int i = 0; i < textFile->length(); i++) {
            wfile << line->data << std::endl;
            line = line->next;
        }
        _info("파일 저장 성공!");
    }

    wfile.close();
    _displayText();

}


void SimpleTextEditor::_delete_line() {

    if (textFile->isEmpty()) {
        _info("지울 라인이 없습니다.");
    }
    else {
        int lineNum;
        std::cout << "지우고 싶은 라인 번호를 입력하세요 : ";
        std::cin >> lineNum;
        if (textFile->length() <= lineNum) {
            _warning("지울 수 없는 라인입니다.");
            return;
        }
        textFile->remove_at(lineNum);
    }

    _displayText();
}


void SimpleTextEditor::_insert_line() {

    int lineNum;
    std::cout << "입력행 번호를 입력하세요 : ";
    std::cin >> lineNum;
    if (textFile->length() < lineNum || lineNum < 0) {
        _warning("입력할 수 없는 라인입니다.");
        return;
    }

    std::string inputLine;
    std::cout << "내용을 입력하세요 : ";

    std::cin.ignore();
    std::getline(std::cin, inputLine);

    textFile->insert(lineNum, inputLine);
    _info("입력 성공");
    _displayText();
}

void SimpleTextEditor::_modify_line() {

    int lineNum;
    std::cout << "수정할 라인 번호를 입력하세요 : ";
    std::cin >> lineNum;
    if (textFile->length() <= lineNum || lineNum < 0) {
        _warning("입력할 수 없는 라인입니다.");
        return;
    }

    std::string inputLine;
    std::cout << "내용을 입력하세요 : ";
    std::cin.ignore();
    std::getline(std::cin, inputLine);

    textFile->replace(lineNum, inputLine);
    _info("수정 성공");
    _displayText();
}

void SimpleTextEditor::_do_command(char command) {
    switch (command)
    {
    case 'd':
        _delete_line();
        break;
    case 'i':
        _insert_line();
        break;
    case 'm':
        _modify_line();
        break;
    case 'r':
        _read_file();
        break;
    case 'w':
        _write_file();
        break;
    case 'q':
        break;
    default:
        break;
    }
}

void SimpleTextEditor::Run() {
    char command;

    do {
        _help();
        std::cout << "Command : ";
        std::cin >> command;
        _do_command(command);

    } while (command != 'q');
}