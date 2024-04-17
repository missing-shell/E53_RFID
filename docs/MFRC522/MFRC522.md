# MFRC522相关说明

## 内部寄存器

```txt
-- CommandReg 启动和停止命令的执行 
-- ComIrqReg 包含中断请求标志 
-- ErrorReg 错误标志，指示执行的上个命令的错误状态 
-- Status2Reg 包含接收器和发送器的状态标志 
-- FIFODtataReg 64 字节 FIFO 缓冲区的输入和输出 
-- FIFOLevelReg 指示 FIFO 中存储的字节数 
-- ControlReg 不同的控制寄存器 
-- BitFramingReg 面向位的帧的调节 
-- CollReg RF 接口上检测到的第一个位冲突的位的位置 
-- ModeReg 定义发送和接收的常用模式 
-- TxModeReg 定义发送过程的数据传输速率
-- TxControlReg 控制天线驱动器管脚 TX1 和 TX2 的逻辑特性 
-- TModeRegTPrescalerReg定义内部定时器的设置
```

## 代码编写

对 MFRC522的控制，实现 RFID 卡的读写操作。

```txt
（1）设置 MF RC500 的状态。
（2）发送命令，要求 MF RC500 执行相应的动作。
（3）通过读 MF RC500 的状态标志来监测 MF RC500 的工作情况。
```

无论上述的哪一种方式，都是通过**读/写 MFRC522 的寄存器**来实现的：

配置 MFRC522 就是设置寄存器的某些位；

```txt
执行命令要向命令寄存器写入命令代码以及通过FIFO 缓冲区寄存器向缓冲区写入命令参数；
监测 MF RC500即读状态寄存器的标志位。
```

因此，**读写寄存器**是所有操作的基础。
