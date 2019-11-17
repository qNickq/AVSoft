#ifndef COMMAND_H
#define COMMAND_H

class Command
{

public:
    Command();

    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
     ~Command();
protected:

};

#endif // COMMAND_H
