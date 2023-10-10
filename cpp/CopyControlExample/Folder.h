#ifndef FOLDER_H
#define FOLDER_H

#include <set>

class Folder {
    friend class Message;
    friend void swap(Folder &, Folder &);
    friend void swap(Message &, Message &);
public:
    Folder() = default;
    Folder(const Folder &);
    Folder &operator=(const Folder &);
    ~Folder();

private:
    std::set<Message *> msgs;

    void add_to_Message(const Folder &);
    void remove_from_Message();

    void addMsg(Message *m) { msgs.insert(m); }
    void remMsg(Message *m) { msgs.erase(m); }
};

void swap(Folder &, Folder &);

#endif // FOLDER_H
