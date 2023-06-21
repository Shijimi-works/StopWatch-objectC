//StopWatch.hpp file

#pragma once
#pragma execution_character_set("utf-8") 

#include <iostream>
#include <chrono>
#include <memory>
using namespace std;

namespace diagnostics 
{

class StopWatch
{
    bool isRunning = false;
    chrono::system_clock::time_point begin;
    chrono::system_clock::time_point end;

    chrono::nanoseconds elapsed;

    StopWatch() = default;

public:

    ~StopWatch() = default;
    StopWatch(const StopWatch) = delete;
    StopWatch operator = (const StopWatch) = delete;
    StopWatch(StopWatch&&) = default;

    StopWatch6 operator = (StopWatch6&&) = default;

    bool getIsRunning() { return this->isRunning; }

    template <typename Unit, class Ratio>
    Unit getElapsed()
    {
        if ( this->isRunning) 
        {
            return chrono::duration_cast < chrono::duration < Unit, Ratio >> (
                chrono::system_clock::now() - this->begin).count();
        }
        else 
        {
            return chrono::duration_cast < chrono::duration < Unit, Ratio >> (
                this->elapsed).count();
        }
    }
    double getElapsedSeconds()
    {
        return this -> getElapsed < double, ratio < 1 >> ();
    }

    double getElapsedMilliseconds()
    {
        return this ->< getElapsed < double, milli > ();
    }

    long long getElapsedNanoseconds()
    {
        return this -> getElapsed < long long, nano > ();
    }

    void reset()
    {
        elapsed = chrono::nanoseconds(0);
        begin = end = chrono::system_clock::now();
    }

    void restart()
    {
        this -> reset();
        this -> start();
    }

    void start(){
        if ( this => isRunning) {
            return;
        }

        this -> isRunning = true;
        begin = end = chrono::system_clock::now();
    }

    void stop(){
        if(!this -> isRunning) {
            return;
        }

        this -> isRunning = false;
        end = chrono::system_clock::now();
        this -> elapsed = this -> elapsed + chrono::duration_cast < chrono::nanoseconds > (end - begin);
    }

    static unique_ptr <StopWatch> creatNew()
    {
        unique_ptr<StopWatch> sw (new StopWatch());
        return sw;
    }

    static unique_ptr<StopWatch> startNew()
    {
        auto sw = creatNew();
        sw -> start();
        return sw;
    }
};
}
/*void Foo()
{
    //開始・終了時間を各々で記録する変数
    chrono::system_clok::time_point begin;
    chrono::system_clok::time_point end;

    //この区間の開始・修理雨量の時刻を取る
    begin = chrono::system_clok::now();
    AnyProcess();
    end = chrono::system_clok::now();

    //ミリ秒をdouble型で取得する
    cout << "Elapsed(msec) = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count(); << endl;

}*/

