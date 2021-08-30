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
    std::cout << "i : �Է�" << std::endl;
    std::cout << "d : ����" << std::endl;
    std::cout << "m : ����" << std::endl;
    std::cout << "r : ���� �б�" << std::endl;
    std::cout << "w : ���� ����" << std::endl;
    std::cout << "q: ����" << std::endl;
    std::cout << "====================================" << std::endl;
}


void SimpleTextEditor::_read_file() {
    std::ifstream rfile;
    std::string fileName;
    char buffer[BUFFER_SIZE];

    if (!textFile->isEmpty()) {
        textFile->clear();
    }

    std::cout << "���� �̸� : ";
    std::cin >> fileName;

    rfile.open(fileName);

    if (!rfile.is_open()) {
        _warning(fileName + " ������ �� �� �����ϴ�");
    }
    else {
        while (rfile.getline(buffer, sizeof(buffer))) {
            textFile->append_back(buffer);
        }
        _info("���� �ҷ����� ����!");
    }

    rfile.close();
    _displayText();
}


void SimpleTextEditor::_write_file() {
    std::ofstream wfile;
    std::string fileName;
    char buffer[BUFFER_SIZE];


    std::cout << "���� �̸� : ";
    std::cin >> fileName;

    wfile.open(fileName);

    if (!wfile.is_open()) {
        _warning(fileName + " ������ �� �� �����ϴ�");
    }
    else {

        Line* line = textFile->getHeadPointer();
        for (int i = 0; i < textFile->length(); i++) {
            wfile << line->data << std::endl;
            line = line->next;
        }
        _info("���� ���� ����!");
    }

    wfile.close();
    _displayText();

}


void SimpleTextEditor::_delete_line() {

    if (textFile->isEmpty()) {
        _info("���� ������ �����ϴ�.");
    }
    else {
        int lineNum;
        std::cout << "����� ���� ���� ��ȣ�� �Է��ϼ��� : ";
        std::cin >> lineNum;
        if (textFile->length() <= lineNum) {
            _warning("���� �� ���� �����Դϴ�.");
            return;
        }
        textFile->remove_at(lineNum);
    }

    _displayText();
}


void SimpleTextEditor::_insert_line() {

    int lineNum;
    std::cout << "�Է��� ��ȣ�� �Է��ϼ��� : ";
    std::cin >> lineNum;
    if (textFile->length() < lineNum || lineNum < 0) {
        _warning("�Է��� �� ���� �����Դϴ�.");
        return;
    }

    std::string inputLine;
    std::cout << "������ �Է��ϼ��� : ";

    std::cin.ignore();
    std::getline(std::cin, inputLine);

    textFile->insert(lineNum, inputLine);
    _info("�Է� ����");
    _displayText();
}

void SimpleTextEditor::_modify_line() {

    int lineNum;
    std::cout << "������ ���� ��ȣ�� �Է��ϼ��� : ";
    std::cin >> lineNum;
    if (textFile->length() <= lineNum || lineNum < 0) {
        _warning("�Է��� �� ���� �����Դϴ�.");
        return;
    }

    std::string inputLine;
    std::cout << "������ �Է��ϼ��� : ";
    std::cin.ignore();
    std::getline(std::cin, inputLine);

    textFile->replace(lineNum, inputLine);
    _info("���� ����");
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