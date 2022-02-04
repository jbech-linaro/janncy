class BenchMark
{
private:
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::microseconds res;
    clock::time_point t1, t2;
    std::string s;
    std::string e;

public:
    BenchMark(std::string str, std::string extra = "") {
        t1 = clock::now();
        s = str;
        e = extra;
    }

    ~BenchMark()
    {
        t2 = clock::now();
        std::cout << "[" << s << ", "
        << std::chrono::duration_cast<res>(t2-t1).count()/1e6;
	if (!e.empty())
		std::cout << ", " << e;
        std::cout << "]\n";
    }
};
