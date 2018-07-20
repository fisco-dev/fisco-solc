# fisco-solc

# 目录
<!-- TOC -->

- [1、功能拓展说明](#1-功能拓展说明)
    - [1.1 fisco-solc对EthCall的支持](#11-fisco-solc对ethcall的支持)
    - [1.2 国密版fisco-solc](#12-国密版fisco-solc)
- [2、使用方法](#2-使用方法)
- [3、编译方法](#3-编译方法)
    - [3.1 linux编译方法](#31-linux编译方法)
        - [3.1.1 编译普通版fisco-solc](#311-编译普通版fisco-solc)
        - [3.1.2 编译国密版fisco-solc](#312-编译国密版fisco-solc)
    - [3.2 windows编译方法](#32-windows编译方法)

<!-- TOC -->

<br>

fisco-solc是FISCO-BCOS的智能合约编译器。fisco-solc对以太坊的solc进行功能拓展，不仅能编译一般的以太坊合约，还能编译针对FISCO-BCOS的合约，实现了更加强大的功能。

基于以太坊solc的版本：0.4.11 （在使用前请确认合约的版本，是否支持被solc 0.4.11编译）

**拓展的功能：**

- **[EthCall](https://github.com/FISCO-BCOS/FISCO-BCOS/blob/master/doc/EthCall%E8%AF%B4%E6%98%8E%E6%96%87%E6%A1%A3.md)**
- **为了适配[国密版FISCO-BCOS](https://github.com/FISCO-BCOS/FISCO-BCOS/blob/master/doc/%E5%9B%BD%E5%AF%86%E6%93%8D%E4%BD%9C%E6%96%87%E6%A1%A3.md)增加国密版fisco-solc编译器，并通过开关ENCRYPTTYPE控制fisco-solc版本**

## 1、功能拓展说明

### 1.1 fisco-solc对EthCall的支持

<br>

fisco-solc对solc的拓展，主要为了兼容FISCO-BCOS中的EthCall功能，使其能编译基于EthCall实现的合约。EthCall可实现solidity语言对C++调用，拓展了合约的功能，提高了合约执行性能。具体Ethcall的介绍，请参考[Ethcall说明文档](https://github.com/FISCO-BCOS/FISCO-BCOS/blob/master/doc/EthCall%E8%AF%B4%E6%98%8E%E6%96%87%E6%A1%A3.md) 和 [EthCall设计文档](https://github.com/FISCO-BCOS/FISCO-BCOS/blob/master/doc/EthCall%E8%AE%BE%E8%AE%A1%E6%96%87%E6%A1%A3.md) 。

改动主要是增加了一条EVM指令：

``` cpp
// libevmasm/Instruction.h
XOR,                 ///< bitwise XOR operation
NOT,                 ///< bitwise NOT opertation
BYTE,                ///< retrieve single byte from word

SHA3 = 0x20,         ///< compute SHA3-256 hash
ETHCALL = 0x2f,      ///< call eth kernel function api  <------------------- New opcode

ADDRESS = 0x30,      ///< get address of currently executing account
BALANCE,             ///< get balance of the given account
ORIGIN,              ///< get execution origination address
```

<br>

### 1.2 国密版fisco-solc

<br>

[国密版FISCO-BCOS](https://github.com/FISCO-BCOS/FISCO-BCOS/blob/master/doc/%E5%9B%BD%E5%AF%86%E6%93%8D%E4%BD%9C%E6%96%87%E6%A1%A3.md) 更新SHA3算法为符合国密标准的SM3算法，**国密版fisco-solc主要用于兼容[国密版FISCO-BCOS](https://github.com/FISCO-BCOS/FISCO-BCOS/blob/master/doc/%E5%9B%BD%E5%AF%86%E6%93%8D%E4%BD%9C%E6%96%87%E6%A1%A3.md)，可编译出与国密版FISCO-BCOS相匹配的abi和bin文件，当向国密版FISCO-BCOS链上发送交易时，交易对应的合约代码必须由国密版fisco-solc编译**。

- **国密版fisco-solc:** 当开关ENCRYPTTYPE为ON时，编译出的fisco-solc为国密版fisco-solc;

- **普通版fisco-solc:** 当开关ENCRYPTTYPE为OFF时，编译出的fisco-solc为普通版fisco-solc.

<br>

[返回目录](#目录)

<br>


## 2、使用方法

[fisco-solc的可执行文件已经在根目录中提供](https://github.com/FISCO-BCOS/fisco-solc)，可直接下载使用，此处提供直接下载使用的方法。若需要手动编译，可参考本文第三部分：[3、编译方法](#3-编译方法)。

> 根据系统和FISCO-BCOS版本(当FISCO-BCOS为国密版时，为了保证[web3sdk生成代码的兼容性](https://github.com/FISCO-BCOS/web3sdk/blob/master/doc/guomi_support_manual.md#6-%E7%94%9F%E6%88%90%E6%94%AF%E6%8C%81%E5%9B%BD%E5%AF%86%E7%AE%97%E6%B3%95%E7%9A%84java%E4%BB%A3%E7%A0%81)，需要同时下载国密版fisco-solc-guomi和普通版fisco-solc)，点击下载相应的fisco-solc：

<br>

> **普通版fisco-solc** 

CentOs： [fisco-solc-centos](https://github.com/FISCO-BCOS/fisco-solc/raw/master/fisco-solc-centos) 

Ubuntu：[fisco-solc-ubuntu](https://github.com/FISCO-BCOS/fisco-solc/raw/master/fisco-solc-ubuntu)

<br>

> **国密版fisco-solc**

CentOs: [fisco-solc-guomi-centos](https://github.com/FISCO-BCOS/fisco-solc/raw/master/fisco-solc-guomi-centos)

Ubuntu: [fisco-solc-guomi-ubuntu](https://github.com/FISCO-BCOS/fisco-solc/raw/master/fisco-solc-guomi-ubuntu)


> **重命名**

``` shell
#===== 重命名普通版fisco-solc ====
mv fisco-solc-xxxx fisco-solc

#===== 重命名国密版fisco-solc ====
mv fisco-solc-guomi-xxx fisco-solc-guomi
```

> **安装入系统目录下**

``` shell
# ===== 安装普通版fisco-solc ====
chmod +x fisco-solc
sudo cp fisco-solc /usr/bin

# ==== 安装国密版fisco-solc ====
chmod +x fisco-solc-guomi
sudo cp fisco-solc-guomi /usr/bin
```

> **检查是否可用**

``` shell
# ==== 检查普通版fisco-solc ====
fisco-solc --help

# ==== 检查国密版fisco-solc ====
fisco-solc-guomi --help
```

> **安装成功，输出help信息，fisco-solc的使用方法与solc的相同。具体使用方法可参考：[solidity官方文档](https://solidity.readthedocs.io/en/latest/using-the-compiler.html) 。**

``` log
# fisco-bcos --help
fisco-solc, the Solidity commandline compiler of fisco-bcos.
Usage: fisco-solc [options] [input_file...]
Compiles the given Solidity input files (or the standard input if none given or
"-" is used as a file name) and outputs the components specified in the options
at standard output or in files in the output directory, if specified.
Imports are automatically read from the filesystem, but it is also possible to
remap paths using the context:prefix=path syntax.
Example:
    fisco-solc --bin -o /tmp/solcoutput dapp-bin=/usr/local/lib/dapp-bin contract.sol

Allowed options:
  --help               Show help message and exit.
  --version            Show version and exit.
  --optimize           Enable bytecode optimizer.
  --optimize-runs n (=200)
                       Estimated number of contract runs for optimizer tuning.
  --add-std            Add standard contracts.
  --libraries libs     Direct string or file containing library addresses. 
                       Syntax: <libraryName>: <address> [, or whitespace] ...
                       Address is interpreted as a hex string optionally 
                       prefixed by 0x.
  -o [ --output-dir ] path
                       If given, creates one file per component and 
                       contract/file at the specified directory.
  --overwrite          Overwrite existing files (used together with -o).
  --combined-json abi,asm,ast,bin,bin-runtime,clone-bin,devdoc,interface,metadata,opcodes,srcmap,srcmap-runtime,userdoc
                       Output a single json document containing the specified 
                       information.
  --gas                Print an estimate of the maximal gas usage for each 
                       function.
  --standard-json      Switch to Standard JSON input / output mode, ignoring 
                       all options. It reads from standard input and provides 
                       the result on the standard output.
  --assemble           Switch to assembly mode, ignoring all options and 
                       assumes input is assembly.
  --link               Switch to linker mode, ignoring all options apart from 
                       --libraries and modify binaries in place.
  --metadata-literal   Store referenced sources are literal data in the 
                       metadata output.
  --allow-paths path(s)
                       Allow a given path for imports. A list of paths can be 
                       supplied by separating them with a comma.

Output Components:
  --ast                AST of all source files.
  --ast-json           AST of all source files in JSON format.
  --asm                EVM assembly of the contracts.
  --asm-json           EVM assembly of the contracts in JSON format.
  --opcodes            Opcodes of the contracts.
  --bin                Binary of the contracts in hex.
  --bin-runtime        Binary of the runtime part of the contracts in hex.
  --clone-bin          Binary of the clone contracts in hex.
  --abi                ABI specification of the contracts.
  --hashes             Function signature hashes of the contracts.
  --userdoc            Natspec user documentation of all contracts.
  --devdoc             Natspec developer documentation of all contracts.
  --metadata           Combined Metadata JSON whose Swarm hash is stored 
                       on-chain.
  --formal             Translated source suitable for formal analysis.
  
  ###==== fisco-solc-guomi --help输出的信息与fisco-solc --help输出的信息相同 ====
```

<br>

[返回目录](#目录)

<br>


## 3、编译方法

若需要手动编译，可参考此处。

### 3.1 linux编译方法

#### 3.1.1 编译普通版fisco-solc

<br>

```bash
#====切换到源码目录====
$ cd fisco-solc

#====安装依赖环境====
$ cd script
$ chmod +x install_deps.sh
$ ./install_deps.sh

#====建立编译文件夹====
$ cd ../     #到fisco-solc的根目录
$ mkdir build
$ cd build

#====预编译、编译====
$ cmake3 .. #注意后面有两个点“..”，Centos用cmake3，Ubuntu用cmake
#或者: cmake3 -DENCRYPTTYPE=OFF ..
$ make

#====编译成功后，会在build/solc下生成 fisco-solc，查看版本====
$ cd solc/
$ ./fisco-solc --version  #得到版本信息，编译成功
fisco-solc, the solidity compiler commandline interface of fisco-bcos
Based on solc version: 0.4.11+commit.68ef5810.Linux.g++
```

<br>

#### 3.1.2 编译国密版fisco-solc

<br>

```bash
#==== 切换到源码目录====
$ cd fisco-solc

#==== 安装依赖环境 ====
$ cd script
$ chmod +x install_deps.sh
$ ./install_deps.sh

#====建立编译文件夹====
$ cd ../     #到fisco-solc的根目录
$ mkdir build
$ cd build

#==== 预编译、编译 ====
$ cmake3 -DENCRYPTTYPE=ON .. #DENCRYPTTYPE为ON表示fisco-solc开启国密特性，注意后面有两个点“..”，Centos用cmake3，Ubuntu用cmake
$ make  #可根据物理机配置调整编译线程数，例：make -j2表示用两个线程并发编译fisco-solc

#==== 编译成功后，会在build/solc下生成 fisco-solc，查看版本====
$ cd solc/
$ ./fisco-solc --version #得到版本信息，编译成功
fisco-solc, the solidity compiler commandline interface of fisco-bcos
Based on solc version: 0.4.11+commit.68ef5810.Linux.g++

```

<br>

[返回目录](#目录)

<br>


### 3.2 windows编译方法

（1）安装[CMake](https://cmake.org/download/)，配置系统环境变量

（2）安装[Visual Studio 2015](https://www.visualstudio.com/products/vs-2015-product-editions)

（3）在fisco-solc-master中新建build文件夹，进入build文件夹，打开cmd，执行命令，进行编译

- **编译产生普通版fisco-solc**

``` bash
cmake -DENCRYPTTYPE=OFF -G "Visual Studio 14 2015 Win64" ..
cmake --build . --config RelWithDebInfo
```

- **编译产生国密版fisco-solc(编译时，加上-DENCRYPTTYPE=ON选项)**

```bash
cmake -DENCRYPTTYPE=ON -G "Visual Studio 14 2015 Win64" ..
cmake --build . --config RelWithDebInfo
```

> 若编译时，报文件格式的错误，是windows无法读取boost库中iso8859_1.hpp的文件格式。将iso8859_1.hpp文件格式从utf-8改成iso8859-1，再重新编译。

（4）编译成功，在build\solc\RelWithDebInfo可以找到fisco-solc.exe，查看版本信息

``` powershell
fisco-bcos.exe --version
```

> 可看到基于windows版本的版本号

``` log
fisco-solc, the solidity compiler commandline interface of fisco-bcos
Based on solc version: 0.4.11+commit.68ef5810.Windows.msvc
```

<br>

[返回目录](#目录)

<br>
