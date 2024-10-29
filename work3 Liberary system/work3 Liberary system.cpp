#include <iostream>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Book {     // 書籍
    string title;
    string writer;
    string id;
};

struct Reader {    // 借閱者
    string name;
    string id;
};

void ubiubi(list<Book>& books) {    // 初始化書籍
    books.push_back({ "紅樓夢", "曹雪芹", "A1234" });
    books.push_back({ "西遊記", "吳承恩", "B2345" });
    books.push_back({ "水滸傳", "施耐庵", "B3456" });
    books.push_back({ "三國演義", "羅貫中", "C4567" });
    books.push_back({ "金瓶梅", "蘭陵笑笑生", "C5678" });
    books.push_back({ "聊齋志異", "蒲松齡", "D6789" });
    books.push_back({ "儒林外史", "吳敬梓", "D7890" });
    books.push_back({ "封神演義", "許仲琳", "E8901" });
    books.push_back({ "鏡花緣", "李汝珍", "E9012" });
    books.push_back({ "老殘遊記", "劉鶚", "F0123" });
}

void addBook(list<Book>& books, const string& title, const string& writer, const string& id) {   // 新增書籍
    books.push_back({ title, writer, id });
}

void removeBook(list<Book>& books, list<Reader>& readers, const string& id) {
    // 刪除書籍
    books.remove_if([&id](const Book& book) { return book.id == id; });

    // 刪除借閱者的借閱記錄
    readers.remove_if([&id](const Reader& reader) { return reader.id == id; });
}

void Booksystem(list<Book>& books, list<Reader>& readers) {   // 書籍管理系統
    int choice;
    while (true) {
        system("CLS");
        cout << "圖書館管理系統" << endl;
        cout << "1.新增書籍" << endl;
        cout << "2.刪除書籍" << endl;
        cout << "3.查詢書籍" << endl;
        cout << "4.列出書籍" << endl;
        cout << "5.離開" << endl;
        if (!(cin >> choice)) {
            cin.clear(); // 清除錯誤標誌
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略無效輸入
            cout << "無效的選項，請重新輸入" << endl;
            system("pause");
            continue;
        }

        switch (choice) {
        case 1:
        {
            string title, writer, id;
            cout << "請輸入書名: ";
            cin >> title;
            cout << "請輸入作者: ";
            cin >> writer;
            cout << "請輸入編號: ";
            cin >> id;
            addBook(books, title, writer, id);
            break;
        }
        case 2:
        {
            string id;
            cout << "請輸入編號: ";
            cin >> id;

            // 檢查書籍是否存在
            auto it = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
            if (it == books.end()) {
                cout << "查無此書" << endl;
            }
            else {
                removeBook(books, readers, id);
				cout << "刪除成功" << endl;
            }
            break;
        }

        case 3:
        {
            string id;
            cout << "請輸入編號: ";
            cin >> id;
            bool found = false;
            for (const auto& book : books) {   // 搜尋書籍,若有則輸出書名,作者,編號，若無則輸出沒有此書
                if (book.id == id) {
                    cout << "有此書" << endl;
                    cout << "書名: " << book.title << ", 作者: " << book.writer << ", 編號: " << book.id << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "沒有此書" << endl;
            }
            break;
        }
        case 4:
        {
            if (books.empty()) {
                cout << "沒有書籍" << endl;
            }
            else {
                // 將書籍從 list 複製到 vector
                vector<Book> sortedBooks(books.begin(), books.end());

                // 使用 std::sort 依照圖書編號排序
                sort(sortedBooks.begin(), sortedBooks.end(), [](const Book& a, const Book& b) {
                    return a.id < b.id;
                    });

                // 輸出排序後的書籍
                for (const auto& book : sortedBooks) {
                    cout << "書名: " << book.title << ", 作者: " << book.writer << ", 編號: " << book.id << endl;
                }
            }
            break;
        }

        case 5:
            return;
        default:
            cout << "無效的選項" << endl;
            break;
        }
        system("pause");
    }
}

void pipi(list<Reader>& readers) {   // 初始化借閱者
    readers.push_back({ "小明", "A1234" });
    readers.push_back({ "小明", "B2345" });
    readers.push_back({ "小華", "C4567" });
    readers.push_back({ "小美", "D6789" });
    readers.push_back({ "小美", "E8901" });
    readers.push_back({ "小強", "F0123" });
    readers.push_back({ "小麗", "B3456" });
    readers.push_back({ "小麗", "C5678" });
}

void addReader(list<Reader>& readers, const string& name, const string& id, const list<Book>& books) {
    // 檢查書籍是否存在於圖書系統中
    auto bookIt = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (bookIt == books.end()) {
        cout << "沒有此書" << endl;
        return;
    }

    // 檢查書籍是否已被借出
    auto readerIt = find_if(readers.begin(), readers.end(), [&id](const Reader& reader) { return reader.id == id; });
    if (readerIt != readers.end()) {
        cout << "此書已被借出" << endl;
        return;
    }
	//若以上都沒有問題，則新增借閱者
    readers.push_back({ name, id });
}

void ReaderSystem(const list<Book>& books, list<Reader>& readers) {   // 借閱者管理系統
    int choice;

    while (true) {
        system("CLS");
        cout << "借閱者管理系統" << endl;
        cout << "1.新增借閱者" << endl;
        cout << "2.刪除借閱者" << endl;
        cout << "3.查詢借閱者" << endl;
        cout << "4.列出借閱者" << endl;
        cout << "5.離開" << endl;
        if (!(cin >> choice)) {
            cin.clear(); // 清除錯誤標誌
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略無效輸入
            cout << "無效的選項，請重新輸入" << endl;
            system("pause");
            continue;
        }

        switch (choice) {
        case 1:
        {
            string name, id;
            cout << "請輸入姓名: ";
            cin >> name;
            cout << "請輸入編號: ";
            cin >> id;
            addReader(readers, name, id, books);
            break;
        }
        case 2:
        {
            string name;
            cout << "請輸入姓名: ";
            cin >> name;

            // 檢查借閱者是否存在
            auto it = find_if(readers.begin(), readers.end(), [&name](const Reader& reader) { return reader.name == name; });
            if (it == readers.end()) {
                cout << "查無此借閱者" << endl;
            }
            else {
                readers.remove_if([&name](const Reader& reader) { return reader.name == name; });
				cout << "刪除成功" << endl;
            }
            break;
        }

        case 3:  // 查詢借閱者，並用map儲存姓名與借閱的書籍編號這樣就可以一次輸出一個人借了哪些書
        {
            string name;
            cout << "請輸入姓名: ";
            cin >> name;
            bool found = false;
            map<string, vector<string>> readerMap;  //因為一個人可以借多本書，所以用vector儲存書籍編號
            for (const auto& reader : readers) {
                if (reader.name == name) {
                    readerMap[reader.name].push_back(reader.id);
                    found = true;
                }
            }
            if (found) {
                for (const auto& entry : readerMap) {    //遍歷readerMap這個list，並將姓名與借閱的書籍編號輸出
                    cout << "姓名: " << entry.first << ", 借閱的圖書編號: {";
                    for (size_t i = 0; i < entry.second.size(); ++i) {  //遍歷vector，並輸出書籍編號
                        cout << "\"" << entry.second[i] << "\"";
                        if (i < entry.second.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << "}" << endl;
                }
            }
            else {
                cout << "沒有此借閱者" << endl;
            }
            break;
        }

        case 4:
        {
            if (readers.empty()) {
                cout << "沒有借閱者" << endl;
            }
            else {
                map<string, vector<string>> readerMap;
                for (const auto& reader : readers) {
                    readerMap[reader.name].push_back(reader.id);
                }
                for (const auto& entry : readerMap) {  //
                    cout << "姓名: " << entry.first << ", 借閱的圖書編號: {";
                    for (size_t i = 0; i < entry.second.size(); ++i) {
                        cout << "\"" << entry.second[i] << "\"";
                        if (i < entry.second.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << "}" << endl;
                }
            }
            break;
        }
        case 5:
            return;
        default:
            cout << "無效的選項" << endl;
            break;
        }
        system("pause");
    }
}

int main() {
    int choice;
    list<Book> books;
    list<Reader> readers;
    ubiubi(books);
    pipi(readers);
    while (true) {
        system("CLS");
        cout << "請問要用[圖書管理]程式還是[借閱者管理]程式?" << endl;
        cout << "1.圖書管理" << endl;
        cout << "2.借閱者管理" << endl;
        cout << "3.結束程式" << endl;
        if (!(cin >> choice)) {
            cin.clear(); // 清除錯誤標誌
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略無效輸入
            cout << "無效的選項，請重新輸入" << endl;
            system("pause");
            continue;
        }

        if (choice == 1) {
            Booksystem(books, readers);
        }
        else if (choice == 2) {
            ReaderSystem(books, readers);
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "輸入錯誤" << endl;
        }
    }
    return 0;
}
