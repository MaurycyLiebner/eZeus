#ifndef ETASK_H
#define ETASK_H

class eThreadBoard;

class eTask {
    friend class eThreadPool;
public:
    eTask();
    virtual ~eTask();
protected:
    virtual void run(eThreadBoard& data) { (void)data; }
    virtual void finish() {}
};

#endif // ETASK_H
