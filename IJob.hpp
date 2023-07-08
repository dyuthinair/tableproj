template<typename IOp, typename R>
class IJob {
    public:
        virtual vector<IJob<IOp, R>*>* getChildren() = 0;
};

class IOp {

};

class R {

};