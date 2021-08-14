#ifndef ETASK_H
#define ETASK_H

class eThreadData;

class eTask {
    friend class eThreadPool;
public:
    eTask();
    virtual ~eTask();
protected:
    virtual void run(eThreadData& data) { (void)data; }
    virtual void finish() {}
};

#endif // ETASK_H
