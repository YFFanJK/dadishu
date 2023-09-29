# dadishu
## 这是一个打地鼠的游戏，是我在实训期间利用C语言编写的一个测试Linux开发板的程序，加入的触摸功能

#### 1.代码编译在ubuntu上进行编译，我使用的是arm架构的开发板。所以编译的时候使用的命令是

```
arm-linux-gcc xiangmu.c -o xiangmu
```

经过编译后得到xiangmu文件

#### 2.利用SecureCRT并使用串口与Linux开发板连接

##### 2.1上传文件（代码名字为xiangmu）

```
rx xiangmu
```

##### 2.2上传图片素材

图片素材为.bmp格式

##### 2.3赋予xiangmu最高权限

```
chmod 777 xiangmu
```

##### 2.4运行xiangmu

```
./xiangmu
```

**打地鼠正确打到20个胜利**

**打错3个失败**

上面结果均会出现相应结果图片

# 说明！！！

1.代码目前已知的BUG是短时间连续点触控板会导致段错误中断程序。

2.如果要改变图片，请在代码中对应的地方修改为你替换图片的名字。

3.图片一定要是.bmp格式

4.背景图片分辨率请随着使用设备的屏幕分辨率而改变，我所使用的是800*480仅供参考

5.失败的结束画面

![new-shibai](https://github.com/YFFanJK/dadishu/assets/100122616/3c8756d4-07ee-4b12-83e2-a6b6b2d7c6ca)

6.胜利的结束画面

![new-shengli](https://github.com/YFFanJK/dadishu/assets/100122616/3be0a012-7091-40d5-9da3-07f80cb2cbd3)

## （以上图片均在“photo中”）
