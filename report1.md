# NS3学习报告一
## 一.实验结果
1.  用命令行读入并且输出了姓名和学号
2.  仿真在5s时停止输出，每一秒输出一次
3.  运用grep分别筛选了带有“+2”和“zyh”的输出内容
4.  运用wc对输出的行数，字符数和字节数

![命令行读入参数](http://ww3.sinaimg.cn/mw690/9fae6ceagw1f4nvwdqdhlj20k30b5q4y.jpg)

![筛选和统计](http://ww4.sinaimg.cn/mw690/9fae6ceagw1f4nvwbrsdvj20k20c076p.jpg)
## 二.分析


    C++:
    CommandLine cmd;
    std::string name;
    std::string id;
	cmd.AddValue ("name", "my name", name);
    cmd.AddValue ("id", "my id", id);

声明了两个变量，分别用于保存姓名(name)和学号(id),并且用NS3中的cmd,使得该两项参数可以在Linux的Terminal中使用命令行的形式输入；


    cmd:
    ./waf run="scratch/hello-simulator --name=zyh --id=2013100102029" 

以上是在Terminal中添加参数的命令行；

    C++:
    static void printHello(std::string word,std::string word1) {
    std::cout<<Simulator::Now()<<" Hello "<<word<<" "<<word1<<std::endl;
	Simulator::Schedule(Seconds(1),&printHello,word,word1); 
    //insert an event 1s later to call printHello function
    }

在输出函数中，首先输出当前时间，然后依次是Hello,name(word)和id(word1);如果不调用NS3里的simulator的stop函数，则是一个死循环

    C++:
    Simulator::Stop(Seconds(5));
	Simulator::Run ();
	Simulator::Destroy ();
    
依次调用stop(at 5),run 和 destroy之后，输出会在5s的时候停下来；

    cmd:
    ./waf run="scratch/hello-simulator --name=zyh --id=2013100102029"|grep "+2"
    
以上的命令即筛选了带有“+2”的输出结果，使得频幕上只显示带有“+2”的输出；

    cmd:
    ./waf run="scratch/hello-simulator --name=zyh --id=2013100102029"|wc
    
即统计了输出的行数，字符数和字节数。