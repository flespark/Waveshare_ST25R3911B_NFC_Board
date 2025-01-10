### WaveShare ST25R3911B NFC Board DEMO

基于VSCode的[微雪 ST25R3911B NFC Board](https://www.waveshare.net/wiki/ST25R3911B_NFC_Board) 示例工程，RFAL更新到官方适配ST25R3911的最新版。使用cmake作为构建工具，gcc作为编译器，jlink作为烧录调试工具，clangd作为代码索引和lint工具, ccache用于加快编译速度。

#### 如何使用

1. 首先在系统上安装必需的开发工具，开源软件在Windows下建议使用[scoop](https://scoop.sh/#/)安装：

```
scoop install vscode cmake ninja gcc-arm-none-eabi clangd ccache
```

    Linux可能需要额外安装`arm-none-eabi-newlib`软件包

2. 安装jlink，~~使用厂商提供中的资料 [FAQ0132_JLink手动添加Artery MCU_V2.0.0.zip](https://www.arterytek.com/file/download/375)，根据其中的说明文档修改jlink以添加对AT32支持~~
3. 打开vscode打开工程目录，安装推荐的插件
4. 调试器连接板子到电脑，vscode下方状态栏中的Build[F4]，Flash[F6]，Reset[F7]，Erase[F8]对应编译，烧录，复位，擦除操作， 调试[F5]借助[cortex-debug](https://github.com/Marus/cortex-debug/wiki)插件。配置相应的快捷键，需要添加 `.vscode/keybindings.json`中的相关配置项到vscode的系统快捷键配置文件中

#### 注意

- 淘宝购买的发货版本可能将MCU替换为了AT23F413RB, 此工程仅适用于STM32F103RB版本。切换到STM32同时需要改动板子上的串口选择跳线（改为RXD<->RXD1, TXD<->TXD1）
- Windows若报编译错误，执行cmake配置生成时指定编译器为Ninja
