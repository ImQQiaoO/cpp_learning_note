#include "Message.h"

#include <iostream>

#include "Folder.h"

void Message::save(Folder &f) {
    folders.insert(&f); // 将给定Folder添加到我们的Folder列表中
    f.addMsg(this);     // 将本Message添加到f的Message集合中
}

void Message::remove(Folder &f) {
    folders.erase(&f);  // 将给定Folder从我们的Folder列表中删除
    f.remMsg(this);     // 将本Message从f的Message集合中删除
}

// 将本Message添加到指向m的Folder中
void Message::add_to_Folders(const Message &m) {
    for (auto f : m.folders)    // 对每个包含m的Folder
        f->addMsg(this);             // 向该Folder添加一个指向本Message的指针
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
    add_to_Folders(m);  // 将本消息添加到指向m的Folder中
}

// 从对应的Folder中删除本Message
void Message::remove_from_Folders() {
    for (auto f : folders)  // 对folders中每个指针
        f->remMsg(this);           // 从该Folder中删除本Message
}

Message::~Message() {
    remove_from_Folders();
}

Message &Message::operator=(const Message &rhs) {
    remove_from_Folders();      // 更新已有Folder
    contents = rhs.contents;    // 从rhs拷贝消息内容
    folders = rhs.folders;      // 从rhs拷贝Folder指针
    add_to_Folders(rhs);        // 将本Message添加到那些Folder中
    return *this;
}

// TODO: 
void swap(Message &lhs, Message &rhs) {
    std::cout << "Message swap-ed" << std::endl;    // 输出是否调用了swap函数
    using std::swap;    // 在本例中严格来说并不需要，但这是一个好习惯
    // 将每个消息的指针从它原来所在的Folder中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);    // 从名为folders的set中删除本Message，但是本Message仍然存在
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    std::cout << "After remMsg Size of lhs.folder is : " << lhs.folders.size() << std::endl;   // 输出经过上面的循环后set的大小
    std::cout << "After remMsg Size of rhs.folder is : " << rhs.folders.size() << std::endl;   // 输出经过上面的循环后set的大小
    //std::cout << "After remMsg Size of rhs.folder is : " << 
    // 交换contents和Folder指针set
    swap(lhs.folders, rhs.folders);     // 使用swap(set&, set&)
    swap(lhs.contents, rhs.contents);   // 使用swap(string&, string&)
    // 将每个Message的指针添加到它的新Folder中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
    //using std::swap;
    //lhs.remove_from_Folders(); // Use existing member function to avoid duplicate code.
    //rhs.remove_from_Folders(); // Use existing member function to avoid duplicate code.

    //swap(lhs.folders, rhs.folders);
    //swap(lhs.contents, rhs.contents);

    //lhs.add_to_Folders(lhs); // Use existing member function to avoid duplicate code.
    //rhs.add_to_Folders(rhs); // Use existing member function to avoid duplicate code.
}


void Message::print_debug() const {
    std::cout << contents << std::endl;
}