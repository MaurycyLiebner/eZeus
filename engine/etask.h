#ifndef ETASK_H
#define ETASK_H

class eTask {
    friend class eThreadPool;
public:
    eTask();
    virtual ~eTask();
protected:
    virtual void run() {}
    virtual void finish() {}
private:
    void exec();
};

#endif // ETASK_H
