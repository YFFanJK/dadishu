# dadishu
## 这是一个打地鼠的游戏，是我在实训期间利用C语言编写的一个测试Linux开发板的程序，加入的触摸功能

### 说明：

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
