#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <limits>

// 清屏函数
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else 
    std::system("clear");
#endif
}

// 清理输入流
void clearCin() {
    std::cin.clear();
    if (std::cin.rdbuf()->in_avail() > 0) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// 计算整数位数
int countDigits(int num) {
    if (num < 0) {
        num = -num;
    }
    if (num == 0) {
        return 1;
    }
    int digits = 0;
    while (num > 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}


// 显示菜单函数
int showMenu() {
    clearScreen();
    std::cout << "=======通讯录管理系统=======" << '\n';
    std::cout << "|     （1）显示联系人      |" << '\n';
    std::cout << "|     （2）新增联系人      |" << '\n';
    std::cout << "|     （3）删除联系人      |" << '\n';
    std::cout << "|     （4）修改联系人      |" << '\n';
    std::cout << "|     （5）查找联系人      |" << '\n';
    std::cout << "|     （6）清空联系人      |" << '\n';
    std::cout << "|     （0）退出通讯录      |" << '\n';
    std::cout << "============================" << std::endl;

    std::cout << "请输入命令编号：";
    int select;
    while (!(std::cin >> select)) {
        std::cout << "错误指令！请重新输入：";
        clearCin();
    }
    clearCin();
    return select;
}

// 联系人结构
struct Contacts {
    std::string name;
    int gender;
    int age;
    std::string phoneNumber;
    std::string addr;
};

// 通讯录
std::vector <struct Contacts> addrBook;

// 打印vector
void printBook(std::vector <struct Contacts>* addrBook, std::string title = "", std::vector<int> findArr = {}) {
    // 计算每列的最大字符数
    int columnWidths[5] = {4,4,4,4,4};

    for (int i = 0; i < (*addrBook).size(); i++) {
        columnWidths[0] = std::max(columnWidths[0], static_cast<int>((*addrBook)[i].name.length()));
        columnWidths[2] = std::max(columnWidths[2], countDigits((*addrBook)[i].age));
        columnWidths[3] = std::max(columnWidths[3], static_cast<int>((*addrBook)[i].phoneNumber.length()));
        columnWidths[4] = std::max(columnWidths[4], static_cast<int>((*addrBook)[i].addr.length()));
    }

    // 是否传入title
    if (title.size()) {
        int sunColumn = 14;
        for (int i = 0; i < 5; i++) {
            sunColumn += columnWidths[i];
        }
        int space = sunColumn - 12;
        int leftPad = space / 2;
        int rightPad = space - leftPad;
        std::cout << std::string(leftPad, '=') << title << std::string(rightPad, '=') << std::endl;
    }

    std::cout << std::setw(6) << std::left << "编号";
    std::cout << std::setw(columnWidths[0] + 2) << std::left << "姓名";
    std::cout << std::setw(columnWidths[1] + 2) << std::left << "性别";
    std::cout << std::setw(columnWidths[2] + 2) << std::left << "年龄";
    std::cout << std::setw(columnWidths[3] + 2) << std::left << "号码";
    std::cout << std::setw(columnWidths[4] + 2) << std::left << "住址" << std::endl;

    // 是否传入的指定索引
    if (findArr.size()) {
        for (int i = 0; i < findArr.size(); i++) {
            std::cout << std::setw(6) << std::left << findArr[i];
            std::cout << std::setw(columnWidths[0] + 2) << std::left << (*addrBook)[findArr[i]].name;
            std::cout << std::setw(columnWidths[1] + 2) << std::left << ((*addrBook)[findArr[i]].gender == 1 ? "男" : "女");
            std::cout << std::setw(columnWidths[2] + 2) << std::left << (*addrBook)[findArr[i]].age;
            std::cout << std::setw(columnWidths[3] + 2) << std::left << (*addrBook)[findArr[i]].phoneNumber;
            std::cout << std::setw(columnWidths[4] + 2) << std::left << (*addrBook)[findArr[i]].addr << std::endl;
        }
    }else{
        for (int i = 0; i < (*addrBook).size(); i++) {
            std::cout << std::setw(6) << std::left << i;
            std::cout << std::setw(columnWidths[0] + 2) << std::left << (*addrBook)[i].name;
            std::cout << std::setw(columnWidths[1] + 2) << std::left << ((*addrBook)[i].gender == 1 ? "男" : "女");
            std::cout << std::setw(columnWidths[2] + 2) << std::left << (*addrBook)[i].age;
            std::cout << std::setw(columnWidths[3] + 2) << std::left << (*addrBook)[i].phoneNumber;
            std::cout << std::setw(columnWidths[4] + 2) << std::left << (*addrBook)[i].addr << std::endl;
        }
    }
}


// 查找联系人
std::vector<int> findContact(std::vector <struct Contacts>* addrBook, std::string name) {
    // 查到的练习人vector
    std::vector<int> findArr;

    for (int i = 0; i < (*addrBook).size(); i++) {
        if ((*addrBook)[i].name == name) {
            findArr.push_back(i);
        }
    }
    return findArr;
}

// 显示所有联系人
void showAll() {
    clearScreen();
    printBook(&addrBook, " 所有联系人 ");
    std::cout << "按回车键继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// 新增联系人
void addContacts() {
    clearScreen();
    clearCin();
    std::cout << "======= 新增联系人 =======" << std::endl;

    std::string name;
    std::cout << "请输入联系人姓名：";
    std::getline(std::cin, name);

    int gender;
    std::cout << "请输入联系人性别（1.男/2.女）：";
    while (!(std::cin >> gender) || (gender != 1 && gender != 2) || std::cin.peek() != '\n') {
        std::cout << "输入错误，请重新输入：";
        clearCin();
    }

    int age;
    std::cout << "请输入联系人年龄：";
    while (!(std::cin >> age) || age < 0 || std::cin.peek() != '\n') {
        std::cout << "输入错误，请重新输入：";
        clearCin();
    }

    clearCin();
    std::string number;
    std::cout << "请输入联系人号码：";
    std::getline(std::cin, number);

    std::string addr;
    std::cout << "请输入联系人地址：";
    std::getline(std::cin,addr);

    struct Contacts contact = { name,gender,age,number,addr };
    addrBook.push_back(contact);

    std::cout << "添加成功！按回车键继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// 删除联系人
void deleteContacts() {
    clearScreen();
    std::cout << "======= 删除联系人 =======" << std::endl;
    std::cout << "请输入要删除的联系人姓名：";
    std::string name;
    std::getline(std::cin, name);

    std::vector<int> findArr;
    findArr = findContact(&addrBook, name);
    if (!findArr.size()) {
        std::cout << "未找到该联系人" << std::endl;
    }else{
        clearScreen();
        printBook(&addrBook, " 删除联系人 ", findArr);
        std::cout << "请输入要删除联系人的编号：";
        int num;
        bool vaildInput = false;
        do {
            // 判断输入是否合法
            if (!(std::cin >> num)) {
                clearCin();
                std::cout << "输入错误，请重新输入：";
            }
            else
            {
                // 判断输入是否在范围内
                for (int item : findArr) {
                    if (item == num) {
                        vaildInput = true;
                        // 结束for循环
                        break;
                    }
                }
                // 判断用户输入是否正确
                if (!vaildInput) {
                    std::cout << "输入编号错误，请重新输入：";
                }

            }
        } while (!vaildInput);

        addrBook.erase(addrBook.begin() + num);
        std::cout << "删除成功！" << std::endl;
    }

    std::cout << "按回车键继续...";
    clearCin();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// 修改联系人
void changeContacts() {
    clearScreen();
    clearCin();
    std::cout << "======= 修改联系人 =======" << std::endl;
    std::cout << "请输入要修改的联系人姓名：";
    std::string name;
    std::getline(std::cin, name);

    std::vector<int> findArr;
    findArr = findContact(&addrBook, name);


    if (!findArr.size()) {
        std::cout << "未找到该联系人，按回车键继续..." << std::endl;
    }else{
        clearScreen();
        printBook(&addrBook, " 修改联系人 ", findArr);
        std::cout << "请输入要修改联系人的编号：";

        int num;
        bool vaildInput = false;
        do {
            // 判断输入是否合法
            if (!(std::cin >> num)) {
                clearCin();
                std::cout << "输入错误，请重新输入：";
            }
            else
            {
                // 判断输入是否在范围内
                for (int item : findArr) {
                    if (item == num) {
                        vaildInput = true;
                        // 结束for循环
                        break;
                    }
                }
                // 判断用户输入是否正确
                if (!vaildInput) {
                    std::cout << "输入编号错误，请重新输入：";
                }

            }
        } while (!vaildInput);
        
        clearCin();
        std::string newname;
        std::cout << "请输入修改后的联系人姓名：";
        std::getline(std::cin, newname);

        int newgender;
        std::cout << "请输入修改后的联系人性别（1.男/2.女）：";
        while (!(std::cin >> newgender) || (newgender != 1 && newgender != 2) || std::cin.peek() != '\n') {
            std::cout << "输入错误，请重新输入：";
            clearCin();
        }

        int newage;
        std::cout << "请输入联系人年龄：";
        while (!(std::cin >> newage) || newage < 0 || std::cin.peek() != '\n') {
            std::cout << "输入错误，请重新输入：";
            clearCin();
        }

        clearCin();
        std::string newnumber;
        std::cout << "请输入联系人号码：";
        std::getline(std::cin, newnumber);

        std::string newaddr;
        std::cout << "请输入联系人地址：";
        std::getline(std::cin, newaddr);
        
        addrBook[num].name = newname;
        addrBook[num].gender = newgender;
        addrBook[num].age = newage;
        addrBook[num].phoneNumber = newnumber;
        addrBook[num].addr = newaddr;

        std::cout << "修改成功！按回车键继续..." << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// 查找联系人
void searchContacts() {
    clearScreen();
    std::cout << "======= 查找联系人 =======" << std::endl;
    std::cout << "输入查找联系人姓名：";
    std::string name;
    std::getline(std::cin, name);
    std::vector<int> findArr;
    findArr = findContact(&addrBook, name);

    if (!findArr.size()) {
        std::cout << "未找到该联系人！按回车键继续..." << std::endl;
    }else {
        clearScreen();
        printBook(&addrBook, " 联系人信息 ", findArr);
        std::cout << "查询成功！按回车键继续..." << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// 清空联系人
void clearContacts() {
    clearScreen();
    std::cout << "======= 清空联系人 =======" << std::endl;
    std::cout << "是否清空联系人？（1.确认/2.取消）：";
    int num;
    while (!(std::cin >> num) || (num != 1 && num != 2) || std::cin.peek() != '\n') {
        clearCin();
        std::cout << "输入错误，请重新输入：";
    }
    if (num == 1) {
        addrBook.clear();
        std::cout << "通讯录清除成功！按回车键继续...";
    }
    else {
        std::cout << "操作取消！按回车键继续...";
    }
    clearCin();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int select;
    do {
        select = showMenu();
        switch (select)
        {
        case 1:
            showAll();
            break;
        case 2:
            addContacts();
            break;
        case 3:
            deleteContacts();
            break;
        case 4:
            changeContacts();
            break;
        case 5:
            searchContacts();
            break;
        case 6:
            clearContacts();
            break;
        case 0:
            std::cout << "欢迎下次使用！按回车键退出...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        default:
            break;
        }
    } while (select);
 
	return 0;
}